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
Texture2D foreground;
Texture2D background;


void main()
{
    p.id = 0;

    // X, Y
    InitWindow(1150, 650, "Furia da Mina");
    InitAudioDevice();

    SetTargetFPS(30);
    float posX = 0;
    float posY = 0;

    #define MAX_ITENS 30

    ItemCaindo listaItens[MAX_ITENS];

    for (int i = 0; i < MAX_ITENS; i++)
    {
        listaItens[i].ativo = 0;
    }

    float timerSpawn = 0;

    while (!WindowShouldClose())
    {

        // caixa de collisão do jogador
        Rectangle plyrColl = {playerPos.x, playerPos.y, (32.0 * 3.5), ((32.0 * 3.5) - 50.0)};

        BeginDrawing();

        if (menu == 0)
        {
            // main menu

            if (init == 0)
            {
                if (start.texture.id == 0)
                {
                    start.texture = LoadTexture("sprites/buttons/butstart.png");
                }
                if (p.id > 0)
                {
                    UnloadTexture(p);
                    UnloadTexture(w);
                    UnloadTexture(foreground);
                    UnloadTexture(background);
                    UnloadTexture(Gold.sprite);
                    UnloadTexture(Ruby.sprite);
                    UnloadTexture(Diamond.sprite);
                    UnloadTexture(Emerald.sprite);
                    UnloadTexture(Bomb.sprite);
                    p.id = 0;
                }

                init = 1;
            }
            ClearBackground((Color){46, 52, 64, 255});
            // load_big_button(&start, 1);

            if (load_button(&start, 3) == 1 || IsKeyPressed(KEY_S))
            {
                menu = 1;
                init = 0;
            }
        }
        else if (menu == 1)
        {
            // game screen
            if (init == 0)
            {
                if (start.texture.id > 0)
                {
                    UnloadTexture(start.texture);

                    start.texture.id = 0;
                }
                if (p.id == 0)
                {
                    foreground = LoadTexture("sprites/Background/Cave_fore.png");
                    background = LoadTexture("sprites/Background/Cave_back.png");
                    p = LoadTexture("sprites/player.png");
                    w = LoadTexture("sprites/wheels.png");
                    Gold.sprite = LoadTexture("sprites/Gold.png");
                    Ruby.sprite = LoadTexture("sprites/Ruby.png");
                    Diamond.sprite = LoadTexture("sprites/Diamond.png");
                    Emerald.sprite = LoadTexture("sprites/Emerald.png");
                    Bomb.sprite = LoadTexture("sprites/dynamite.png");
                }
                init = 1;
            }

            ClearBackground(RAYWHITE);

            // 0,0 coordinate
            DrawRectangle(0, 0, 20, 20, RED);

            if (IsKeyPressed(KEY_O))
            {
                cs += Emerald.points;
            }
            if (IsKeyPressed(KEY_G))
            {
                gameover = 1;
            }
            if (IsKeyPressed(KEY_R))
            {
                reset_pos();
                life = 3; // restaura a vida do jogador
                cs = 0;     // reseta a pontuação
                for (int i = 0; i < MAX_ITENS; i++)
                {
                    listaItens[i].ativo = 0; // desativa todos os itens na tela
                }
            }
            move(cs);
            DrawBackground(background);
            DrawText(TextFormat("SCORE: %d", cs), 30, 60, 20, BLACK);
            DrawPlayer(p, w, cs);
            DrawForeground(foreground);
            // movement test
            // DrawRectangle(posX, posY,20, 20, BLUE);
            // posX += GetFrameTime();
            /// posY += (GetFrameTime() * 65) * Emerald.fallspd;

            // Soma o tempo que passou desde o último frame
            timerSpawn += GetFrameTime();

            float tempoLimite = 1.0f - (cs / 50000.0f); //tempo de spawn diminui com a pontuação, mas não pode ser menor que 0.25 segundos
            if(tempoLimite < 0.25f) {
                tempoLimite = 0.25f;
            }   
            // Se passou o tempo limite, tenta criar um item novo
            if (timerSpawn >= tempoLimite)
            {
                timerSpawn = 0.0f; // Zera o cronômetro para contar o próximo segundo

                // Procura a primeira gaveta vazia (ativo == 0) no vetor
                for (int i = 0; i < MAX_ITENS; i++)
                {
                    if (listaItens[i].ativo == 0)
                    {
                        listaItens[i].ativo = 1; // Liga o item!

                        // Sorteia uma posição X aleatória na largura da tela (entre 0 e 1100)
                        listaItens[i].hitBox.x = GetRandomValue(0, 1100);
                        // Começa lá no topo, um pouco acima da tela (-50) para cair suave
                        listaItens[i].hitBox.y = -50;
                        // Tamanho da caixa de colisão do item (largura e altura)
                        listaItens[i].hitBox.width = 50;
                        listaItens[i].hitBox.height = 50;

                        // Sorteando qual minério vai cair
                        int sorteio = GetRandomValue(1, 5); // 1 a 4 para os minérios, 5 para a bomba
                        switch (sorteio)
                        {
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
                        case 5:
                            listaItens[i].tipo = Bomb;
                            break;
                        }
                        break; // criar só 1 item por vez, não 30 de uma vez
                    }
                }
            }

            for (int i = 0; i < MAX_ITENS; i++)
            {
                // Só mexe no item se ele estiver ativo na tela
                if (listaItens[i].ativo == 1)
                {

                    float multiplicadorVel = 1.0f + (cs / 5000.0f) * 0.1f; // Aumenta a velocidade de queda com base na pontuação
                    // GRAVIDADE: Aumentando o eixo Y para ele descer
                    listaItens[i].hitBox.y += (GetFrameTime() * 65) * listaItens[i].tipo.fallspd * multiplicadorVel;

                    // DESENHO: Desenha o sprite do minério na posição X e Y da hitBox
                    Rectangle recorteOriginal = {0.0f, 0.0f, (float)listaItens[i].tipo.sprite.width, (float)listaItens[i].tipo.sprite.height};
                    DrawTexturePro(listaItens[i].tipo.sprite, recorteOriginal, listaItens[i].hitBox, (Vector2){0, 0}, 0.0f, WHITE);
                    // COLETA: Checa se o retângulo do item encostou no retângulo do jogador (plyrColl)
                    if (CheckCollisionRecs(listaItens[i].hitBox, plyrColl))
                    {
                        if (listaItens[i].tipo.points == 0)
                        {
                            life--;
                            if (life <= 0)
                            {
                                gameover = 1;
                            }
                        }
                        else
                        {
                            cs += listaItens[i].tipo.points;
                        }
                        listaItens[i].ativo = 0;
                    }

                    // LIMPEZA DE TELA: Se passou do fundo da janela (altura > 650)
                    if (listaItens[i].hitBox.y > 650)
                    {
                        listaItens[i].ativo = 0;
                    }
                }
            }
        }
        EndDrawing();
    }
    if (start.texture.id > 0)
    {
        UnloadTexture(start.texture);
    }
    if (p.id > 0)
    {
        UnloadTexture(p);
        UnloadTexture(w);
        UnloadTexture(Gold.sprite);
        UnloadTexture(Ruby.sprite);
        UnloadTexture(Diamond.sprite);
        UnloadTexture(Emerald.sprite);
        UnloadTexture(Bomb.sprite);
    }

    CloseAudioDevice();
    CloseWindow();
}

// [FEITO] items deven cair mais rapido com a quantidade de pontos
// [FEITO] Mais items devem cair com mais pontos
// [FEITO] Codigo para determinar quantos items estão caindo
// [FEITO] Codigo para deletar items coletados ou fora de tela, para não lagar o jogo
// [FEITO] Codigo para spawnar items
// [FEITO] Codigo para cair items, e aumentar a velocidade

// Codigo para manter os pontos 1/2
// Codigo para salvar o high score
// Leaderboard de score