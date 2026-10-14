#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

const float PI = 3.14159265359f;

bool animationRunning = true;

float squareAngle = 0.0f;
float triangleAngle = 0.0f;
float circleScale = 1.0f;

float circleScaleSpeed = 0.01f;

float squareR = 1.0f;
float squareG = 1.0f;
float squareB = 1.0f;

float objectR = 1.0f;
float objectG = 0.0f;
float objectB = 0.0f;

float subR = 0.2f;
float subG = 0.2f;
float subB = 0.5f;

int mainWindow;
int subWindow;
int window2;


void drawSquare()
{
    glPushMatrix();

    glRotatef(squareAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(squareR, squareG, squareB);

    glBegin(GL_QUADS);

    glVertex2f(-0.25f, -0.25f);
    glVertex2f(0.25f, -0.25f);
    glVertex2f(0.25f, 0.25f);
    glVertex2f(-0.25f, 0.25f);

    glEnd();

    glPopMatrix();
}


void displayMain()
{
    glutSetWindow(mainWindow);

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawSquare();

    glutSwapBuffers();
}



void displaySubWindow()
{
    glutSetWindow(subWindow);

    glClearColor(subR, subG, subB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.3f, 0.3f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        float x = 0.55f * std::cos(angle);
        float y = 0.30f * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();

    glutSwapBuffers();
}


void displayWindow2()
{
    glutSetWindow(window2);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glPushMatrix();

    glScalef(circleScale, circleScale, 1.0f);

    glColor3f(objectR, objectG, objectB);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(-0.45f, 0.25f);

    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        float x = -0.45f + 0.25f * std::cos(angle);
        float y = 0.25f + 0.25f * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();

    glPopMatrix();



    glPushMatrix();

    glTranslatef(0.45f, 0.20f, 0.0f);

    glRotatef(triangleAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(objectR, objectG, objectB);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.30f);
    glVertex2f(-0.30f, -0.25f);
    glVertex2f(0.30f, -0.25f);

    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}



void idle()
{
    if (!animationRunning)
        return;

    squareAngle += 0.4f;

    triangleAngle -= 0.6f;

    circleScale += circleScaleSpeed;

    if (circleScale >= 1.3f)
    {
        circleScaleSpeed = -0.01f;
    }

    if (circleScale <= 0.7f)
    {
        circleScaleSpeed = 0.01f;
    }

    glutSetWindow(mainWindow);
    glutPostRedisplay();

    glutSetWindow(window2);
    glutPostRedisplay();

    glutSetWindow(subWindow);
    glutPostRedisplay();
}


void keyboardWindow2(unsigned char key, int, int)
{
    switch (key)
    {
    case 'r':
        objectR = 1.0f;
        objectG = 0.0f;
        objectB = 0.0f;
        break;

    case 'g':
        objectR = 0.0f;
        objectG = 1.0f;
        objectB = 0.0f;
        break;

    case 'b':
        objectR = 0.0f;
        objectG = 0.0f;
        objectB = 1.0f;
        break;

    case 'y':
        objectR = 1.0f;
        objectG = 1.0f;
        objectB = 0.0f;
        break;

    case 'o':
        objectR = 1.0f;
        objectG = 0.5f;
        objectB = 0.0f;
        break;

    case 'p':
        objectR = 0.6f;
        objectG = 0.0f;
        objectB = 0.8f;
        break;

    case 'w':
        objectR = 1.0f;
        objectG = 1.0f;
        objectB = 1.0f;
        break;

    default:
        return;
    }

    glutPostRedisplay();
}


void mainMenu(int option)
{
    switch (option)
    {
    case 1:
        animationRunning = false;
        break;

    case 2:
        animationRunning = true;
        break;

    case 3:
        squareR = 1.0f;
        squareG = 1.0f;
        squareB = 1.0f;
        break;

    case 4:
        squareR = 1.0f;
        squareG = 0.0f;
        squareB = 0.0f;
        break;

    case 5:
        squareR = 0.0f;
        squareG = 1.0f;
        squareB = 0.0f;
        break;
    }

    glutSetWindow(mainWindow);
    glutPostRedisplay();
}


void subWindowMenu(int option)
{
    switch (option)
    {
    case 1:
        subR = 1.0f;
        subG = 1.0f;
        subB = 1.0f;
        break;

    case 2:
        subR = 1.0f;
        subG = 0.0f;
        subB = 0.0f;
        break;

    case 3:
        subR = 0.0f;
        subG = 1.0f;
        subB = 0.0f;
        break;

    case 4:
        subR = 0.0f;
        subG = 0.0f;
        subB = 1.0f;
        break;

    case 5:
        subR = 1.0f;
        subG = 1.0f;
        subB = 0.0f;
        break;
    }

    glutSetWindow(subWindow);
    glutPostRedisplay();
}


void createMenus()
{

    int squareColorMenu = glutCreateMenu(mainMenu);

    glutAddMenuEntry("White", 3);
    glutAddMenuEntry("Red", 4);
    glutAddMenuEntry("Green", 5);


    int mainMenuID = glutCreateMenu(mainMenu);

    glutAddMenuEntry("Stop Animation", 1);
    glutAddMenuEntry("Start Animation", 2);
    glutAddSubMenu("Square Colors", squareColorMenu);


    glutSetWindow(mainWindow);

    glutAttachMenu(GLUT_RIGHT_BUTTON);



    int subMenuID = glutCreateMenu(subWindowMenu);

    glutAddMenuEntry("White Background", 1);
    glutAddMenuEntry("Red Background", 2);
    glutAddMenuEntry("Green Background", 3);
    glutAddMenuEntry("Blue Background", 4);
    glutAddMenuEntry("Yellow Background", 5);

    glutSetWindow(subWindow);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    (void)mainMenuID;
    (void)subMenuID;
}


void runInteraction()
{
    int argc = 1;

    char arg0[] = "interaction";

    char* argv[] =
    {
        arg0,
        nullptr
    };

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);

    mainWindow = glutCreateWindow(
        "Main Window - Black and White Square"
    );

    glutDisplayFunc(displayMain);



    subWindow = glutCreateSubWindow(
        mainWindow,
        50,
        50,
        250,
        200
    );

    glutDisplayFunc(displaySubWindow);


    glutInitWindowSize(600, 600);
    glutInitWindowPosition(750, 100);

    window2 = glutCreateWindow("window 2");

    glutDisplayFunc(displayWindow2);

    glutKeyboardFunc(keyboardWindow2);



    createMenus();



    glutIdleFunc(idle);


    glutMainLoop();
}