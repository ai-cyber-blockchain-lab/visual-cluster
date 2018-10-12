#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <raylib.h>
#include <string.h>

#include "network.h"
#include "particles.h"

#define PORT 8000

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
        particle *p;
        int i;

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