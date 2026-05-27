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
                mainMenu();
                if (IsKeyDown(KEY_ENTER)) {
                    gameState = PLAYING;
                }
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

void mainMenu() {
    DrawText("Minesweeper", 70, 40, 50, BLACK);
    DrawText("By Raphael Botond Jonas", 100, 100, 20, BLACK);
    DrawText("Press ENTER to start", 50, 200, 30, BLACK);
}

void drawField() {

}