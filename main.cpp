/* TODO:
A simple 2d pixel top-down shoot'em up with a very limited color pallete

CURRENTLY WORKING ON: 
    Figuring out a way to make the systems not to be too over-engineered, just work,
    but still be open enough for more functions lol I should probably just make it work
    and think later... But thinking it through now will save me a lot of reworking later too
    [...] I better figure it out!

Planned general:
    - AN EPIC MENU with a HIGHSCORE!!!!
    sidebar:
    - simple life counter, ship images basically
    - a vertical level progression bar
    topbar:
    - score counter
    levelcounter:
    - ditto
    gamearea:
    - a few backgrounds
    - camera2D implementation for parallax & different angles
    enemies:
    - different types of enemies with distinct patterns of attacks and movement
    player:
    - different ships? with different attacks?
    
    TODO artistical direction edition:
    - Make Backgrounds for topbar, sidebar and levelcounter areas * implement them
    - Make Textures for the Player and Enemies
    - Make a -simple- fancy font
    - Design a title for the MENU
    - Come up with a better game name than whats coded in right now...
    - Find the right color palletes, orrr better yet, automate it!
    - Some pixel effects of destruction and screenshake?
    - -Satisfying- not too irritating sound effects
*/ 

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
    const char* title = "Galaxory";
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
class Entity
{
    public:
        Vector2 position;
        Rectangle Texture;
    
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