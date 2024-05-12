#include <GL/freeglut.h>
#include <cmath>
#include <iostream>

class CelestialBody {
protected:
    float radius;
    float color[3];
    float angle;
    float distance;

public:
    CelestialBody(float r, float red, float green, float blue, float dist) :
        radius(r), distance(dist), angle(0) {
        color[0] = red;
        color[1] = green;
        color[2] = blue;
    }

    void setAngle(float a) { angle = fmod(a, 360.0f); }

    virtual void draw() const {
        glColor3f(color[0], color[1], color[2]);
        glutSolidSphere(radius, 16, 16);
    }

    virtual void drawOrbit() const {
        glRotatef(angle, 0, 1, 0);
        glTranslatef(distance, 0, 0);
        draw();
    }

    virtual void updateAngle(float increment) { setAngle(angle + increment); }

    float getDistance() const { return distance; }
};

class Moon : public CelestialBody {
public:
    Moon() : CelestialBody(1, 0.5f, 0.5f, 0.5f, 8) {}

    void drawOrbit(float earthAngle) const {
        glRotatef(earthAngle, 0, 1, 0);
        glTranslatef(distance, 0, 0);
        CelestialBody::draw();
    }
};

class Mercury : public CelestialBody {
public:
    Mercury() : CelestialBody(2, 0.7f, 0.7f, 0.7f, 20) {}
};

class Venus : public CelestialBody {
public:
    Venus() : CelestialBody(3, 1, 0.5f, 0, 40) {}
};

class Earth : public CelestialBody {
private:
    Moon moon;

public:
    Earth() : CelestialBody(5, 0, 0, 1, 60) {}

    void drawOrbit() const override {
        glRotatef(angle, 0, 1, 0);
        glTranslatef(distance, 0, 0);
        CelestialBody::draw();
        glPushMatrix();
        moon.drawOrbit(angle);
        glPopMatrix();
    }

    void updateMoon(float increment) { moon.updateAngle(increment); }
};

class Mars : public CelestialBody {
public:
    Mars() : CelestialBody(4, 1, 0.2f, 0, 75) {}
};


// moonjup recei the eix for rotate
class JupiterMoon : public CelestialBody {
public:
    JupiterMoon(float dist) : CelestialBody(1, 0.5f, 0.5f, 0.5f, dist) {}

    void drawOrbit(float jupiterAngle) const {
        glRotatef(jupiterAngle, 0, 1, 0);
        glTranslatef(distance, 0, 0);
        CelestialBody::draw();
    }
};

class Jupiter : public CelestialBody {
private:
    JupiterMoon moon1;
    JupiterMoon moon2;
    JupiterMoon moon3;

public:
    Jupiter() : CelestialBody(9, 0.8f, 0.5f, 0.3f, 100),
                moon1(15), moon2(20), moon3(25) {}

    void drawOrbit() const override {
        glRotatef(angle, 0, 1, 0);
        glTranslatef(distance, 0, 0);
        CelestialBody::draw();

        glPushMatrix();
        moon1.drawOrbit(angle);
        glPopMatrix();

        glPushMatrix();
        moon2.drawOrbit(angle *  0.9f); // Ângulo diferente para evitar sobreposição
        glPopMatrix();

        glPushMatrix();
        moon3.drawOrbit(angle * 0.7f);
        glPopMatrix();
    }
};
class Saturn : public CelestialBody
{
public:
  Saturn() : CelestialBody(8, 0.9f, 0.7f, 0.2f, 130) {}
  void draw() const override
  {
    CelestialBody::draw();

    // Desenha o anel ao redor de Júpiter
    glColor3f(0.6f, 0.5f, 0.3f);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);           // Posiciona o anel ao redor do equador
    glutSolidTorus(0.2f, 12, 30, 30); // raio interno, raio externo, lados, segmentos (é um toroide)
    glPopMatrix();
  }
};
class Uranus : public CelestialBody {
public:
    Uranus() : CelestialBody(7, 0.6f, 0.8f, 0.9f, 160) {}
};

class Neptune : public CelestialBody {
public:
    Neptune() : CelestialBody(7, 0.2f, 0.4f, 0.8f, 190) {}
};

void drawOrbit(float radius) {
    glBegin(GL_LINE_LOOP);
    const int num_segments = 100;
    for (int i = 0; i < num_segments; ++i) {
        float angle = 2 * M_PI * i / num_segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0, z);
    }
    glEnd();
}

