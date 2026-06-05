#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#define fieldSize 10
//Defines how many bombs they are maximal in other words every Bomb has one flag
#define maxFlags 15

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
bool playerWon = false;
//player muss false gesetzt werden damit man nicht einmal gewinnt und dann immer es wird der player zurück gesetzt
int fieldValue[fieldSize][fieldSize] = {0};

int main(void) {
    //Makes all covered in grass
    resetGrass();
    generateBombs();
    calculateNumbers();
    //Windows size
    const int screenWidth = 500;
    const int screenHeight = 500;

    //Init Windows
    InitWindow(screenWidth, screenHeight, "MINESWEEPER");
    //Set Target FPS
    SetTargetFPS(60);

    //Inits all PNGS
    initGame();

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
                drawField();//muss nochmal gedrawt werden damit man alles sieht
                endGame();
                if (IsKeyDown(KEY_SPACE)) {
                    resetGame();
                    gameState = MAIN_MENU;
                }
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
    DrawText("FIND THE 15 BOMBS", 90, 310, 25, RED);
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
                        lastClickedX = i;
                        lastClickedY = j;
                        wonOrLoose();//Funktion wonorloose aufrufen um zu schauen ob man verloren oder gewonnen hat
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
                        wonOrLoose();//Funktion wonorloose aufrufen um zu schauen ob man verloren oder gewonnen hat
                    }
                }
            }
        }
    }
}

void generateBombs() {
    srand(time(NULL));
    for (int i = 0; i < maxFlags; i++) {
        //generate a random number for the x Coordinate
        int x = rand() % 10;
        //generate a random number for the y Coordinate
        int y = rand() % 10;
        if (isBomb[x][y] == false) {
            isBomb[x][y] = true;
        }
        else {
            i--;
        }

    }
}

void calculateNumbers() {
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            bool isBombFields[8] = {false};
            int count = 0;

            //Check every field for bombs and teriary is here to check if its on field
            isBombFields[0] = (i - 1) >= 0 ? isBomb[i - 1][j] : false;
            isBombFields[1] = (i + 1) < fieldSize ? isBomb[i + 1][j] : false;
            isBombFields[2] = (j - 1) >= 0 ? isBomb[i][j - 1] : false;
            isBombFields[3] = (j + 1) < fieldSize ? isBomb[i][j + 1] : false;
            isBombFields[4] = (i - 1) >= 0 && (j - 1) >= 0 ? isBomb[i - 1][j - 1] : false;
            isBombFields[5] = (i + 1) <= fieldSize && (j + 1) < fieldSize ? isBomb[i + 1][j + 1] : false;
            isBombFields[6] = (i + 1) < fieldSize && (j - 1) >= 0 ? isBomb[i + 1][j - 1] : false;
            isBombFields[7] = (i - 1) >= 0 && (j + 1) < fieldSize ? isBomb[i - 1][j + 1] : false;
            //Counts how many bombs they are
            for (int k = 0; k < 8; k++) {
                if (isBombFields[k] == true) {
                    count++;
                }
            }
            //The field value is count of bombs
            fieldValue[i][j] = count;
            isCovered[i][j] = false;
        }
    }
}

