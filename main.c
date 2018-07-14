#include <stdlib.h>
#include "raylib.h"


#define NUM_PARTICLES 60
#define VX_DIVIDER 50

typedef struct particle {
    int x, y;
    double vx, vy;
     struct Color color;
    int radius;
} particle_t;

particle_t particles[NUM_PARTICLES];

void initParticles(int w, int h) {
    int i;
    for (i = 0; i < NUM_PARTICLES; i++) {
        particle_t *p = &particles[i];
        uint g = rand() % 256;
        uint r = g / 2 + rand() % 128;

        p->x = 0;
        p->y = 0;
        p->vx = (rand() % w / VX_DIVIDER) + w / VX_DIVIDER;
        p->vy = (rand() % w / VX_DIVIDER) + w / VX_DIVIDER;
        p->color =  CLITERAL{ r, g, 0, 128 };
        p->radius = (rand() % w / 10) + 10;
    }
}

int main()
{
    int width = 1280;
    int height = 1024;

    initParticles(width, height);

    InitWindow(width, height, "particles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        particle_t *p;
        int i;
        // TODO: Update your variables here

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (i = 0; i < NUM_PARTICLES; i++) {
                p = &particles[i];
                DrawCircle(p->x , p->y, p->radius, p->color);
                p->x += p->vx;
                p->y += p->vy;

                p->vx *= 0.98;
                if (p->vy > 0)
                    p->vy *= 0.97;

                // Gravity
                p->vy -= 0.1;
                // Stop particles leaving the canvas  
                if (p->x < -50)
                    p->x = width + 50;
                if (p->x > width + 50)
                    p->x = -50;

                if (p->y < -50) {
                    p->x = 0;
                    p->y = 0;
                    p->vx = (rand() % width / VX_DIVIDER) + width / VX_DIVIDER;
                    p->vy = (rand() % width / VX_DIVIDER) + width / VX_DIVIDER;
                }
            }
            DrawText(FormatText("%2i FPS", GetFPS()), 0, 0, 20, LIME);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}