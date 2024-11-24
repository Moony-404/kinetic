
#include <raylib.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Kinetic");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        {
            ClearBackground(RAYWHITE);
        }

        EndDrawing();
    }
}