void endGame() {
    if (playerWon) {
        //schwarzer Rand für game over
        DrawText("YOU WON!", 117, 40, 50, BLACK);
        DrawText("YOU WON!", 123, 40, 50, BLACK);
        DrawText("YOU WON!", 120, 37, 50, BLACK);
        DrawText("YOU WON!", 120, 43, 50, BLACK);
        DrawText("YOU WON!", 118, 38, 50, BLACK);
        DrawText("YOU WON!", 122, 38, 50, BLACK);
        DrawText("YOU WON!", 118, 42, 50, BLACK);
        DrawText("YOU WON!", 122, 42, 50, BLACK);
        //Normaler Text
        DrawText("YOU WON!", 120, 40, 50, GREEN);

        //Rand für blauen Text
        DrawText("Press SPACE to play", 8, 160, 45, BLACK);
        DrawText("Press SPACE to play", 12, 160, 45, BLACK);
        DrawText("Press SPACE to play", 10, 158, 45, BLACK);
        DrawText("Press SPACE to play", 10, 162, 45, BLACK);
        //normaler blauer Text
        DrawText("Press SPACE to play", 10, 160, 45, BLUE);

        //dickerer Rand
        DrawText("again", 8, 210, 45, BLACK);
        DrawText("again", 12, 210, 45, BLACK);
        DrawText("again", 10, 208, 45, BLACK);
        DrawText("again", 10, 212, 45, BLACK);
        //dickeres Blau
        DrawText("again", 10, 210, 45, BLUE);
    } else {
        //schwarzer Rand für game over
        DrawText("GAME OVER", 117, 40, 50, BLACK);
        DrawText("GAME OVER", 123, 40, 50, BLACK);
        DrawText("GAME OVER", 120, 37, 50, BLACK);
        DrawText("GAME OVER", 120, 43, 50, BLACK);
        DrawText("GAME OVER", 118, 38, 50, BLACK);
        DrawText("GAME OVER", 122, 38, 50, BLACK);
        DrawText("GAME OVER", 118, 42, 50, BLACK);
        DrawText("GAME OVER", 122, 42, 50, BLACK);
        //game over Text in rot
        DrawText("GAME OVER", 120, 40, 50, RED);

        //Rand for Press Space to try again, aber abgeschnitten weil again geht sich nicht bei 500x 500 aus
        DrawText("Press SPACE to try", 8, 160, 45, BLACK);
        DrawText("Press SPACE to try", 12, 160, 45, BLACK);
        DrawText("Press SPACE to try", 10, 158, 45, BLACK);
        DrawText("Press SPACE to try", 10, 162, 45, BLACK);
        DrawText("Press SPACE to try", 10, 160, 45, BLUE);

        //Rand für again
        DrawText("again", 8, 210, 45, BLACK);
        DrawText("again", 12, 210, 45, BLACK);
        DrawText("again", 10, 208, 45, BLACK);
        DrawText("again", 10, 212, 45, BLACK);
        //hier again bisschen weiter unten
        DrawText("again", 10, 210, 45, BLUE);
    }
}

void wonOrLoose() {
    // VERLOREN: Bombe angeklickt
    if (isBomb[lastClickedX][lastClickedY]) {
        for (int x = 0; x < fieldSize; x++) {
            for (int y = 0; y < fieldSize; y++) {
                isCovered[x][y] = false;
            }
        }
        playerWon = false;
        gameState = GAME_OVER;
        return;
    }

    // GEWONNEN?
    bool allSafeOpen = true;

    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            // 1. Alle sicheren Felder müssen offen sein
            if (!isBomb[i][j] && isCovered[i][j]) {
                allSafeOpen = false;
            }
        }
    }

    // Sieg nur wenn BEIDES stimmt
    if (allSafeOpen) {
        for (int x = 0; x < fieldSize; x++) {
            for (int y = 0; y < fieldSize; y++) {
                isCovered[x][y] = false;
            }
        }
        playerWon = true;
        gameState = GAME_OVER;
    }
}

void resetGame() {
    //alles wird zurück gesetzt
    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            isBomb[i][j] = false;
            isFlag[i][j] = false;
            isCovered[i][j] = true;
            fieldValue[i][j] = 0;
        }
    }
    //für die neue Runde es werden wieder Bomben,Flaggen auf 15beschränkt platziert und das Spiel geht weiter
    flagsLeft = maxFlags;
    playerWon = false;

    generateBombs();
    calculateNumbers();
}
//ich glaub es passt so alles(ungefähr fürs erste) sorry wenn nicht schreibt mir falls ich noch was tun soll ich musste bisschen ai
//benutzen weil ich bei der Logik probleme hatte und wie man einen Rand macht