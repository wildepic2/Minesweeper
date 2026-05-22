#include "raylib.h"

void drawField();
void generateBomb();
void calculateNumbers();
void resetGame();
void endGame();
void timer();
void playerInput();
void wonOrLoose();
void drawScore();
void mainMenu();



int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Changeme!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 350, 200, 20, BLACK);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
    //ka
}
