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
int fieldValue[fieldSize][fieldSize] = {0};

int main(void)
{
    const int screenWidth = 450;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MINESWEEPER");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (gameState) {
            case MAIN_MENU:
                //mainMenu();
                break;
            case PLAYING:

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
