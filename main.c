#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <raylib.h>
#include <string.h>

#include "network.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define PORT 8000

#define PARTICLES_PER_ROW 8
#define PARTICLES_PER_COL 6
#define NUM_PARTICLES PARTICLES_PER_ROW * PARTICLES_PER_COL
#define VX_DIVIDER 50


unsigned int particles_per_row = PARTICLES_PER_ROW;
unsigned int particles_per_col = PARTICLES_PER_COL;

typedef struct particle {
    int x, y;
    double vx, vy;
    struct Color color;
    int radius;
} particle_t;

particle_t particles[NUM_PARTICLES];

void initParticles(int w, int h) {
    int i;
    int xpart = w / PARTICLES_PER_ROW;
    int ypart = h / PARTICLES_PER_COL;
    for (i = 0; i < NUM_PARTICLES; i++) {
        particle_t *p = &particles[i];
        uint g = rand() % 256;
        uint r = g / 2 + rand() % 128;

        p->x = xpart * (i % PARTICLES_PER_ROW) + xpart / 2;
        p->y = ypart * (i / PARTICLES_PER_ROW) + xpart / 2;
        p->color =  CLITERAL{ r, g, 0, 192 };
        p->radius = MIN(xpart / 2, ypart / 2);
    }
}


int main() {
    struct MHD_Daemon *daemon;
    int width = 1280;
    int height = 1024;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &request, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              completed, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        fprintf(stderr, "startup of webserver failed on port %d\n", PORT);
        return 1;
    }

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
            }
            DrawText(FormatText("%2i FPS", GetFPS()), 0, 0, 20, LIME);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}