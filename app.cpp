#include "UI.h"

void extern RunApplication()
{

    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Kinetic");
    SetTargetFPS(60);

    using namespace UI;

    /*
    Create UIComponents and add them to UIComponentList
    */
    Background bg(screenWidth, screenHeight);
    Viewport viewport(150, 50, 600, 450);
    Toolbar toolbar(90, 50, 50, 100);

    /*
    The order in which the components are added to the list matters
    */
    UIComponentList list;
    list.add(&bg);
    list.add(&viewport);
    list.add(&toolbar);

    /*
    Create and add a triangle to the graph
    */
    Polygon t;
    t.addVertex(400.0f, 500.0f);
    t.addVertex(100.0f, 100.0f);
    t.addVertex(200.0f, 40.0f);

    viewport.graph.add(&t);

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