class SolarSystem {
private:
    CelestialBody sun;
    Earth earth;
    Mars mars;
    Mercury mercury;
    Venus venus;
    Jupiter jupiter;
    Saturn saturn;
    Uranus uranus;
    Neptune neptune;

public:
    SolarSystem() : sun(12, 1, 1, 0, 0) {}Unknown
    void draw() const {
        sun.draw();

        glColor3f(1, 1, 1); // Branco para as órbitas

        drawOrbit(mercury.getDistance());
        drawOrbit(venus.getDistance());
        drawOrbit(earth.getDistance());
        drawOrbit(mars.getDistance());
        drawOrbit(jupiter.getDistance());
        drawOrbit(saturn.getDistance());
        drawOrbit(uranus.getDistance());
        drawOrbit(neptune.getDistance());

        glPushMatrix();
        mercury.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        venus.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        earth.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        mars.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        jupiter.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        saturn.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        uranus.drawOrbit();
        glPopMatrix();

        glPushMatrix();
        neptune.drawOrbit();
        glPopMatrix();
    }
    void updateAngles() {
        earth.updateAngle(3);
        earth.updateMoon(6);
        mars.updateAngle(2);
        mercury.updateAngle(4);
        venus.updateAngle(3);
        jupiter.updateAngle(2);
        saturn.updateAngle(1.5);
        uranus.updateAngle(1.2);
        neptune.updateAngle(1.1);
    }
};

class Simulation {
private:
    SolarSystem solarSystem;
    static float eyex, eyey, eyez;
    static float cameraYaw, cameraPitch;
    static int lastMouseX, lastMouseY;
    static float cameraDistance;

public:
    static void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Calcula as coordenadas esféricas para a câmera
        float radYaw = cameraYaw * M_PI / 180.0f;
        float radPitch = cameraPitch * M_PI / 180.0f;

        // Define a posição da câmera baseada nos ângulos e na distância
        eyex = cameraDistance * cos(radPitch) * sin(radYaw);
        eyey = cameraDistance * sin(radPitch);
        eyez = cameraDistance * cos(radPitch) * cos(radYaw);

        // Define a visão da câmera, apontando para o ponto central
        gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

        // Desenha o sistema solar
        Simulation *sim = static_cast<Simulation *>(glutGetWindowData());
        sim->solarSystem.draw();

        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70.0f, static_cast<float>(width) / height, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static void timer(int value) {
        Simulation *sim = static_cast<Simulation *>(glutGetWindowData());
        sim->solarSystem.updateAngles();
        glutPostRedisplay();
        glutTimerFunc(33, timer, value);
    }

    static void mouseMotion(int x, int y) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        cameraYaw += dx * 0.2f;
        cameraPitch += dy * 0.2f;

        // Limita a rotação vertical para evitar inversão completa
        if (cameraPitch > 89.0f)
            cameraPitch = 89.0f;
        else if (cameraPitch < -89.0f)
            cameraPitch = -89.0f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }

    static void mouseClick(int button, int state, int x, int y) {
        // Detecta a rolagem para controlar o zoom
        if (button == 3 && state == GLUT_DOWN) {  // Rodinha para cima
            cameraDistance -= 10;
            if (cameraDistance < 30) cameraDistance = 30;
            glutPostRedisplay();
        } else if (button == 4 && state == GLUT_DOWN) {  // Rodinha para baixo
            cameraDistance += 10;
            if (cameraDistance > 500) cameraDistance = 500;
            glutPostRedisplay();
        }

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            lastMouseX = x;
            lastMouseY = y;
        }
    }

    void start(int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(100, 100);
        int id = glutCreateWindow(argv[0]);
        glutSetWindowData(this);
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutMotionFunc(mouseMotion);
        glutMouseFunc(mouseClick);
        glutTimerFunc(33, timer, 1);
        glutMainLoop();
    }
};

// Inicializa as variáveis estáticas da classe Simulation
float Simulation::eyex = 0;
float Simulation::eyey = 60;
float Simulation::eyez = 120;
float Simulation::cameraYaw = 0;
float Simulation::cameraPitch = 0;
float Simulation::cameraDistance = 220;
int Simulation::lastMouseX = 0;
int Simulation::lastMouseY = 0;

int main(int argc, char **argv) {
    Simulation simulation;
    simulation.start(argc, argv);
    return 0;
}
