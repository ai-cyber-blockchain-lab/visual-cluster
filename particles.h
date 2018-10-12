#ifndef PARTICLES_H
#define PARTICLES_H

#include <raylib.h>

#define PARTICLES_PER_ROW 8
#define PARTICLES_PER_COL 6
#define NUM_PARTICLES PARTICLES_PER_ROW * PARTICLES_PER_COL

unsigned int particles_per_row;
unsigned int particles_per_col;

typedef struct particle {
    int x, y;
    double vx, vy;
    struct Color color;
    int radius;
} particle;

particle particles[NUM_PARTICLES];

void initParticles(int w, int h);

#endif /* PARTICLES_H */