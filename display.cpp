#include "UI.h"

Color UI::BGColor = {46, 52, 64, 255};
Color UI::CanvasColor = {59, 66, 82, 255};
Color UI::LineColor = {136, 191, 208, 255};

/*
Implementation of UI::Polygon methods
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

/*
This function is total BS. The problem of visibility of a polygon require a collision test.
Specifically, we need to test if the given polygon (simple or self-intersecting) overlaps with the
Viewport window. If it does, then we render it else we don't.

This problem is made is made particularily hard because the polygon can be anything and there is no cheap,
memory effiecient test to check for its visibility. One approach would be to triangulate the polygon and
then check the visiblility of those triangles. If any one of the triangles is visible then the shape must
be atleast partially visible and we must render it.

*/

bool UI::Polygon::isShapeVisible(Vector2 vPosition, Vector2 graphPosition, float width, float height) { return true; }

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
    end = (Vector2){originx + vertices.begin()->x, originy + vertices.begin()->y};
    DrawLineEx(start, end, 2.0f, LineColor);
}

/*
Implementation of UI::Graph methods
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
Implementation of UI::Viewport method
*/

UI::Viewport::Viewport(float x, float y, float w, float h) : UIComponent(x, y, w, h)
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
    renderCover();
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

void UI::Viewport::renderCover()
{
    Color c = {38, 43, 54, 255};
    DrawRectangle(0, 0, position.x, position.y + height + 100, c);
    DrawRectangle(position.x, 0, width, position.y, c);
    DrawRectangle(position.x, position.y + height, width, 100, c);
    DrawRectangle(position.x + width, 0, 100, position.y + height + 100, c);
}

void UI::Viewport::handleMouseEvent(UIComponentList *UIList)
{
    if (IsKeyDown(KEY_SPACE))
    {
        pan(GetMouseDelta());
    }
}

void UI::Viewport::pan(Vector2 mouseDelta)
{
    graphPosition = Vector2Add(graphPosition, mouseDelta);
}

/*
Implementation of UI::UIComponentList methods
*/

void UI::UIComponentList::setList(std::vector<UIComponent *> c)
{
    components = c;
}

void UI::UIComponentList::add(UIComponent *c)
{
    components.push_back(c);
}

void UI::UIComponentList::render()
{
    for (auto c : components)
        c->render();
}

void UI::UIComponentList::setActiveComponent()
{
    Vector2 point = GetMousePosition();
    // We iterate through the list of components in the reverse order
    for (int i = components.size() - 1; i > -1; --i)
    {
        if (components[i]->isPointInside(point))
        {
            activeComponent = components[i];
            break;
        }
    }
}

void UI::UIComponentList::setSelectedComponent(UIComponent *c)
{
    selectedComponent = c;
}

bool UI::UIComponentList::isSelectedComponent(UIComponent *c)
{
    return (c == selectedComponent ? true : false);
}

void UI::UIComponentList::clearSelectedComponent()
{
    selectedComponent = NULL;
}

void UI::UIComponentList::handleMouseEvents()
{

    /*
    There is a order in which the UIComponentList handles mouse events.
    If there is a selected component then, UIComponentList prioritizes it,
    else it delegates the handling of mouse event to the active component
    */
    if (selectedComponent != NULL)
    {
        selectedComponent->handleMouseEvent(this);
    }
    else
    {
        setActiveComponent();
        activeComponent->handleMouseEvent(this);
    }
};

/*
Implementation of UI::Background methods
*/

void UI::Background::render()
{
    DrawRectangle(position.x, position.y, width, height, color);
}

/*
Implementation of UI::Toolbar methods
*/

void UI::Toolbar::render()
{
    DrawRectangle(position.x, position.y, width, height, BGColor);
    DrawRectangleLines(position.x, position.y, width, height, BorderColor);
}

void UI::Toolbar::handleMouseEvent(UIComponentList *UIList)
{
    if (IsKeyDown(KEY_SPACE) && !UIList->isSelectedComponent(this))
    {
        UIList->setSelectedComponent(this);
        printf("The Toolbar is selected.\n");
        move(GetMouseDelta());
    }
    else if (IsKeyUp(KEY_SPACE) && UIList->isSelectedComponent(this))
        UIList->clearSelectedComponent();

    else if (IsKeyDown(KEY_SPACE))
        move(GetMouseDelta());
}

void UI::Toolbar::move(Vector2 mouseDelta)
{
    position = Vector2Add(position, mouseDelta);
}
