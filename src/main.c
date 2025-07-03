#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

void drawFPS(){
    int fps = GetFPS();
    char fpsText[32];
    snprintf(fpsText, sizeof(fpsText), "%d", fps);
    DrawText(fpsText, 0, 0, 20, BLACK);
}

void drawScore(int snakeSize, int WIDTH, int HEIGHT){
    char scoreText[32];
    snprintf(scoreText, sizeof(scoreText), "TOTAL SCORE: %d", snakeSize);
    DrawText(scoreText, WIDTH - 200, 0, 20, BLACK);
}

int main(){
    const int WIDTH = 1200;
    const int HEIGHT = 900;
    const int BLOCKSIZE = 20;
    const int SPEED = 4;

    char* UP = "up";
    char* DOWN = "down";
    char* LEFT = "left";
    char* RIGHT = "right";

    int x = WIDTH/2;
    int y = HEIGHT/2;
    int snakeSize = 1;
    char* currentDirection;
    
    int ballEaten = 1;
    int ballX, ballY;

    InitWindow(1200, 900, "Lemke snake game");
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT)) currentDirection = RIGHT;
        if (IsKeyPressed(KEY_LEFT)) currentDirection = LEFT;
        if (IsKeyPressed(KEY_UP)) currentDirection = UP;
        if (IsKeyPressed(KEY_DOWN)) currentDirection = DOWN;

        if (currentDirection == UP) y -= SPEED;
        if (currentDirection == DOWN) y += SPEED;
        if (currentDirection == LEFT) x -= SPEED;
        if (currentDirection == RIGHT) x += SPEED;
        
        if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT) return 0;
        
        if (ballEaten){
            ballEaten = 0;
            ballX = GetRandomValue(0, WIDTH);
            ballY = GetRandomValue(0, HEIGHT);
        }

        if (abs(ballX - x) < BLOCKSIZE && abs(ballY - y) < BLOCKSIZE){
            snakeSize++;
            ballEaten = 1;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawFPS();
            drawScore(snakeSize, WIDTH, HEIGHT);
            DrawRectangle(x - (BLOCKSIZE / 2), y - (BLOCKSIZE / 2), BLOCKSIZE, BLOCKSIZE, BLACK);
            DrawRectangle(ballX - (BLOCKSIZE / 2), ballY - (BLOCKSIZE / 2), BLOCKSIZE, BLOCKSIZE, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}