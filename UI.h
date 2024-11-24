#include <iostream>
#include <vector>
#include <raylib.h>
#include <raymath.h>

namespace UI
{
    extern Color BGColor;
    extern Color CanvasColor;
    extern Color LineColor;

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

    class Box : public UIComponent
    {
    public:
        Box(Vector2 p, float w, float h) : UIComponent(p, w, h)
        {
        }

        void render() override
        {
            DrawRectangleLines(position.x, position.y, width, height, LineColor);
        }
    };

    /*
    An abstract base class for all types of objects that can be
    drawn on a graph
    */
    class AbstractShape
    {
    public:
        virtual void render() = 0;
    };

    /*
    A class representing an infinte graph
    */
    class Graph
    {
    protected:
        std::vector<AbstractShape *> objects;

    public:
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

        /*
        Render all the shapes present in the graph
        */
        void render()
        {
            for (AbstractShape *s : objects)
            {
                s->render();
            }
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
        UI::Graph graph;

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

    public:
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

            // Render all the objects in the graph
            graph.render();
        }
    };

}
