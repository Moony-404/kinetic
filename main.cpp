#include "UI.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(screenWidth, screenHeight, "Kinetic");
    SetTargetFPS(60);

    void extern RunApplication();

    RunApplication();
}
