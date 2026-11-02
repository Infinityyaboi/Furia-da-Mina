#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include "items.h"
#include "movement.h"
#include "highscore.h"
#include "menu.h"

int init = 0;
int life = 3;
int menu = 0;
int cs = 0;
int gameover = 0;
Texture2D p;
Texture2D w;


void main(){
    p.id = 0;

    // X, Y
    InitWindow(1150, 650, "Furia da Mina");
    InitAudioDevice();

    SetTargetFPS(30);
    float posX = 0;
    float posY = 0;
    
    #define MAX_ITEMS 30

    ItemCaindo items[MAX_ITEMS];

    for(int i =0; i < MAX_ITEMS; i++){
        listaItems[i].ativo = 0;
    }

    float timerSpawn = 0;

    while(!WindowShouldClose()){



        // caixa de collisão do jogador
        Rectangle plyrColl = {playerPos.x, playerPos.y, (32.0 * 3.5), ((32.0 * 3.5) - 50.0)};
        

        BeginDrawing();

            if(menu == 0){
                //main menu

                if(init == 0){ 
                    if(start.texture.id == 0){
                        start.texture = LoadTexture("sprites/buttons/butstart.png");
                    }
                    if(p.id > 0){
                        UnloadTexture(p);
                        UnloadTexture(w);
                        UnloadTexture(Gold.sprite);
                        UnloadTexture(Ruby.sprite);
                        UnloadTexture(Diamond.sprite);
                        UnloadTexture(Emerald.sprite);
                        p.id = 0;
                    }
                    
                    init = 1;
                }
                ClearBackground((Color){46, 52, 64, 255});
                //load_big_button(&start, 1);

                if(load_button(&start, 3) == 1 || IsKeyPressed(KEY_S)){
                    menu = 1;
                    init = 0;
                }

            } else if(menu == 1){
                // game screen
                if(init == 0){
                    if(start.texture.id > 0){
                        UnloadTexture(start.texture);

                        start.texture.id = 0;
                    }
                    if(p.id == 0){
                        p = LoadTexture("sprites/player.png");
                        w = LoadTexture("sprites/wheels.png");
                        Gold.sprite = LoadTexture("sprites/Gold.png");
                        Ruby.sprite = LoadTexture("sprites/Ruby.png");
                        Diamond.sprite = LoadTexture("sprites/Diamond.png");
                        Emerald.sprite = LoadTexture("sprites/Emerald.png");
                    }
                    init = 1;
                }

                ClearBackground(RAYWHITE);

                DrawText(TextFormat("SCORE: %d", cs), 30, 60, 20, BLACK);
                // 0,0 coordinate
                DrawRectangle(0,0,20, 20, RED);

                if(IsKeyPressed(KEY_O)){
                    cs += Emerald.points;
                }
                if(IsKeyPressed(KEY_G)){
                    gameover = 1;
                }
                if(IsKeyPressed(KEY_R)){
                    reset_pos();
                }
                move(cs);
                DrawPlayer(p, w, cs);
                //movement test
                //DrawRectangle(posX, posY,20, 20, BLUE);
                //posX += GetFrameTime();
                ///posY += (GetFrameTime() * 65) * Emerald.fallspd;

                // Soma o tempo que passou desde o último frame
timerSpawn += GetFrameTime();

// Se passou 1 segundo, tenta criar um item novo
if(timerSpawn >= 1.0f) {
    timerSpawn = 0.0f; // Zera o cronômetro para contar o próximo segundo

    // Procura a primeira gaveta vazia (ativo == 0) no vetor
    for(int i = 0; i < MAX_ITENS; i++) {
        if(listaItens[i].ativo == 0) {
            listaItens[i].ativo = 1; // Liga o item!
            
            // Sorteia uma posição X aleatória na largura da tela (entre 0 e 1100)
            listaItens[i].hitBox.x = GetRandomValue(0, 1100);
            // Começa lá no topo, um pouco acima da tela (-50) para cair suave
            listaItens[i].hitBox.y = -50;
            // Tamanho da caixa de colisão do item (largura e altura)
            listaItens[i].hitBox.width = 40;
            listaItens[i].hitBox.height = 40;

            // Sorteando qual minério vai cair
            int sorteio = GetRandomValue(1, 4);
            switch(sorteio){
                case 1:
                    listaItens[i].tipo = Gold;
                    break;
                case 2:
                    listaItens[i].tipo = Ruby;
                    break;
                case 3:
                    listaItens[i].tipo = Diamond;
                    break;
                case 4:
                    listaItens[i].tipo = Emerald;
                    break;
            }
            break; // criar só 1 item por vez, não 30 de uma vez
        }
    }
}

                for(int i = 0; i < MAX_ITENS; i++){
    // Só mexe no item se ele estiver ativo na tela
    if(listaItens[i].ativo == 1) {
        
        // GRAVIDADE: Aumentando o eixo Y para ele descer
        listaItens[i].hitBox.y += (GetFrameTime() * 65) * listaItens[i].tipo.fallspd;

        // DESENHO: Desenha o sprite do minério na posição X e Y da hitBox
        DrawTexture(listaItens[i].tipo.sprite, listaItens[i].hitBox.x, listaItens[i].hitBox.y, WHITE);

        // COLETA: Checa se o retângulo do item encostou no retângulo do jogador (plyrColl)
        if(CheckCollisionRecs(listaItens[i].hitBox, plyrColl)) {
            cs += listaItens[i].tipo.points;
            listaItens[i].ativo = 0;
        }

        // LIMPEZA DE TELA: Se passou do fundo da janela (altura > 650)
        if(listaItens[i].hitBox.y > 650) {
            listaItens[i].ativo = 0;
        }
    }
}
            
            }
        EndDrawing();
    }
    if(start.texture.id > 0){
        UnloadTexture(start.texture);
    }
    if(p.id > 0){
        UnloadTexture(p);
        UnloadTexture(w);
        UnloadTexture(Gold.sprite);
        UnloadTexture(Ruby.sprite);
        UnloadTexture(Diamond.sprite);
        UnloadTexture(Emerald.sprite);
    }
    

    
    CloseAudioDevice();
    CloseWindow();
}

// items deven cair mais rapido com a quantidade de pontos

// Mais items devem cair com mais pontos

// Codigo para determinar quantos items estão caindo

// Codigo para deletar items coletados ou fora de tela, para não lagar o jogo

// Codigo para spawnar items

// Codigo para cair items, e aumentar a velocidade

// Codigo para manter os pontos 1/2

// Codigo para salvar o high score

// Leaderboard de score