#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>


void main(){
    // X, Y
    InitWindow(1150, 650, "Furia da Mina");
    SetTargetFPS(30);
    float posX = 0;
    float posY = 0;

    while(!WindowShouldClose()){
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Test sucessful!", 20, 30, 20, LIGHTGRAY);

            // 0,0 coordinate
            DrawRectangle(0,0,20, 20, RED);

            //movement test
            DrawRectangle(posX, posY,20, 20, BLUE);
            posX += GetFrameTime();
            posY += (GetFrameTime() * 65) * 3.5f;
        EndDrawing();
    }
    CloseWindow();
}
// Sprite do minecart muda quanto mais pontos tem, tendo mais items nele, tambem deve fica mais devagar com mais items

// items deven cair mais rapido com a quantidade de pontos

// Poções devem ficar mais raras com a quantidade de pontos, bombas mais communs

// Mais items devem cair com mais pontos

// Codigo para determinar quantos items estão caindo

// Codigo para deletar items coletados ou fora de tela, para não lagar o jogo

// Codigo para spawnar items

// Codigo para cair items, e aumentar a velocidade

// Codigo de movimento do jogador

// Codigo para manter os pontos

// Codigo para salvar o high score