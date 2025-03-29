/* TODO:
A simple 2d pixel top-down shoot'em up with a very limited color pallete

CURRENTLY WORKING ON: 

    
Planned general:
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
    
    TODO artistical direction edition:
    
    - Find the right color palletes, orrr better yet, automate it!
    - Some pixel effects of destruction and screenshake?
    - -Satisfying- not too irritating sound effects
*/ 

#include <iostream>
#include <vector>
#include "raylib.h"


#define gamearea_square 512
#define topbar_height 64
#define sidebar_width 96

void Calculation();
void Drawing();
void LoadTextures();

const struct Window {
    const char* title = "Galaxory";
    int width = gamearea_square + sidebar_width;
    int height = gamearea_square + topbar_height;
} window;

Image IMAGES[64];
Texture2D TEXTURES[64];
enum TextureEnum
{
    NullTexture = 0,
    PlayerTexture = 10,
    EnemyEyeTexture = 20,
    Enemy2Texture = 21,
    Enemy3Texture = 22,
    TopbarTexture = 30,
    LevelCounterTexture = 31,
    SidebarTexture = 40,
    GameArea1Texture = 50
};
enum bulletType {
    PLAYER,
    ENEMY
};

class StaticSquareArea {
    protected:
        Vector2 position;
        Vector2 size;
    public:
        Vector2 getPosition() {
            return this->position;
        }
        Vector2 getSize() {
            return this->size;
        }
};
class hasTexture {
    protected:
        enum TextureEnum textureID;
    public:
        void setTextureID(enum TextureEnum ID) {
            this->textureID = ID;
        }
        enum TextureEnum getTextureID() {
            return this->textureID;
        }
};
class isAnimated {
    protected:
        int frameCount;
        int frameSpeed;
        int frameCooldown = 0;
        int currentFrame = 0;
        Rectangle currentFraming;
};

class Entity
{
    public:
        Vector2 position;
        Vector2 size;
        Vector2 velocity;
        void move(){
            this->position.x += this->velocity.x;
            this->position.y += this->velocity.y;
        }
        void bounds() {
            if (this->position.x < 0) {
                this->position.x = 0;
                this->velocity.x = 0;
            }
            if (this->position.x > gamearea_square - this->size.x) {
                this->position.x = gamearea_square - this->size.x;
                this->velocity.x = 0;
            }
            if (this->position.y < topbar_height) {
                this->position.y = topbar_height;
                this->velocity.y = 0;
            }
            if (this->position.y > gamearea_square + topbar_height - this->size.y) {
                this->position.y = gamearea_square + topbar_height - this->size.y;
                this->velocity.y = 0;
            }
        }
    private:
        int life = 0;
};
class canShoot
{
    protected:
        int damage = 0;
    public:
        void shoot();
};
class TopBar : public StaticSquareArea, public hasTexture
{
    
    public:
        TopBar()
        {
            position = {0, 0};
            size = {(float)window.width - sidebar_width, topbar_height};
        }
        void setScore(int number) {
            this->score = number;
        }
        int getScore() {
            return this->score;
        }
    private:
        int score = 0;
};
class SideBar : public StaticSquareArea, public hasTexture
{
    public:
        SideBar()
        {
            position = {gamearea_square, topbar_height};
            size = {sidebar_width, gamearea_square};
            setTextureID(SidebarTexture);
        }
        void setLives(int number) {
            this->lives = number;
        }
        void setProgress(int number) {
            this->progress = number;
        }
        void draw()
        {
            DrawTextureV(TEXTURES[this->textureID], this->position, WHITE);
            DrawTextureV(TEXTURES[this->textureID+1], this->position, WHITE);
            DrawTextureV(TEXTURES[this->textureID+2], this->position, WHITE);
        }
    private:
        int lives = 3;
        int progress = 0;
};
class LevelCounter : public StaticSquareArea, public hasTexture
{
    public:
        LevelCounter()
        {
            position = {gamearea_square, 0};
            size = {sidebar_width, topbar_height};
        }
        void setLevel(int number) {
            this->level = number;
        }
    private:
        int level = 1;
};
class GameArea : public StaticSquareArea, public hasTexture
{
    public:
        GameArea()
        {
            position = {0, topbar_height};
            size = {gamearea_square, gamearea_square};
            setTextureID(GameArea1Texture);
        }
};



