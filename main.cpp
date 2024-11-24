#include "UI.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Kinetic");
    SetTargetFPS(60);

    UI::Viewport v((Vector2){50, 50}, 700, 450);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        {
            ClearBackground(UI::BGColor);
            v.render();
        }

        EndDrawing();
    }
}
