#include "particles.h"
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

unsigned int particles_per_row = PARTICLES_PER_ROW;
unsigned int particles_per_col = PARTICLES_PER_COL;

particle particles[NUM_PARTICLES];

void initParticles(int w, int h) {
    int i;
    int xpart = w / PARTICLES_PER_ROW;
    int ypart = h / PARTICLES_PER_COL;
    for (i = 0; i < NUM_PARTICLES; i++) {
        particle *p = &particles[i];
        uint g = rand() % 256;
        uint r = g / 2 + rand() % 128;

        p->x = xpart * (i % PARTICLES_PER_ROW) + xpart / 2;
        p->y = ypart * (i / PARTICLES_PER_ROW) + xpart / 2;
        p->color =  CLITERAL{ r, g, 0, 192 };
        p->radius = MIN(xpart / 2, ypart / 2);
    }
}