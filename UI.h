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
    Need to declare these classes here or else the compiler would yell at you
    */
    class UIComponent;
    class UIComponentList;

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
        UIComponent(float x, float y, float w, float h)
        {
            position = (Vector2){x, y};
            width = w;
            height = h;
        }

        virtual void render() = 0;
        virtual void handleMouseEvent(UIComponentList *UIList) {}
        virtual bool isPointInside(Vector2 p)
        {
            if (p.x > position.x + width || p.x < position.x)
                return false;
            if (p.y > position.y + height || p.y < position.y)
                return false;

            return true;
        }
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
        UIComponent *selectedComponent = NULL;
        UIComponent *activeComponent;
        void setActiveComponent();

    public:
        void setSelectedComponent(UIComponent *c);
        bool isSelectedComponent(UIComponent *c);
        void clearSelectedComponent();
        void setList(std::vector<UIComponent *> c);
        void add(UIComponent *c);
        void render();
        void handleMouseEvents();
    };

    /*
    An abstract base class for all types of objects that can be drawn on a graph
    */
    class AbstractShape
    {
    public:
        virtual void render(float graphPositionX, float graphPositionY) = 0;
        virtual bool isShapeVisible(Vector2 vPosition, Vector2 graphPosition, float width, float height) = 0;
    };

    class Polygon : public AbstractShape
    {
    protected:
        std::vector<Vector2> vertices;

    public:
        Polygon();
        void addVertex(Vector2);
        void addVertex(float x, float y);
        bool isShapeVisible(Vector2 vPosition, Vector2 graphPosition, float width, float height) override;
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
        /*
        A hack to keep objects in the viewport from spilling into the rest of the window.
        Just a temporary solution. It has got a bunch of magic numbers which is totally not okay.
        It works fine as long as we don't resize the window
        */
        void renderCover();

    public:
        /*
        graph attribute stores all the objects to be drawn on the viewport
        */
        UI::Graph graph;
        Viewport(float x, float y, float w, float h);
        void render() override;
        void handleMouseEvent(UIComponentList *UIList) override;
        void setGridSpace(float s);
        /*
        Move the graph's position by mouseDelta (Vector2)
        */
        void pan(Vector2 mouseDelta);
    };

    class Background : public UIComponent
    {
    private:
        Color color = {38, 43, 54, 255};

    public:
        Background(float width, float height) : UIComponent(0, 0, width, height) {}
        void render() override;
    };

    /*
    Toolbar class, derived from UIComponent
    */
    class Toolbar : public UIComponent
    {
    private:
        Color BGColor = {59, 66, 82, 255};
        Color BorderColor = {136, 191, 208, 255};
        int iconSize = 20;
        int toolHovered = -1;

    public:
        Toolbar(float x, float y, float width, float height) : UIComponent(x, y, width, height) {}
        void move(Vector2 mouseDelta);
        void render() override;
        void handleMouseEvent(UIComponentList *UIList) override;
    };
}
