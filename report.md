# Assignment 1 Report

Student IT - 2506 Abdrakhmanov ILnur

Assignment: 1

# Task 1

## 1. Red Triangle

The first program was created to display a single red triangle.

The program creates a GLFW window with a size of 500 x 500 pixels.
GLAD is used to load the OpenGL functions.

The triangle vertices are stored in a vertex buffer object (VBO).
A vertex array object (VAO) is used to describe the vertex attributes.

A vertex shader receives the vertex position through the
`aPos` attribute.

A fragment shader assigns the color red to every fragment.

The triangle is rendered using:

`GL_TRIANGLES`

No deprecated OpenGL functions are used.

---

## 2. Blue Square

The second program displays a single blue square.

The square is constructed from two triangles because the program
uses the modern OpenGL programmable pipeline.

The vertex data is stored in a VBO and accessed through a VAO.

The fragment shader assigns the color blue.

The square is rendered using:

`GL_TRIANGLES`

The square fits completely inside the 500 x 500 window.

---

# Task 2

## Part 1

The second part demonstrates drawing several 2D polygons with colors.

The vertex shader contains two vertex attributes:

`vPosition`

and

`vColor`

The position attribute specifies the location of each vertex.

The color attribute specifies the color associated with each vertex.

The color is passed from the vertex shader to the fragment shader.

Because different vertices can have different colors, OpenGL
interpolates the colors across the triangles.

---

## Circle

The circle is generated using the parametric equations:

x = cos(angle)

y = sin(angle)

The angle is increased from 0 to 2*pi.

The generated points are scaled and translated to position the
circle inside the window.

The circle is rendered using:

`GL_TRIANGLE_FAN`

The red component of the vertex color changes according to the
angle, producing a shaded appearance.

---

## Ellipse

The ellipse is generated using the same parametric equation as
the circle.

The y coordinate is scaled to make the object shorter vertically.

The ellipse is rendered using triangles.

---

## Square

The square is constructed from triangles.

Multiple square regions with different grayscale colors are used
to create a transition from black to white.

---

## Triangle

The triangle uses three vertices with different colors.

The fragment shader receives the interpolated color from the
vertex shader.

This produces a smooth color gradient across the triangle.

---

# Task 2 Part 2

The creative program contains several different objects.

The scene contains:

1. A red horizontal ellipse.
2. A multicolor triangle.
3. A dark red shaded circle.
4. A set of concentric black and white squares.

The background is black.

The triangle demonstrates color interpolation between red,
green, and blue vertices.

The circle uses the parametric equation of a circle and changes
the red component according to the angle.

The concentric squares are drawn from largest to smallest.
Alternating black and white squares create the target-like
pattern.

---

# OpenGL Techniques Used

The programs use the modern OpenGL programmable pipeline.

The following OpenGL objects were used:

- Vertex Array Objects (VAO)
- Vertex Buffer Objects (VBO)
- Vertex shaders
- Fragment shaders
- Vertex attributes
- Color interpolation
- GL_TRIANGLES
- GL_TRIANGLE_FAN

Deprecated immediate-mode OpenGL functions were not used.

Examples of functions deliberately not used include:

- glBegin()
- glEnd()
- glVertex*()
- glColor*()
- glMatrixMode()

# Testing

The programs were developed using Visual Studio on Windows.

The OpenGL context was configured to use OpenGL 3.3 Core Profile.

The window size is 500 x 500 pixels.

The programs were tested by compiling and running each source file
individually.