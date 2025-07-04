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

enum Direction{
    DIR_UP,
    DIR_DOWN,
    DIR_RIGHT,
    DIR_LEFT
};

struct Block {
    int x;
    int y;
    Direction dir;
};

struct Position{
    int x;
    int y;
};

int main(){
    const int WIDTH = 1200;
    const int HEIGHT = 900;
    const int BLOCKSIZE = 20;
    const int SPEED = 4;
    const int MAXSIZE = 2048;

    Block snake[MAXSIZE] = {0};
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    snake[0].dir = DIR_RIGHT;
    int snakeSize = 0;

    int ballEaten = 1;
    int ballX, ballY;

    int currentFrame = 0;
    Direction currentDirection = DIR_RIGHT;
    Position history[MAXSIZE*5] = {0};
    history[0] = {snake[0].x, snake[0].y};
    
    InitWindow(1200, 900, "Lemke snake game");
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        currentFrame++;
        currentDirection = snake[0].dir;
        if (IsKeyPressed(KEY_RIGHT) && currentDirection != DIR_LEFT){
            currentDirection = DIR_RIGHT;
        }
        if (IsKeyPressed(KEY_LEFT) && currentDirection != DIR_RIGHT){
            currentDirection = DIR_LEFT;
        }
        if (IsKeyPressed(KEY_UP) && currentDirection != DIR_DOWN){
            currentDirection = DIR_UP;
        }
        if (IsKeyPressed(KEY_DOWN) && currentDirection != DIR_UP){
            currentDirection = DIR_DOWN;
        }

        snake[0].dir = currentDirection;
        if (snake[0].dir == DIR_UP) snake[0].y -= SPEED;
        else if (snake[0].dir == DIR_DOWN) snake[0].y += SPEED;
        else if (snake[0].dir == DIR_LEFT) snake[0].x -= SPEED;
        else if (snake[0].dir == DIR_RIGHT) snake[0].x += SPEED;

        for (int i = MAXSIZE - 1; i > 0; i--){
            history[i] = history[i-1];
        }
        history[0] = {snake[0].x, snake[0].y};

        for (int i = 1; i <= snakeSize; i++){
            int historyIndex = i * (BLOCKSIZE / SPEED);
            snake[i].x = history[historyIndex].x;
            snake[i].y = history[historyIndex].y;
            snake[i].dir = snake[i-1].dir;
        }

        if (snake[0].x < 0 || snake[0].x > WIDTH || snake[0].y < 0 || snake[0].y > HEIGHT) return 0;
        
        for (int i = 1; i < snakeSize; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                return 0;
            }
        }

        if (ballEaten){
            ballEaten = 0;
            ballX = GetRandomValue(0, WIDTH);
            ballY = GetRandomValue(0, HEIGHT);
        }

        if (abs(ballX - snake[0].x) < BLOCKSIZE && abs(ballY - snake[0].y) < BLOCKSIZE){
            snakeSize++;
            ballEaten = 1;

            snake[snakeSize].x = snake[snakeSize - 1].x; 
            snake[snakeSize].y = snake[snakeSize - 1].y;
            snake[snakeSize].dir = snake[snakeSize - 1].dir;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        drawFPS();
        drawScore(snakeSize, WIDTH, HEIGHT);

        // draw snake
        for(int i = 0; i <= snakeSize; i++){
            DrawRectangle(snake[i].x - (BLOCKSIZE / 2), snake[i].y - (BLOCKSIZE / 2), BLOCKSIZE, BLOCKSIZE, BLACK);
        }

        // draw food
        DrawRectangle(ballX - (BLOCKSIZE / 2), ballY - (BLOCKSIZE / 2), BLOCKSIZE, BLOCKSIZE, BLUE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}