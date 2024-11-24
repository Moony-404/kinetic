#include "UI.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Kinetic");
    SetTargetFPS(60);

    UI::Viewport v((Vector2){50, 50}, 700, 450);
    /*
    Create and add a triangle to the graph
    */
    UI::Polygon t;
    t.addVertex(20.0f, 20.0f);
    t.addVertex(100.0f, 100.0f);
    t.addVertex(200.0f, 40.0f);

    v.graph.add(&t);

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
