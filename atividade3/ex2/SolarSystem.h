#include <GL/freeglut.h>

class CelestialBody {
protected:
    float radius;
    float color[3];
    float angle;
    float distance;

public:
    CelestialBody(float r, float red, float green, float blue, float dist);
    void setAngle(float a);
    virtual void draw() const;
    virtual void drawOrbit() const;
    virtual void updateAngle(float increment);
    float getDistance() const;
};

class Moon : public CelestialBody {
public:
    Moon();
    void drawOrbit(float earthAngle) const;
};

class Mercury : public CelestialBody {
public:
    Mercury();
};

class Venus : public CelestialBody {
public:
    Venus();
};

class Earth : public CelestialBody {
private:
    Moon moon;

public:
    Earth();
    void drawOrbit() const override;
    void updateMoon(float increment);
};

class Mars : public CelestialBody {
public:
    Mars();
};

class JupiterMoon : public CelestialBody {
public:
    JupiterMoon(float dist);
    void drawOrbit(float jupiterAngle) const;
};

class Jupiter : public CelestialBody {
private:
    JupiterMoon moon1;
    JupiterMoon moon2;
    JupiterMoon moon3;

public:
    Jupiter();
    void drawOrbit() const override;
};

class Saturn : public CelestialBody {
public:
    Saturn();
    void draw() const override;
};

class Uranus : public CelestialBody {
public:
    Uranus();
};

class Neptune : public CelestialBody {
public:
    Neptune();
};

void drawOrbit(float radius);

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
    SolarSystem();
    void draw() const;
    void updateAngles();
};
