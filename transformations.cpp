#include <iostream>
#include <cmath>
#include <GL/freeglut.h>

using namespace std;

enum TransformMode {
    SCALE,
    ROTATE,
    TRANSLATE
};

static TransformMode currentMode = ROTATE;

static float scaleX = 0.55f;
static float scaleY = 0.55f;
static float scaleZ = 0.55f;

static float rotX = 35.264f;
static float rotY = -45.0f;
static float rotZ = 0.0f;

static float transX = 0.0f;
static float transY = 0.0f;
static float transZ = 0.0f;

static float scaleDelta = 0.05f;
static float rotDelta = 5.0f;
static float transDelta = 0.05f;

static void printInstructions() {
    cout << "\n============================================\n";
    cout << "         3D Transformations Controls        \n";
    cout << "============================================\n";
    cout << "s / S : SCALE\n";
    cout << "r / R : ROTATE\n";
    cout << "t / T : TRANSLATE\n";
    cout << "--------------------------------------------\n";
    cout << "x : decrease X     X : increase X\n";
    cout << "y : decrease Y     Y : increase Y\n";
    cout << "z : decrease Z     Z : increase Z\n";
    cout << "--------------------------------------------\n";
    cout << "+ : increase step\n";
    cout << "- : decrease step\n";
    cout << "SPACE / C : reset\n";
    cout << "ESC : exit\n";
    cout << "============================================\n\n";
}

static void resetTransformations() {
    scaleX = 0.55f;
    scaleY = 0.55f;
    scaleZ = 0.55f;

    rotX = 35.264f;
    rotY = -45.0f;
    rotZ = 0.0f;

    transX = 0.0f;
    transY = 0.0f;
    transZ = 0.0f;

    scaleDelta = 0.05f;
    rotDelta = 5.0f;
    transDelta = 0.05f;

    currentMode = ROTATE;
}

static void drawCube() {
    glBegin(GL_QUADS);

    // Top
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Front
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Left
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Bottom
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glEnd();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(transX, transY, transZ);

    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    glScalef(scaleX, scaleY, scaleZ);

    drawCube();

    glutSwapBuffers();
}

static void reshape(int width, int height) {
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height;

    if (aspect >= 1.0f)
        glOrtho(-2.5f * aspect, 2.5f * aspect,
            -2.5f, 2.5f,
            -10.0f, 10.0f);
    else
        glOrtho(-2.5f, 2.5f,
            -2.5f / aspect, 2.5f / aspect,
            -10.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 's':
    case 'S':
        currentMode = SCALE;
        break;

    case 'r':
    case 'R':
        currentMode = ROTATE;
        break;

    case 't':
    case 'T':
        currentMode = TRANSLATE;
        break;

    case 'x':
        if (currentMode == SCALE)
            scaleX -= scaleDelta;
        else if (currentMode == ROTATE)
            rotX -= rotDelta;
        else
            transX -= transDelta;
        break;

    case 'X':
        if (currentMode == SCALE)
            scaleX += scaleDelta;
        else if (currentMode == ROTATE)
            rotX += rotDelta;
        else
            transX += transDelta;
        break;

    case 'y':
        if (currentMode == SCALE)
            scaleY -= scaleDelta;
        else if (currentMode == ROTATE)
            rotY -= rotDelta;
        else
            transY -= transDelta;
        break;

    case 'Y':
        if (currentMode == SCALE)
            scaleY += scaleDelta;
        else if (currentMode == ROTATE)
            rotY += rotDelta;
        else
            transY += transDelta;
        break;

    case 'z':
        if (currentMode == SCALE)
            scaleZ -= scaleDelta;
        else if (currentMode == ROTATE)
            rotZ -= rotDelta;
        else
            transZ -= transDelta;
        break;

    case 'Z':
        if (currentMode == SCALE)
            scaleZ += scaleDelta;
        else if (currentMode == ROTATE)
            rotZ += rotDelta;
        else
            transZ += transDelta;
        break;

    case '+':
    case '=':
        if (currentMode == SCALE)
            scaleDelta += 0.01f;
        else if (currentMode == ROTATE)
            rotDelta += 1.0f;
        else
            transDelta += 0.01f;
        break;

    case '-':
    case '_':
        if (currentMode == SCALE)
            scaleDelta = fmax(0.001f, scaleDelta - 0.01f);
        else if (currentMode == ROTATE)
            rotDelta = fmax(0.1f, rotDelta - 1.0f);
        else
            transDelta = fmax(0.001f, transDelta - 0.01f);
        break;

    case ' ':
    case 'c':
    case 'C':
        resetTransformations();
        break;

    case 27:
        glutLeaveMainLoop();
        return;
    }

    glutPostRedisplay();
}

void runTransformations() {
    printInstructions();

    int argc = 1;
    char* argv[] = {
        (char*)"3DTransformations"
    };

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);

    glutCreateWindow("3D Transformations - Cube");

    glEnable(GL_DEPTH_TEST);

    glClearColor(
        1.0f,
        1.0f,
        1.0f,
        1.0f
    );

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}