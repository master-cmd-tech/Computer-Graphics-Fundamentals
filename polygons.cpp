#include <iostream>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {
    const float PI = 3.14159265358979323846f;

    const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 color;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
    color = vColor;
}
)";

    const char* fragmentShaderSource = R"(
#version 330 core

in vec3 color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0);
}
)";

    unsigned int compileShader(unsigned int type, const char* source)
    {
        unsigned int shader = glCreateShader(type);

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << std::endl;
        }

        return shader;
    }

    unsigned int createShaderProgram()
    {
        unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        unsigned int program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        int success;
        char infoLog[512];

        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout << "Shader linking error:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    void createObject(
        const std::vector<float>& vertices,
        unsigned int& VAO,
        unsigned int& VBO)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(float),
            vertices.data(),
            GL_STATIC_DRAW
        );

        // Position
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)0
        );
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)(3 * sizeof(float))
        );
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    std::vector<float> createTriangle()
    {
        return {
             0.00f,  0.78f, 0.0f,   1.0f, 0.10f, 0.25f,
            -0.28f,  0.30f, 0.0f,   0.10f, 1.0f, 0.25f,
             0.28f,  0.30f, 0.0f,   0.10f, 0.35f, 1.0f
        };
    }

    std::vector<float> createEllipse()
    {
        std::vector<float> vertices;
        const int segments = 80;

        vertices.push_back(-0.62f);
        vertices.push_back(0.58f);
        vertices.push_back(0.0f);

        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        for (int i = 0; i <= segments; i++)
        {
            float angle = 2.0f * PI * i / segments;

            float x = -0.62f + 0.34f * cos(angle);
            float y = 0.58f + 0.14f * sin(angle);

            float red = 0.75f + 0.25f * (cos(angle) + 1.0f) / 2.0f;
            float green = 0.02f;
            float blue = 0.02f;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0.0f);

            vertices.push_back(red);
            vertices.push_back(green);
            vertices.push_back(blue);
        }

        return vertices;
    }

    std::vector<float> createCircle()
    {
        std::vector<float> vertices;
        const int segments = 80;

        vertices.push_back(0.62f);
        vertices.push_back(0.58f);
        vertices.push_back(0.0f);

        vertices.push_back(0.65f);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        for (int i = 0; i <= segments; i++)
        {
            float angle = 2.0f * PI * i / segments;

            float x = 0.62f + 0.25f * cos(angle);
            float y = 0.58f + 0.25f * sin(angle);

            float shade = 0.15f + 0.75f * ((cos(angle) + 1.0f) / 2.0f);

            float red = shade;
            float green = 0.0f;
            float blue = 0.0f;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0.0f);

            vertices.push_back(red);
            vertices.push_back(green);
            vertices.push_back(blue);
        }

        return vertices;
    }

    std::vector<float> createSquare(
        float centerX,
        float centerY,
        float halfSize,
        float r,
        float g,
        float b)
    {
        return {
            centerX - halfSize, centerY - halfSize, 0.0f, r, g, b,
            centerX + halfSize, centerY - halfSize, 0.0f, r, g, b,
            centerX + halfSize, centerY + halfSize, 0.0f, r, g, b,

            centerX - halfSize, centerY - halfSize, 0.0f, r, g, b,
            centerX + halfSize, centerY + halfSize, 0.0f, r, g, b,
            centerX - halfSize, centerY + halfSize, 0.0f, r, g, b
        };
    }
}

void runPolygons()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "2D Polygons Scene", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    unsigned int shaderProgram = createShaderProgram();

    // ELLIPSE
    std::vector<float> ellipse = createEllipse();
    unsigned int ellipseVAO, ellipseVBO;
    createObject(ellipse, ellipseVAO, ellipseVBO);

    // TRIANGLE
    std::vector<float> triangle = createTriangle();
    unsigned int triangleVAO, triangleVBO;
    createObject(triangle, triangleVAO, triangleVBO);

    // CIRCLE
    std::vector<float> circle = createCircle();
    unsigned int circleVAO, circleVBO;
    createObject(circle, circleVAO, circleVBO);

    // SQUARE TARGET
    std::vector<float> square1 = createSquare(0.0f, -0.55f, 0.35f, 1.0f, 1.0f, 1.0f);
    std::vector<float> square2 = createSquare(0.0f, -0.55f, 0.275f, 0.0f, 0.0f, 0.0f);
    std::vector<float> square3 = createSquare(0.0f, -0.55f, 0.20f, 1.0f, 1.0f, 1.0f);
    std::vector<float> square4 = createSquare(0.0f, -0.55f, 0.125f, 0.0f, 0.0f, 0.0f);
    std::vector<float> square5 = createSquare(0.0f, -0.55f, 0.055f, 1.0f, 1.0f, 1.0f);
    std::vector<float> square6 = createSquare(0.0f, -0.55f, 0.025f, 0.0f, 0.0f, 0.0f);

    unsigned int squareVAO[6];
    unsigned int squareVBO[6];

    createObject(square1, squareVAO[0], squareVBO[0]);
    createObject(square2, squareVAO[1], squareVBO[1]);
    createObject(square3, squareVAO[2], squareVBO[2]);
    createObject(square4, squareVAO[3], squareVBO[3]);
    createObject(square5, squareVAO[4], squareVBO[4]);
    createObject(square6, squareVAO[5], squareVBO[5]);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Red ellipse
        glBindVertexArray(ellipseVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(ellipse.size() / 6));

        // Gradient triangle
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Dark red circle
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(circle.size() / 6));

        // Square target
        for (int i = 0; i < 6; i++)
        {
            glBindVertexArray(squareVAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &ellipseVAO);
    glDeleteBuffers(1, &ellipseVBO);

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);

    glDeleteVertexArrays(1, &circleVAO);
    glDeleteBuffers(1, &circleVBO);

    for (int i = 0; i < 6; i++)
    {
        glDeleteVertexArrays(1, &squareVAO[i]);
        glDeleteBuffers(1, &squareVBO[i]);
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}