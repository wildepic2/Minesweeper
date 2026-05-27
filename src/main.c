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

enum {
    PLAYING,
    GAME_OVER,
    MAIN_MENU
} gameState = MAIN_MENU;

bool isCovered[fieldSize][fieldSize];
bool isBomb[fieldSize][fieldSize];
int fieldValue[fieldSize][fieldSize] = {0};
bool init[1] = {false};

int main(void)
{
    const int screenWidth = 500;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "MINESWEEPER");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (gameState) {
            case MAIN_MENU:
                mainMenu();
                if (IsKeyDown(KEY_SPACE)) {
                    gameState = PLAYING;
                }
                break;
            case PLAYING:
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

void mainMenu() {
    DrawText("Minesweeper", 70, 40, 50, BLACK);
    DrawText("By Raphael Botond Jonas", 100, 100, 20, BLACK);
    DrawText("Press SPACE to start", 50, 200, 30, BLACK);
}

void grassField(int x , int y) {
    Image grass = LoadImage("assets/minesweeper_tiles/masked_tile.png");
    ImageResize(&grass, 50, 50);
    Texture2D texture = LoadTextureFromImage(grass);

    DrawTexture(texture, x, y, WHITE);
}

void drawGrass() {
 grassField(0 , 0);
}
void drawBomb(){}
void drawNumber(){}
void drawLines(){}

void drawField() {
    drawGrass();
    drawNumber();
    drawBomb();
    drawLines();
}