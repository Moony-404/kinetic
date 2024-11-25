#include "UI.h"

void extern RunApplication()
{
    using namespace UI;

    /*
    Create a UIComponent and add it to UIComponentList
    */
    Viewport v((Vector2){50, 50}, 700, 450);
    UIComponentList list;
    list.add(&v);

    /*
    Create and add a triangle to the graph
    */
    Polygon t;
    t.addVertex(20.0f, 20.0f);
    t.addVertex(100.0f, 100.0f);
    t.addVertex(200.0f, 40.0f);

    v.graph.add(&t);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        {
            ClearBackground(UI::BGColor);
            list.render();
        }

        EndDrawing();
    }
}
