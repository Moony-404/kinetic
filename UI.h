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

        virtual void render() = 0;
    };

    /*
    A class to contain all the UIComponents needed in an application.
    */
    class UIComponentList
    {
    protected:
        /*
        The `components` attributes contain pointers to all the UIComponents in the order they
        should be drawn onto the screen.
        */
        std::vector<UIComponent *> components = {};

    public:
        void setList(std::vector<UIComponent *> c);
        void add(UIComponent *c);
        void render();
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
        Polygon();
        void addVertex(Vector2);
        void addVertex(float x, float y);
        void render(float delx, float dely) override;
    };

    /*
    A class representing an infinte graph
    */
    class Graph
    {
    public:
        std::vector<AbstractShape *> objects;
        Graph();
        void add(AbstractShape *s);
        void add(AbstractShape **s, int size);
        void remove(int index);
        void remove(int first, int last);
    };

    /*
    Viewport class, derived from UIComponent
    */
    class Viewport : public UIComponent
    {
    private:
        Color BGColor = {59, 66, 82, 255};
        Color BorderColor = {136, 191, 208, 255};
        Color GridColor = ColorAlpha(BorderColor, 0.35f);
        float gridSpace = 20.0f;

    protected:
        Vector2 graphPosition;
        void renderGridlines();
        void renderGraphObjects();

    public:
        UI::Graph graph;
        Viewport(Vector2 p, float w, float h);
        void render() override;
        void setGridSpace(float s);
    };
}
