#include "raylib.h"
#define fieldSize 10

void drawField();
void generateBombs();
void calculateNumbers();
void resetGame();
void endGame();
void timer();
void playerInput();
void wonOrLoose();
void drawScore();
void mainMenu();
void initGrassTexture();
void initGame();
void initExplodedTexture();

//Textures for Images
Texture2D grassTexture;
Texture2D explodedTexture;

//State of Game
enum {
    PLAYING,
    GAME_OVER,
    MAIN_MENU
} gameState = MAIN_MENU;

//If grass is on field x y then true else false
bool isCovered[fieldSize][fieldSize];
//Is bomb on field x y
bool isBomb[fieldSize][fieldSize];
//What number does the field have
int fieldValue[fieldSize][fieldSize] = {0};

int main(void)
{
    //Windows size
    const int screenWidth = 500;
    const int screenHeight = 500;

    //Init Windows
    InitWindow(screenWidth, screenHeight, "MINESWEEPER");
    //Set Target FPS
    SetTargetFPS(60);

    //Inits all PNGS
    BeginDrawing();
    initGame();
    EndDrawing();

    while (!WindowShouldClose()) {
        BeginDrawing();
        //Set Background to white
        ClearBackground(RAYWHITE);
        //Switch States
        switch (gameState) {
            //Main Menu state
            case MAIN_MENU:
                //Shows main menu
                mainMenu();
                //If space down game starts
                if (IsKeyDown(KEY_SPACE)) {
                    gameState = PLAYING;
                }
                break;
            case PLAYING:
                //Draws all
                drawField();
                break;
            case GAME_OVER:
                //endGame();
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
//Inits all Textures
void initGame() {
    initGrassTexture();
    initExplodedTexture();
}

//Texts for Main menu
void mainMenu() {
    DrawText("Minesweeper", 70, 40, 50, BLACK);
    DrawText("By Raphael Botond Jonas", 100, 100, 20, BLACK);
    DrawText("Press SPACE to start", 50, 200, 30, BLACK);
}

//Init GRASS Texture
void initGrassTexture() {
    Image grass = LoadImage("assets/minesweeper_tiles/masked_tile.png");
    ImageResize(&grass, 50, 50);
    grassTexture = LoadTextureFromImage(grass);
}
//Init Exploded Texture
void initExplodedTexture() {
    Image exploded = LoadImage("assets/minesweeper_tiles/tile_exploded.png");
    ImageResize(&exploded, 50, 50);
    explodedTexture = LoadTextureFromImage(exploded);

}
//Good Looking functions for DrawTexture
void grassField(int x , int y) {
    DrawTexture(grassTexture, x, y, WHITE);
}
//Good Looking functions for DrawTexture
void explodedField(int x , int y) {
    DrawTexture(explodedTexture, x, y, WHITE);
}

//Functions to draw all grass
void drawGrass() {
    grassField(0 , 0);
}
//Functions to draw all bomb under grass
void drawBomb() {
    explodedField(50 , 0);
}
//Functions to draw all numbers under grass
void drawNumber(){}

//Main call for draw fields what calls subfunctions
void drawField() {
    drawGrass();
    drawNumber();
    drawBomb();
}