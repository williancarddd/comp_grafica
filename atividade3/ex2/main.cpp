#include "SolarSystem.h"
#include <GL/freeglut.h>
#include <cmath>


class Simulation {
private:
    SolarSystem solarSystem;
    static float eyex, eyey, eyez;
    static float cameraYaw, cameraPitch;
    static int lastMouseX, lastMouseY;
    static float cameraDistance;

public:
    static void display();
    static void reshape(int width, int height);
    static void timer(int value);
    static void mouseMotion(int x, int y);
    static void mouseClick(int button, int state, int x, int y);

    void start(int argc, char **argv);
};

float Simulation::eyex = 0;
float Simulation::eyey = 60;
float Simulation::eyez = 120;
float Simulation::cameraYaw = 0;
float Simulation::cameraPitch = 0;
float Simulation::cameraDistance = 220;
int Simulation::lastMouseX = 0;
int Simulation::lastMouseY = 0;

void Simulation::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float radYaw = cameraYaw * M_PI / 180.0f;
    float radPitch = cameraPitch * M_PI / 180.0f;

    eyex = cameraDistance * cos(radPitch) * sin(radYaw);
    eyey = cameraDistance * sin(radPitch);
    eyez = cameraDistance * cos(radPitch) * cos(radYaw);

    gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

    Simulation *sim = static_cast<Simulation *>(glutGetWindowData());
    sim->solarSystem.draw();

    glutSwapBuffers();
}

void Simulation::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, static_cast<float>(width) / height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Simulation::timer(int value) {
    Simulation *sim = static_cast<Simulation *>(glutGetWindowData());
    sim->solarSystem.updateAngles();
    glutPostRedisplay();
    glutTimerFunc(33, timer, value);
}

void Simulation::mouseMotion(int x, int y) {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    cameraYaw += dx * 0.2f;
    cameraPitch += dy * 0.2f;

    if (cameraPitch > 89.0f)
        cameraPitch = 89.0f;
    else if (cameraPitch < -89.0f)
        cameraPitch = -89.0f;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

void Simulation::mouseClick(int button, int state, int x, int y) {
    if (button == 3 && state == GLUT_DOWN) {
        cameraDistance -= 10;
        if (cameraDistance < 30) cameraDistance = 30;
        glutPostRedisplay();
    } else if (button == 4 && state == GLUT_DOWN) {
        cameraDistance += 10;
        if (cameraDistance > 500) cameraDistance = 500;
        glutPostRedisplay();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

void Simulation::start(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glEnable ( GL_TEXTURE_2D );
	glEnable(GL_COLOR_MATERIAL);
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
    int id = glutCreateWindow(argv[0]);
    glutSetWindowData(this);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);
    glutTimerFunc(33, timer, 1);
    glutMainLoop();
}

int main(int argc, char **argv) {
    Simulation simulation;
    simulation.start(argc, argv);
    return 0;
}