class Bullet : public Entity, public hasTexture
{
    private:
        Vector2 velocity;
    public:
        Bullet(enum bulletType type)
        {
            setTextureID(NullTexture);
            switch(type) {
                case PLAYER:
                    velocity = {0, -1};
                    break;
                case ENEMY:
                    velocity = {0, 1};
                    break;
            }
            
        }
};

class Player: public Entity, public hasTexture, public canShoot
{
    public:
        Player()
        {
            size = {64, 96};
            position = {(float)gamearea_square/2 - this->size.x/2, (float)window.height - this->size.y*2};
            setTextureID(PlayerTexture);
        }
        void shoot() {
            new Bullet(PLAYER);
        }
        void draw() {
            DrawTextureV(TEXTURES[this->textureID], this->position, RED);
        }
        void control() {
            if (IsKeyDown(KEY_SPACE)) {
                this->shoot();
            }
            if (IsKeyDown(KEY_A)) {
                this->velocity.x += -1.0;
            }
            if (IsKeyDown(KEY_D)) {
                this->velocity.x += 1.0;
            }
            if (IsKeyDown(KEY_W)) {
                this->velocity.y -= 1.0;
            }
            if (IsKeyDown(KEY_S)) {
                this->velocity.y += 1.0;
            }
            if (this->velocity.x > 0) {
                this->velocity.x -= 0.3;
            }
            if (this->velocity.x < 0) {
                this->velocity.x += 0.3;
            }
            if (this->velocity.x < 0.31 && this->velocity.x > -0.31) {
                this->velocity.x = 0;
            }
            if (this->velocity.y > 0) {
                this->velocity.y -= 0.3;
            }
            if (this->velocity.y < 0) {
                this->velocity.y += 0.3;
            }
            if (this->velocity.y < 0.31 && this->velocity.y > -0.31) {
                this->velocity.y = 0;
            }
        }
        
};
class Enemy: public Entity, public hasTexture, public isAnimated
{
    public:
    
        Enemy(float x, float y)
        {
            frameSpeed = 10;
            frameCount = 4;
            this->size = {96, 64};
            currentFraming = {0, 0, this->size.x, this->size.y};
            this->position = {x, y};
            setTextureID(EnemyEyeTexture);
        }
        void draw() {

            this->currentFraming.x = this->size.x*currentFrame;
            DrawTextureRec(TEXTURES[this->textureID], this->currentFraming, this->position, WHITE);
            
            if (this->frameCooldown == this->frameSpeed) {
                if (this->currentFrame == this->frameCount) {
                    this->currentFrame = 0;
                }
                this->currentFrame++;
            }
            if (this->frameCooldown == this->frameSpeed) {
                this->frameCooldown = 0;
            }
            this->frameCooldown++;
            //DrawTextureV(TEXTURES[this->textureID], this->position, WHITE);
        }
    
};

TopBar topbar;
SideBar sidebar;
GameArea gamearea;
LevelCounter levelcounter;
Player player;

std::vector<class Enemy*> enemies
{
    new class Enemy(0, 40),
    new class Enemy(100, 40),
    new class Enemy(200, 40),

};

int main( void )
{

    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(60);
    
    LoadTextures();
    while (!WindowShouldClose())
    {
        Calculation();
        Drawing();
    }
    
    CloseWindow();
    return 0;
}
void LoadTextures()
{
        IMAGES[0] = LoadImage("res/null.png");
        IMAGES[10] = LoadImage("res/player.png");
        IMAGES[20] = LoadImage("res/enemyEye_sheet.png");
        IMAGES[40] = LoadImage("res/sidebar_background.png");
        IMAGES[41] = LoadImage("res/sidebar_progress_background.png");
        IMAGES[42] = LoadImage("res/sidebar_progress_background_display.png");
        IMAGES[50] = LoadImage("res/starsold.png");
        for (int i = 0; i < 64; i++)
        {
            if(IsImageValid(IMAGES[i]))
            TEXTURES[i] = LoadTextureFromImage(IMAGES[i]);
        }
}

void Calculation()
{
    
    
    player.control();
    player.move();
    player.bounds();
    return;
}
void Drawing()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (class Enemy* enemy : enemies) {
        enemy->draw();
    }
    player.draw();
    sidebar.draw();
    
    EndDrawing();
}