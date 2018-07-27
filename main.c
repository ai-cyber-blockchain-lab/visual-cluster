#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <raylib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define PORT 8000

#define PARTICLES_PER_ROW 8
#define PARTICLES_PER_COL 6
#define NUM_PARTICLES PARTICLES_PER_ROW * PARTICLES_PER_COL
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

int request(void *cls, struct MHD_Connection *connection,
            const char *url,
            const char *method,
            const char *version,
            const char *upload_data,
            size_t *upload_data_size, void **con_cls)
{
    struct MHD_Response *response;
    const char page[64];
    int ret;

    if (strncmp(method, "GET", 4) == 0) {
        snprintf(page, 64, "{rows:%d, cols:%d}", PARTICLES_PER_ROW,  PARTICLES_PER_COL);
        response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    } else {
        response = MHD_create_response_from_buffer(0, (void *) page, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 404, response);
        MHD_destroy_response(response);
    }

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;
    int width = 1280;
    int height = 1024;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &request, NULL, MHD_OPTION_END);

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