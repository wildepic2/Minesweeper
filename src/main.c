#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#define fieldSize 10
//Defines how many bombs they are maximal in other words every Bomb has one flag
#define maxFlags 10

//Function to Draw Fields
void drawField();

//Function to Generate Random bombs
void generateBombs();

//Function to Make the numbers for the fields
void calculateNumbers();

//Functions to Reset the game
void resetGame();

//Endmenu
void endGame();

//Function for Player Input
void playerInput();

//Check If you won or lost
void wonOrLoose();

//startmenu
void mainMenu();

//Init Functions
void initGrassTexture();

void initGame();

void initExplodedTexture();

void initNumber0Texture();

void initNumber1Texture();

void initNumber2Texture();

void initNumber3Texture();

void initNumber4Texture();

void initNumber5Texture();

void initFlagTexture();

void resetGrass();

//Funnktion to draw grass
void drawGrass();

//Textures for Images
Texture2D grassTexture;
Texture2D explodedTexture;
Texture2D number0;
Texture2D number1;
Texture2D number2;
Texture2D number3;
Texture2D number4;
Texture2D number5;
Texture2D flag;

//Last clicked position for all placement
int lastClickedX;
int lastClickedY;
//Counts how many flags are available
int flagsLeft = maxFlags;

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
//Is flag on field x y
bool isFlag[fieldSize][fieldSize];
//What number does the field have
int fieldValue[fieldSize][fieldSize] = {0};

int main(void) {
    //Makes all covered in grass
    resetGrass();
    generateBombs();
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
                //Player Input function
                //Also it needs to be before draw field because it needs to check if you clicked on a bomb or not and show if its an bomb
                playerInput();
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
    initNumber0Texture();
    initNumber1Texture();
    initNumber2Texture();
    initNumber3Texture();
    initNumber4Texture();
    initNumber5Texture();
    initFlagTexture();
}

//Covers all with grass for every new round
void resetGrass() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            isCovered[i][j] = true;
        }
    }
}

//Texts for Main menu
void mainMenu() {
    drawGrass();
    DrawText("Minesweeper", 80, 40, 50, BLACK);
    DrawText("By Raphael Botond Jonas", 110, 100, 20, BLACK);
    DrawText("Press SPACE to start", 10, 200, 25, BLACK);
    DrawText("Press Left Mouse Button to Uncover", 10, 230, 25, BLACK);
    DrawText("Press Right Mouse Button to Flag", 10, 260, 25, BLACK);
    DrawText("FIND THE 10 BOMBS", 90, 310, 25, RED);
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

//Init Number 0 Texture
void initNumber0Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile.png");
    ImageResize(&field, 50, 50);
    number0 = LoadTextureFromImage(field);
}

//Init Number 1 Texture
void initNumber1Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile_1.png");
    ImageResize(&field, 50, 50);
    number1 = LoadTextureFromImage(field);
}

//Init Number 2 Texture
void initNumber2Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile_2.png");
    ImageResize(&field, 50, 50);
    number2 = LoadTextureFromImage(field);
}

//Init Number 3 Texture
void initNumber3Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile_3.png");
    ImageResize(&field, 50, 50);
    number3 = LoadTextureFromImage(field);
}

//Init Number 4 Texture
void initNumber4Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile_4.png");
    ImageResize(&field, 50, 50);
    number4 = LoadTextureFromImage(field);
}

//Init Number 5 Texture
void initNumber5Texture() {
    Image field = LoadImage("assets/minesweeper_tiles/revealed_tile_5.png");
    ImageResize(&field, 50, 50);
    number5 = LoadTextureFromImage(field);
}

void initFlagTexture() {
    Image field = LoadImage("assets/minesweeper_tiles/masked_tile_flag_blue.png");
    ImageResize(&field, 50, 50);
    flag = LoadTextureFromImage(field);
}

//Good Looking functions for DrawTexture
void grassField(int x, int y) {
    DrawTexture(grassTexture, x, y, WHITE);
}

//Good Looking functions for DrawTexture
void explodedField(int x, int y) {
    DrawTexture(explodedTexture, x, y, WHITE);
}

//Good Looking functions for DrawTexture
void flagField(int x, int y) {
    DrawTexture(flag, x, y, WHITE);
}

//Shows the correct number under grass
void numberField(int x, int y, int number) {
    if (number == 1) {
        DrawTexture(number1, x, y, WHITE);
    } else if (number == 2) {
        DrawTexture(number2, x, y, WHITE);
    } else if (number == 3) {
        DrawTexture(number3, x, y, WHITE);
    } else if (number == 4) {
        DrawTexture(number4, x, y, WHITE);
    } else if (number == 5) {
        DrawTexture(number5, x, y, WHITE);
    } else {
        DrawTexture(number0, x, y, WHITE);
    }
}

//Functions to draw all grass
void drawGrass() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            if (isCovered[i][j] == true) {
                grassField(i * 50, j * 50);
            }
        }
    }
}

//Functions to draw all bomb under grass
void drawBomb() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            if (isBomb[i][j] == true && isCovered[i][j] == false) {
                explodedField(i * 50, j * 50);
            }
        }
    }
}

//Functions to draw all numbers under grass
void drawNumber() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            if (isCovered[i][j] == false && isBomb[i][j] == false) {
                numberField(i * 50, j * 50, fieldValue[i][j]);
            }
        }
    }
}

//Function to Draw all flags
void drawFlag() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            if (isFlag[i][j] == true) {
                flagField(i * 50, j * 50);
            }
        }
    }
}

//Main call for draw fields what calls subfunctions
void drawField() {
    drawGrass();
    drawBomb();
    drawNumber();
    drawFlag();
}

void playerInput() {
    int i = 0;
    int j = 0;
    //Input functions
    for (i = 0; i < fieldSize; i++) {
        for (j = 0; j < fieldSize; j++) {
            //Checks if the mouse is on which field and gets back the x and y of field
            if (GetMouseX() > i * 50 && GetMouseX() < (i + 1) * 50 && GetMouseY() > j * 50 && GetMouseY() < (j + 1) *
                50) {
                //If left button is pressed and there is no flag it uncovers the field
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (isFlag[i][j] == false) {
                        isCovered[i][j] = false;
                    }
                }
                //If the field is covered and right button is pressed it places a flag
                //If you right click again it removes the flag
                else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                    //It only works if the field is covered
                    if (isCovered[i][j] == true) {
                        //If its flag on field it removes the flag
                        //And adds one flag to the usable ones
                        if (isFlag[i][j] == true) {
                            isFlag[i][j] = false;
                            flagsLeft++;
                        }
                        //If there isnt any flag it adds one flag but removes one flag from the usable ones
                        //If there are no flags left it does nothing
                        else if (isFlag[i][j] == false && flagsLeft > 0) {
                            isFlag[i][j] = true;
                            flagsLeft--;
                        }
                    }
                }
            }
        }
    }
}












void generateBombs() {
    srand(time(NULL));
    for (int i = 0; i < maxFlags; i++) {
            int x =   rand()% 10;
            int y =   rand()% 10;
            isBomb[x][y] = true;
    }
}
void calculateNumbers() {

}