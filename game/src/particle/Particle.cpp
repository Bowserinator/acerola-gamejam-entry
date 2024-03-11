#include "Particle.h"

void Particle::tick() {
    vel.y += gravity;
    pos += vel;
    vel.x *= 0.95;
    life -= 1.0f;
}

void Particle::draw() {
    DrawRectangle(pos.x, pos.y, size, size, color);
}

void ParticleManager::tick() {
    bool kill = false;
    for (auto &part: particles) {
        part.tick();
        if (part.life < 0.0f) kill = true;
    }

    if (kill) {
        std::vector<Particle> result;
        std::copy_if(particles.begin(), particles.end(), back_inserter(result), [](const Particle &part) { return part.life >= 0.0f; });
        particles = result;
    }
}

void ParticleManager::draw() {
    for (auto &part: particles)
        part.draw();
}