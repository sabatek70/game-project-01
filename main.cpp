#include <iostream>
#include "raylib.h"

#define gamearea_square 512
#define topbar_height 64
#define sidebar_width 96

void Initialization();
void Deinitialization();
void Calculation();
void Drawing();
void GameLoop();
void LoadLevel();

const struct Window {
    const char* title = "Galaxorg";
    int width = gamearea_square + sidebar_width;
    int height = gamearea_square + topbar_height;
} window;

class SquareArea {
    public:
        Vector2 position;
        Vector2 size;
};
class TopBar : public SquareArea
{
    public:
    TopBar()
    {
        position = {0, 0};
        size = {(float)window.width - sidebar_width, topbar_height};
    }
    void DrawBackground()
    {
        DrawRectangleV(this->position, this->size, GREEN);
    }
};
class SideBar : public SquareArea
{
    public:
    SideBar()
    {
        position = {gamearea_square, topbar_height};
        size = {sidebar_width, gamearea_square};
    }
    void DrawBackground()
    {
        DrawRectangleV(this->position, this->size, BLUE);
    }
};
class GameArea : public SquareArea
{
    public:
    GameArea()
    {
        position = {0, topbar_height};
        size = {gamearea_square, gamearea_square};
    }
    void DrawBackground()
    {
        DrawRectangleV(this->position, this->size, RED);
    }
};
class LevelCounter : public SquareArea
{
    public:
    LevelCounter()
    {
        position = {gamearea_square, 0};
        size = {sidebar_width, topbar_height};
    }
    void DrawBackground()
    {
        DrawRectangleV(this->position, this->size, YELLOW);
    }
};

TopBar topbar;
SideBar sidebar;
GameArea gamearea;
LevelCounter levelcounter;

int main( void )
{
    Initialization();
    GameLoop();
    Deinitialization();
    
    return 0;
}
void GameLoop()
{
    while (!WindowShouldClose())
    {
        Calculation();
        Drawing();
    }
}
void Initialization()
{
    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(60);
    
}
void Deinitialization()
{
    CloseWindow();
}
void Calculation()
{
    return;
}
void Drawing()
{
    BeginDrawing();
    
    ClearBackground(BLACK);
    
    topbar.DrawBackground();
    sidebar.DrawBackground();
    gamearea.DrawBackground();
    levelcounter.DrawBackground();
    
    EndDrawing();
}