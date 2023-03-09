#include "raylib.h"

#define MAX_QUEUE_SIZE 25

struct User{
    int x;
    int y;
    bool pos;
}User;

struct Enemy{
    int x;
    int y;
    int point;
    bool using;
    bool pos;
}Enemy;

int main(void) {
    
    const int ScreenWidth = 1920;
    const int ScreenHeight = 1080;
    
    InitWindow(ScreenWidth, ScreenHeight, "spider dance");
    
    SetTargetFPS(60);
    
    ToggleFullscreen();
    
    User.x = -400;
    User.y = 100;
    
    int start = 0;
    
    int frame = 0;
    
    int score = 0;
    
    int speed = 30;
    
    bool gameover = false;
    
    struct Enemy enemys[2] = {0};
    
    enemys[0].x = 10000;
    enemys[1].x = 10000;
    
    int sequence = 2;
    
    while(!WindowShouldClose()) {
        
        if(IsKeyPressed(KEY_SPACE) && !start) {
            start = 1;
        }
        if(User.x < 200 && start == 1) {
            User.x += 60;
        }
        
        if(frame < 60 && start) {
            frame++;
        } else {
            frame = 0;
        }
        
        if(!gameover){
            
            if(!frame && start) {
                
                if(sequence < 1) {
                    sequence++;
                } else{
                    sequence = 0;
                }
                
                enemys[sequence].x = 1920;
                int rand = GetRandomValue(0, 1);
                if(rand) {
                    enemys[sequence].y = 880;
                    enemys[sequence].pos = true;
                } else {
                    enemys[sequence].y = 100;
                    enemys[sequence].pos = false;
                }
                
                enemys[sequence].using = true;
                
            }
            
            for(int i = 0; i < 2; i++) {
                if(enemys[i].using) {
                    enemys[i].x -= speed;
                    if(enemys[i].x <= -100) {
                        enemys[i].using = false;
                    }
                } else {
                    continue;
                }
            }
            
            if(IsKeyPressed(KEY_SPACE) && start) {
                if(User.y == 880) {
                    User.y = 100;
                    User.pos = false;
                } else {
                    User.y = 880;
                    User.pos = true;
                }
            }
            for(int i = 0; i < 2; i++) {
                
                if(User.pos == enemys[i].pos && User.x <= enemys[i].x - 100 && enemys[i].x <= User.x + 150) {
                    enemys[i].x = 10000;
                    enemys[i].y = 10000;
                    score++;
                    if(!(score % 5) && speed < 50) {
                        speed++;
                    }
                } else if(enemys[i].x <= 0) {
                    gameover = true;
                } else {
                    continue;
                }
                
            }
            
        }
        
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            DrawRectangle(0, 0, 1920, 100, BLACK);
            DrawRectangle(0, 980, 1920, 100, BLACK);
            
            //DrawText(TextFormat("%d", speed), 200, 200, 100, BLACK);
            
            DrawText(TextFormat("score : %d", score), 0, 0, 100, WHITE);
            
            for(int i = 0; i < 2; i++) {
                if(enemys[i].using && !gameover) {
                    DrawRectangle(enemys[i].x, enemys[i].y, 100, 100, BLUE);
                } else if(gameover) {
                    DrawRectangle(0, enemys[i].y, 100, 100, RED);
                    DrawText(TextFormat("your score : %i", score), 640, 440, 100, BLACK);
                } else {
                    continue;
                }
            }
            
            DrawRectangle(User.x, User.y, 100, 100, RED);
            DrawRectangle(User.x+150, User.y, 50, 100, RED);
            
        EndDrawing();
        
    }
    
}