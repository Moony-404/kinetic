#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>

namespace UI
{
    extern Color BGColor;
    extern Color CanvasColor;
    extern Color LineColor;

    /*
    A Base class for all the UI elements.
    Elements like buttons, labels, viewport, etc inherit from this class
    */
    class UIComponent
    {

    protected:
        Vector2 position;
        float width;
        float height;

    public:
        UIComponent(Vector2 p, float w, float h)
        {
            position = p;
            width = w;
            height = h;
        }

        virtual void render()
        {
            std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
            std::cout << "width: " << width << '\n';
            std::cout << "height: " << height << '\n';
        };
    };

    /*
    An abstract base class for all types of objects that can be drawn on a graph
    */
    class AbstractShape
    {
    public:
        virtual void render(float delx, float dely) = 0;
    };

    class Polygon : public AbstractShape
    {
    protected:
        std::vector<Vector2> vertices;

    public:
        Polygon()
        {
            vertices = {};
        }
        void addVertex(Vector2 v)
        {
            vertices.push_back(v);
        }

        void addVertex(float x, float y)
        {
            vertices.push_back((Vector2){x, y});
        }

        /*
        Renders the polygon to the viewport
        */
        void render(float originx, float originy) override
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
    };

    /*
    A class representing an infinte graph
    */
    class Graph
    {
    public:
        std::vector<AbstractShape *> objects;

        Graph()
        {
            objects = {};
        }
        void add(AbstractShape *s)
        {
            objects.push_back(s);
        }

        void add(AbstractShape **s, int size)
        {
            for (int i = 0; i < size; i++)
                objects.push_back(s[i]);
        }

        void remove(int index)
        {
            objects.erase(objects.begin() + index);
        }

        void remove(int first, int last)
        {
            objects.erase(objects.begin() + first, objects.begin() + last);
        }
    };

    class Viewport : public UIComponent
    {
    private:
        Color BGColor = {59, 66, 82, 255};
        Color BorderColor = {136, 191, 208, 255};
        Color GridColor = ColorAlpha(BorderColor, 0.35f);
        float gridSpace = 20.0f;

    protected:
        Vector2 graphPosition;

        void renderGridlines()
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

        void renderGraphObjects()
        {
            for (AbstractShape *s : graph.objects)
                s->render(position.x + graphPosition.x, position.y + graphPosition.y);
        }

    public:
        UI::Graph graph;

        Viewport(Vector2 p, float w, float h) : UIComponent(p, w, h)
        {
            graphPosition = (Vector2){w / 2, h / 2};
            graph = Graph();
        }

        void render() override
        {
            Rectangle bounds = {position.x, position.y, width, height};
            DrawRectangleRec(bounds, BGColor);
            DrawRectangleLinesEx(bounds, 3.0f, BorderColor);
            renderGridlines();
            renderGraphObjects();
        }
    };

}
