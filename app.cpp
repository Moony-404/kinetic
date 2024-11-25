#include "UI.h"

void extern RunApplication()
{

    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Kinetic");
    SetTargetFPS(60);

    using namespace UI;

    /*
    Create a UIComponent and add it to UIComponentList
    */
    Background bg(screenWidth, screenHeight);
    Viewport v(50, 50, 700, 450);

    /*
    The order in which the components are added to the list matters
    */
    UIComponentList list;
    list.add(&bg);
    list.add(&v);

    /*
    Create and add a triangle to the graph
    */
    Polygon t;
    t.addVertex(1000.0f, 1000.0f);
    t.addVertex(100.0f, 100.0f);
    t.addVertex(200.0f, 40.0f);

    v.graph.add(&t);

    Vector2 delta = GetMouseDelta();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        {
            list.handleMouseEvents();
            list.render();
        }

        EndDrawing();
    }
}
