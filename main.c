#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include "items.h"
#include "movement.h"

void main(){

    Texture2D p;    
    Texture2D w;

    // X, Y
    InitWindow(1150, 650, "Furia da Mina");
    InitAudioDevice();

    p = LoadTexture("sprites/player.png");
    w = LoadTexture("sprites/wheels.png");
    Gold.sprite = LoadTexture("sprites/Gold.png");
    Ruby.sprite = LoadTexture("sprites/Ruby.png");
    Diamond.sprite = LoadTexture("sprites/Diamond.png");
    Emerald.sprite = LoadTexture("sprites/Emerald.png");

    int score = 0;

    SetTargetFPS(30);
    float posX = 0;
    float posY = 0;
    Vector2 playerPos = {500, 450};

    while(!WindowShouldClose()){

        // caixa de collisão do jogador
        Rectangle plyrColl = {playerPos.x, playerPos.y, (Diamond.sprite.width * 0.3f), ((Diamond.sprite.height * 0.3f) - 50)};

        //Movemento do jogador, precisa melhorar as physicas e adicionar a mudança de velocidade de acordo com os pontos
        move(&playerPos, score);

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("SCORE: ", 20, 30, 20, BLACK);

            // 0,0 coordinate
            DrawRectangle(0,0,20, 20, RED);

            if(IsKeyPressed(KEY_P)){
                score += 6;
            }


            DrawPlayer(p, w, &playerPos, score);
            // DrawTextureEx(Diamond.sprite, playerPos, 0.0f, 0.3f, WHITE);
            //movement test
            DrawRectangle(posX, posY,20, 20, BLUE);
            posX += GetFrameTime();
            posY += (GetFrameTime() * 65) * Emerald.fallspd;
        EndDrawing();
    }

    UnloadTexture(Gold.sprite);
    UnloadTexture(Ruby.sprite);
    UnloadTexture(Diamond.sprite);
    UnloadTexture(Emerald.sprite);
    CloseAudioDevice();
    CloseWindow();
}
// Sprite do minecart muda quanto mais pontos tem, tendo mais items nele, tambem deve fica mais devagar com mais items

// items deven cair mais rapido com a quantidade de pontos

// Mais items devem cair com mais pontos

// Codigo para determinar quantos items estão caindo

// Codigo para deletar items coletados ou fora de tela, para não lagar o jogo

// Codigo para spawnar items

// Codigo para cair items, e aumentar a velocidade

// Codigo de movimento do jogador

// Codigo para manter os pontos

// Codigo para salvar o high score

// Leaderboard de score