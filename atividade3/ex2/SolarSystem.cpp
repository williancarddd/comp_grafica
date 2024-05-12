#include "SolarSystem.h"
#include <cmath>

CelestialBody::CelestialBody(float r, float red, float green, float blue, float dist) :
    radius(r), distance(dist), angle(0) {
    color[0] = red;
    color[1] = green;
    color[2] = blue;
}

void CelestialBody::setAngle(float a) {
    angle = fmod(a, 360.0f);
}

void CelestialBody::draw() const {
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(radius, 16, 16);
}

void CelestialBody::drawOrbit() const {
    glRotatef(angle, 0, 1, 0);
    glTranslatef(distance, 0, 0);
    draw();
}

void CelestialBody::updateAngle(float increment) {
    setAngle(angle + increment);
}

float CelestialBody::getDistance() const {
    return distance;
}

Moon::Moon() : CelestialBody(1, 0.5f, 0.5f, 0.5f, 8) {}

void Moon::drawOrbit(float earthAngle) const {
    glRotatef(earthAngle, 0, 1, 0);
    glTranslatef(distance, 0, 0);
    CelestialBody::draw();
}

Mercury::Mercury() : CelestialBody(2, 0.7f, 0.7f, 0.7f, 20) {}

Venus::Venus() : CelestialBody(3, 1, 0.5f, 0, 40) {}

Earth::Earth() : CelestialBody(5, 0, 0, 1, 60) {}

void Earth::drawOrbit() const {
    glRotatef(angle, 0, 1, 0);
    glTranslatef(distance, 0, 0);
    CelestialBody::draw();
    glPushMatrix();
    moon.drawOrbit(angle);
    glPopMatrix();
}

void Earth::updateMoon(float increment) {
    moon.updateAngle(increment);
}

Mars::Mars() : CelestialBody(4, 1, 0.2f, 0, 75) {}

JupiterMoon::JupiterMoon(float dist) : CelestialBody(1, 0.5f, 0.5f, 0.5f, dist) {}

void JupiterMoon::drawOrbit(float jupiterAngle) const {
    glRotatef(jupiterAngle, 0, 1, 0);
    glTranslatef(distance, 0, 0);
    CelestialBody::draw();
}

Jupiter::Jupiter() : CelestialBody(9, 0.8f, 0.5f, 0.3f, 100),
                     moon1(15), moon2(20), moon3(25) {}

void Jupiter::drawOrbit() const {
    glRotatef(angle, 0, 1, 0);
    glTranslatef(distance, 0, 0);
    CelestialBody::draw();

    glPushMatrix();
    moon1.drawOrbit(angle);
    glPopMatrix();

    glPushMatrix();
    moon2.drawOrbit(angle * 0.9f); // Ângulo diferente para evitar sobreposição
    glPopMatrix();

    glPushMatrix();
    moon3.drawOrbit(angle * 0.7f);
    glPopMatrix();
}

Saturn::Saturn() : CelestialBody(8, 0.9f, 0.7f, 0.2f, 130) {}

void Saturn::draw() const {
    CelestialBody::draw();

    // Desenha o anel ao redor de Saturno
    glColor3f(0.6f, 0.5f, 0.3f);
    glPushMatrix();
    glRotatef(90, 1, 0, 0); // Posiciona o anel ao redor do equador
    glutSolidTorus(0.2f, 12, 30, 30); // raio interno, raio externo
    glPopMatrix();
}

Uranus::Uranus() : CelestialBody(7, 0.6f, 0.8f, 0.9f, 160) {}

Neptune::Neptune() : CelestialBody(7, 0.2f, 0.4f, 0.8f, 190) {}

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

SolarSystem::SolarSystem() : sun(12, 1, 1, 0, 0) {}

void SolarSystem::draw() const {
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

void SolarSystem::updateAngles() {
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
