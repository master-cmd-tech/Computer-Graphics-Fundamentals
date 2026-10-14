#include <iostream>
#include <vector>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {
    const float PI = 3.14159265359f;

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

    unsigned int createShaderProgram()
    {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

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

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            6 * sizeof(float),
            (void*)0
        );
        glEnableVertexAttribArray(0);

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
}

void runCreative()
{
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Task 2 - Creative Picture", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD initialization failed\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    unsigned int shaderProgram = createShaderProgram();

    std::vector<float> circle;
    circle.push_back(-0.55f);
    circle.push_back(0.45f);
    circle.push_back(0.0f);
    circle.push_back(1.0f);
    circle.push_back(0.0f);
    circle.push_back(0.0f);

    const int circlePoints = 60;
    for (int i = 0; i <= circlePoints; i++)
    {
        float angle = 2.0f * PI * i / circlePoints;
        float x = -0.55f + 0.30f * cos(angle);
        float y = 0.45f + 0.30f * sin(angle);

        float red = 0.3f + 0.7f * (cos(angle) + 1.0f) / 2.0f;
        float green = 0.0f;
        float blue = 0.0f;

        circle.push_back(x);
        circle.push_back(y);
        circle.push_back(0.0f);
        circle.push_back(red);
        circle.push_back(green);
        circle.push_back(blue);
    }

    unsigned int circleVAO, circleVBO;
    createObject(circle, circleVAO, circleVBO);

    std::vector<float> ellipse;
    const int ellipsePoints = 60;
    for (int i = 0; i < ellipsePoints; i++)
    {
        float angle = 2.0f * PI * i / ellipsePoints;
        float x = 0.35f + 0.30f * cos(angle);
        float y = 0.45f + 0.18f * sin(angle);

        ellipse.push_back(x);
        ellipse.push_back(y);
        ellipse.push_back(0.0f);
        ellipse.push_back(0.0f);
        ellipse.push_back(0.7f);
        ellipse.push_back(1.0f);
    }

    unsigned int ellipseVAO, ellipseVBO;
    createObject(ellipse, ellipseVAO, ellipseVBO);

    std::vector<float> square;
    float size = 0.38f;
    float squareVertices[] =
    {
        -size, -0.65f - size,
         size, -0.65f - size,
         size, -0.65f + size,
        -size, -0.65f + size
    };

    int indices[] = { 0, 1, 2, 0, 2, 3 };
    float colors[4][3] =
    {
        {0.0f, 0.0f, 0.0f},
        {0.35f, 0.35f, 0.35f},
        {1.0f, 1.0f, 1.0f},
        {0.65f, 0.65f, 0.65f}
    };

    for (int i = 0; i < 6; i++)
    {
        int v = indices[i];
        square.push_back(squareVertices[v * 2]);
        square.push_back(squareVertices[v * 2 + 1]);
        square.push_back(0.0f);
        square.push_back(colors[v][0]);
        square.push_back(colors[v][1]);
        square.push_back(colors[v][2]);
    }

    unsigned int squareVAO, squareVBO;
    createObject(square, squareVAO, squareVBO);

    std::vector<float> triangle =
    {
         0.0f,  -0.05f, 0.0f,  1.0f, 0.2f, 0.2f,
        -0.25f, -0.55f, 0.0f,  0.2f, 0.2f, 1.0f,
         0.25f, -0.55f, 0.0f,  0.2f, 1.0f, 0.2f
    };

    unsigned int triangleVAO, triangleVBO;
    createObject(triangle, triangleVAO, triangleVBO);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Circle
        glBindVertexArray(circleVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(circle.size() / 6));

        // Ellipse
        glBindVertexArray(ellipseVAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(ellipse.size() / 6));

        // Square
        glBindVertexArray(squareVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Triangle
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &circleVAO);
    glDeleteBuffers(1, &circleVBO);
    glDeleteVertexArrays(1, &ellipseVAO);
    glDeleteBuffers(1, &ellipseVBO);
    glDeleteVertexArrays(1, &squareVAO);
    glDeleteBuffers(1, &squareVBO);
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVBO);

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}