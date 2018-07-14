#include "raylib.h"

int main()
{
    int screenWidth = 1280;
    int screenHeight = 1024;

    InitWindow(screenWidth, screenHeight, "particles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // TODO: Update your variables here

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircle(screenWidth/2, screenHeight / 2, screenHeight / 2, DARKBLUE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}