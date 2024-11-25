#include "UI.h"

Color UI::BGColor = {46, 52, 64, 255};
Color UI::CanvasColor = {59, 66, 82, 255};
Color UI::LineColor = {136, 191, 208, 255};

/*
Definitions of UI::Polygon methods
*/

UI::Polygon::Polygon()
{
    vertices = {};
}

void UI::Polygon::addVertex(Vector2 v)
{
    vertices.push_back(v);
}

void UI::Polygon::addVertex(float x, float y)
{
    vertices.push_back((Vector2){x, y});
}

// Renders the polygon to the viewport
void UI::Polygon::render(float originx, float originy)
{

    for (Vector2 p : vertices)
        DrawCircle(p.x + originx, p.y + originy, 3.0f, LineColor);

    Vector2 start, end;

    std::vector<Vector2>::iterator it;
    for (it = vertices.begin(); it < vertices.end() - 1; ++it)
    {
        start = (Vector2){originx + it->x, originy + it->y};
        end = (Vector2){originx + (it + 1)->x, originy + (it + 1)->y};
        DrawLineEx(start, end, 2.0f, LineColor);
    }

    start = (Vector2){originx + it->x, originy + it->y};
    end = (Vector2){originx + vertices.begin()->x, originy + vertices.begin()->x};
    DrawLineEx(start, end, 2.0f, LineColor);
}

/*
Definitions of UI::Graph methods
*/

UI::Graph::Graph()
{
    objects = {};
}

void UI::Graph::add(AbstractShape *s)
{
    objects.push_back(s);
}

void UI::Graph::add(AbstractShape **s, int size)
{
    for (int i = 0; i < size; i++)
        objects.push_back(s[i]);
}

void UI::Graph::remove(int index)
{
    objects.erase(objects.begin() + index);
}

void UI::Graph::remove(int first, int last)
{
    objects.erase(objects.begin() + first, objects.begin() + last);
}

/*
Definitions of UI::Viewport method
*/

UI::Viewport::Viewport(Vector2 p, float w, float h) : UIComponent(p, w, h)
{
    graphPosition = (Vector2){w / 2, h / 2};
    graph = Graph();
}

void UI::Viewport::render()
{
    Rectangle bounds = {position.x, position.y, width, height};
    DrawRectangleRec(bounds, BGColor);
    DrawRectangleLinesEx(bounds, 3.0f, BorderColor);
    renderGridlines();
    renderGraphObjects();
}

void UI::Viewport::setGridSpace(float s)
{
    gridSpace = s;
}

void UI::Viewport::renderGridlines()
{
    if (graphPosition.y > 0.0f && graphPosition.y < height)
        DrawLineEx(
            Vector2Add(position, (Vector2){0, graphPosition.y}),
            Vector2Add(position, (Vector2){width, graphPosition.y}),
            2.0f,
            BorderColor);

    if (graphPosition.x > 0.0f && graphPosition.x < width)
        DrawLineEx(
            Vector2Add(position, (Vector2){graphPosition.x, 0}),
            Vector2Add(position, (Vector2){graphPosition.x, height}),
            2.0f,
            BorderColor);

    float gridx = (int)graphPosition.x % (int)gridSpace;
    gridx = gridx < 0.0f ? gridx + gridSpace : gridx;

    while (gridx < width)
    {
        DrawLineEx(
            Vector2Add(position, (Vector2){gridx, 0}),
            Vector2Add(position, (Vector2){gridx, height}),
            1.0f,
            GridColor);

        gridx += gridSpace;
    }

    float gridy = (int)graphPosition.y % (int)gridSpace;
    gridy = gridy < 0.0f ? gridy + gridSpace : gridy;

    while (gridy < height)
    {
        DrawLineEx(
            Vector2Add(position, (Vector2){0, gridy}),
            Vector2Add(position, (Vector2){width, gridy}),
            1.0f,
            GridColor);

        gridy += gridSpace;
    }
}

void UI::Viewport::renderGraphObjects()
{
    for (AbstractShape *s : graph.objects)
        s->render(position.x + graphPosition.x, position.y + graphPosition.y);
}
