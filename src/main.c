#include "raylib.h"
#define fieldSize 10

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

//DrawScore
void drawScore();

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
    initNumber0Texture();
    initNumber1Texture();
    initNumber2Texture();
    initNumber3Texture();
    initNumber4Texture();
    initNumber5Texture();
    initFlagTexture();
}

//Texts for Main menu
void mainMenu() {
    DrawText("Minesweeper", 80, 40, 50, BLACK);
    DrawText("By Raphael Botond Jonas", 110, 100, 20, BLACK);
    DrawText("Press SPACE to start", 60, 200, 30, BLACK);
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
    if (number == 0) {
        DrawTexture(number0, x, y, WHITE);
    }
    if (number == 1) {
        DrawTexture(number1, x, y, WHITE);
    }
    if (number == 2) {
        DrawTexture(number2, x, y, WHITE);
    }
    if (number == 3) {
        DrawTexture(number3, x, y, WHITE);
    }
    if (number == 4) {
        DrawTexture(number4, x, y, WHITE);
    }
    if (number == 5) {
        DrawTexture(number5, x, y, WHITE);
    }
}

//Functions to draw all grass
void drawGrass() {
    grassField(0, 0);
}

//Functions to draw all bomb under grass
void drawBomb() {
    explodedField(50, 0);
}

//Functions to draw all numbers under grass
void drawNumber() {
    numberField(100, 0, 0);
}

//Function to Draw all flags
void drawFlag() {
    flagField(150, 0);
}

//Main call for draw fields what calls subfunctions
void drawField() {
    drawGrass();
    drawNumber();
    drawBomb();
    drawFlag();
}
