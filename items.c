#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include "items.h"

#define MAX_ITENS 30

//Ores

Ore Gold = {500, 1.0f, {0}, 0, 2};
Ore Ruby = {1000, 2.0f, {0}, 0, 3};
Ore Diamond = {1500, 2.5f, {0}, 0, 4};
Ore Emerald = {2500, 3.5f, {0}, 0, 5};
Ore Bomb = {0, 1.5f, {0}, 0, 2.5};
Ore Shield = {-1, 2.0f, {0}, 0, 2};
Ore Magnet = {-2, 2.0f, {0}, 0, 2};

int escudoAtivo = 0;
float tempoIma = 0.0f;


ItemCaindo listaItens[MAX_ITENS];

void ItemsStart(){
    for(int i = 0; i < MAX_ITENS; i++){
        listaItens[i].ativo = 0;
    }
}

// Bombs

// Escudo

// Magnet

float timerSpawn = 0;

int metaVida = 10000; // meta de pontuação para ganhar uma vida extra


float getTimeLimit(int cs){
    timerSpawn += GetFrameTime();

    float tempoLimite = 1.0f - (cs / 50000.0f); //tempo de spawn diminui com a pontuação, mas não pode ser menor que 0.25 segundos
    if(tempoLimite < 0.25f) {
        tempoLimite = 0.25f;
    } 
    return tempoLimite;
}


void itemLogic(int *cs, Rectangle plyrColl, int *life, int *gameover, float tl, int f, int *h){
    if(f == 0){
    if(tempoIma > 0.0f){
        tempoIma -= GetFrameTime();
        if(tempoIma <= 0.0f) tempoIma = 0.0f;
    }
    if (timerSpawn >= tl){
                timerSpawn = 0.0f; // Zera o cronômetro para contar o próximo segundo

                // Procura a primeira gaveta vazia (ativo == 0) no vetor
                for (int i = 0; i < MAX_ITENS; i++){
                    if (listaItens[i].ativo == 0){
                        listaItens[i].ativo = 1; // Liga o item!

                        // Sorteia uma posição X aleatória na largura da tela (entre 0 e 1100)
                        listaItens[i].hitBox.x = GetRandomValue(0, 1100);
                        // Começa lá no topo, um pouco acima da tela (-50) para cair suave
                        listaItens[i].hitBox.y = -50;
                        // Tamanho da caixa de colisão do item (largura e altura)
                        listaItens[i].hitBox.width = 50;
                        listaItens[i].hitBox.height = 50;
                        int chance = GetRandomValue(1, 100);
                        int limiteMinerio = 70 - (*cs / 2500) * 2;
                        if(limiteMinerio < 30) limiteMinerio = 30; // Limita a chance mínima de minérios para 30%
                        if(chance <= limiteMinerio){
                            // Sorteando qual minério vai cair
                            int sorteioMinerio = GetRandomValue(1, 4); // 1 a 4 para os minérios
                            switch (sorteioMinerio){
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
                        }else if (chance <= 90){
                            listaItens[i].tipo = Bomb;
                        }else if (chance <= 95){
                            listaItens[i].tipo = Shield;
                        }else{
                            listaItens[i].tipo = Magnet;
                        }
                        break; // Sai do loop após ativar um item
                    }
                }
            }
    }

    for (int i = 0; i < MAX_ITENS; i++)
            {
                // Só mexe no item se ele estiver ativo na tela
                if (listaItens[i].ativo == 1)
                {
                    if(f == 0){
                    float multiplicadorVel = 1.0f + (*cs / 5000.0f) * 0.1f; // Aumenta a velocidade de queda com base na pontuação
                    // GRAVIDADE: Aumentando o eixo Y para ele descer
                    listaItens[i].hitBox.y += (GetFrameTime() * 65) * listaItens[i].tipo.fallspd * multiplicadorVel;
                    listaItens[i].tipo.rot += listaItens[i].tipo.rotRate;

                    if(tempoIma > 0.0f && listaItens[i].tipo.points > 0){
                        float centroPlayerX = plyrColl.x + plyrColl.width / 2;
                        float centroPlayerY = plyrColl.y + plyrColl.height / 2;
                        float dx = centroPlayerX - listaItens[i].hitBox.x;
                        float dy = centroPlayerY - listaItens[i].hitBox.y;
                        float distancia = sqrt(dx * dx + dy * dy);

                        if(distancia < 260.0f && distancia > 1.0f){
                            listaItens[i].hitBox.x += (dx / distancia) * 320.0f * GetFrameTime();
                            listaItens[i].hitBox.y += (dy / distancia) * 320.0f * GetFrameTime();
                        }
                    }
                    }
                    // DESENHO: Desenha o sprite do minério na posição X e Y da hitBox
                    if (listaItens[i].tipo.sprite.id > 0) {
                        Rectangle recorteOriginal = {0.0f, 0.0f, (float)listaItens[i].tipo.sprite.width, (float)listaItens[i].tipo.sprite.height};
                        DrawTexturePro(listaItens[i].tipo.sprite, recorteOriginal, listaItens[i].hitBox, (Vector2){16, 16}, listaItens[i].tipo.rot, WHITE);
                    } else if (listaItens[i].tipo.points == -1) {
                        // Desenho provisório do Escudo (Bolinha Azul com E)
                        DrawCircle((int)listaItens[i].hitBox.x + 25, (int)listaItens[i].hitBox.y + 25, 22, SKYBLUE);
                        DrawText("E", (int)listaItens[i].hitBox.x + 18, (int)listaItens[i].hitBox.y + 13, 25, DARKBLUE);
                    } else if (listaItens[i].tipo.points == -2) {
                        // Desenho provisório do Ímã (Bolinha Roxa com I)
                        DrawCircle((int)listaItens[i].hitBox.x + 25, (int)listaItens[i].hitBox.y + 25, 22, PURPLE);
                        DrawText("I", (int)listaItens[i].hitBox.x + 21, (int)listaItens[i].hitBox.y + 13, 25, WHITE);
                    }
                    // COLETA: Checa se o retângulo do item encostou no retângulo do jogador (plyrColl)
                    if (CheckCollisionRecs(listaItens[i].hitBox, plyrColl))
                    {
                        if (listaItens[i].tipo.points == 0){
                            if(escudoAtivo > 0){
                                escudoAtivo = 0; // desativa o escudo
                            }else{
                                *life -= 1;
                                *h = 1;
                            }
                        }
                        else if(listaItens[i].tipo.points == -1){
                            escudoAtivo = 1;
                        }
                        else if(listaItens[i].tipo.points == -2){
                            tempoIma = 6.0f; // ativa o efeito do ímã
                            }else{
                                *cs += listaItens[i].tipo.points;

                            if(*cs >= metaVida){
                                metaVida += 10000; // aumenta a meta para a próxima vida extra
                                if(*life < 3){
                                    *life += 1; // dá uma vida extra
                                }
                            }
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

void clearItems(){
    metaVida = 10000; // reseta a meta de pontuação para ganhar uma vida extra
    escudoAtivo = 0; // reseta o escudo ativo
    tempoIma = 0.0f; // reseta o tempo do ímã
    for (int i = 0; i < MAX_ITENS; i++){
        listaItens[i].ativo = 0; // desativa todos os itens na tela
    }
}