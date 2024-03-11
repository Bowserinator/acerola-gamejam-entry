#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "../utils/types/vector.h"
#include <vector>

using namespace bowser_util;

class ParticleManager;

class Particle {
public:
    Particle() {}
    Particle(float size, Color color, vec2 pos, vec2 vel, float gravity, float life):
        size(size), color(color), pos(pos), vel(vel), gravity(gravity), life(life) {};

    void tick();
    void draw();
private:
    friend ParticleManager;

    float size = 1.0f;
    float gravity = 0.1f;
    float life = 100.0f;
    Color color = WHITE;
    vec2 pos = vec2(0.0);
    vec2 vel = vec2(0.0);
};

class ParticleManager {
public:
    std::vector<Particle> particles;

    void tick();
    void draw();
};

#endif