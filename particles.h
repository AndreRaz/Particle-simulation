#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"

typedef struct {
  Vector2 pos;
  Vector2 vel;
  Vector2 force;
  float mass;
  float charge;
  float radius;
} Particle;

#endif

void apply_force(Particle part[], int n);
void update_particles(Particle part[], int n);
void draw_particles(Particle part[], int n);
void draw_field(Particle part[], int n);
void draw_hist(Particle part[], int n);
void init_particles(Particle part[], int n);
