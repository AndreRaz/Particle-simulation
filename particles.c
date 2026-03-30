#include "particles.h"
#include "raylib.h"
#include <math.h>

void init_particles(Particle part[], int n) {
  for (int i = 0; i < n; i++) {
    part[i].pos.x = (float)GetRandomValue(50, 450);
    part[i].pos.y = (float)GetRandomValue(50, 450);
    part[i].vel.x = (float)GetRandomValue(-100, 100);
    part[i].vel.y = (float)GetRandomValue(-100, 100);
    part[i].mass = 1.f;
    part[i].charge = (int)GetRandomValue(0, 1) * 2 - 1;
    part[i].force.x = 0.f;
    part[i].force.y = 0.f;
    part[i].radius = 5.f;
  }
}

// Calculate and apply Coulomb forces between all particle pairs
void apply_force(Particle part[], int n) {
  float ke = 8000.f;

  // Reset forces to zero
  for (int i = 0; i < n; i++) {
    part[i].force.x = 0.0f;
    part[i].force.y = 0.0f;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      // Distance vector between particles
      float dx = part[j].pos.x - part[i].pos.x;
      float dy = part[j].pos.y - part[i].pos.y;
      // Unit vector
      float r = sqrt(dx * dx + dy * dy);
      if (r < 1.0f)
        continue;
      float rx = dx / r;
      float ry = dy / r;

      // Compute Coulomb force magnitude: F = ke * q1 * q2 / r^2
      float F = ke * part[i].charge * part[j].charge / (r * r);
      float Fx = F * rx;
      float Fy = F * ry;

      // Accumulate forces on both particles (Newton's 3rd law)
      part[i].force.x += Fx;
      part[i].force.y += Fy;
      part[j].force.x -= Fx;
      part[j].force.y -= Fy;
    }
  }
}

// Update particle positions and velocities using Euler integration

void update_particles(Particle part[], int n) {
  float dt = GetFrameTime();

  for (int i = 0; i < n; i++) {
    float ax = part[i].force.x / part[i].mass;
    float ay = part[i].force.y / part[i].mass;

    part[i].vel.x += ax * dt;
    part[i].vel.y += ay * dt;

    part[i].pos.x += part[i].vel.x * dt;
    part[i].pos.y += part[i].vel.y * dt;

    if (part[i].pos.x < 0 || part[i].pos.x > 500) {
      part[i].vel.x = -part[i].vel.x;
    }

    if (part[i].pos.y < 0 || part[i].pos.y > 500) {
      part[i].vel.y = -part[i].vel.y;
    }
  }
}

// Draw particles as colored circles (red = positive, blue = negative)

void draw_particles(Particle part[], int n) {
  for (int i = 0; i < n; i++) {
    Color c = (part[i].charge > 0) ? RED : BLUE;
    DrawCircleV(part[i].pos, part[i].radius, c);
  }
}

// Draw electric field vectors on a grid using superposition principle

void draw_field(Particle part[], int n) {
  int grid = 25;
  float ke = 8000.0f;

  for (int x = 0; x < 500; x += grid) {
    for (int y = 0; y < 500; y += grid) {
      float Ex = 0.0f;
      float Ey = 0.0f;

      // Accumulate field contributions from each particle
      for (int i = 0; i < n; i++) {
        float dx = x - part[i].pos.x;
        float dy = y - part[i].pos.y;
        float r = sqrt(dx * dx + dy * dy);

        if (r < 5.0f)
          continue;

        float E = ke * part[i].charge / (r * r);
        Ex += E * (dx / r);
        Ey += E * (dy / r);
      }

      float mag = sqrt(Ex * Ex + Ey * Ey);
      if (mag < 1e-6f)
        continue;
      float len = 10.0f;
      float ex = Ex / mag * len;
      float ey = Ey / mag * len;

      DrawLine(x, y, x + (int)ex, y + (int)ey, Fade(WHITE, 0.4f));
    }
  }
}

void draw_hist(Particle part[], int n) {
  int bins = 20;
  float max_speed = 300.0f;
  int counts[20] = {0};

  for (int i = 0; i < n; i++) {
    float vx = part[i].vel.x;
    float vy = part[i].vel.y;

    float speed = sqrt(vx * vx + vy * vy);

    int bin_index = (int)(speed / max_speed * bins);
    if (bin_index >= bins)
      bin_index = bins - 1;
    counts[bin_index]++;
  }

  int bar_w = 8;
  int max_h = 80;
  int origin_x = 10;
  int origin_y = 490;

  for (int i = 0; i < bins; i++) {
    int bar_h = counts[i] * max_h / n;
    DrawRectangle(origin_x + i * bar_w, origin_y - bar_h, bar_w - 1, bar_h,
                  Fade(GREEN, 0.7f));
  };
}

int main() {
  Particle part[50];

  InitWindow(500, 500, "Particle simulation");
  SetTargetFPS(60);

  init_particles(part, 50);

  while (!WindowShouldClose()) {
    apply_force(part, 50);
    update_particles(part, 50);

    BeginDrawing();
    ClearBackground(BLACK);
    draw_field(part, 50);
    draw_particles(part, 50);
    draw_hist(part, 50);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
