#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include "items.h"

#define MAX_ITENS 30

//Ores

Ore Gold = {500, 1.0f, {0}, 0};
Ore Ruby = {1000, 2.0f, {0}, 0};
Ore Diamond = {1500, 2.5f, {0}, 0};
Ore Emerald = {2500, 3.5f, {0}, 0};
Ore Bomb = {0, 1.0f, {0}, 0};


ItemCaindo listaItens[MAX_ITENS];

void ItemsStart(){
    for(int i = 0; i < MAX_ITENS; i++){
        listaItens[i].ativo = 0;
    }
}

// Bombs

// Magnet

float timerSpawn = 0;

// Speed Potion

float getTimeLimit(int cs){
    timerSpawn += GetFrameTime();

    float tempoLimite = 1.0f - (cs / 50000.0f); //tempo de spawn diminui com a pontuação, mas não pode ser menor que 0.25 segundos
    if(tempoLimite < 0.25f) {
        tempoLimite = 0.25f;
    } 
    return tempoLimite;
}


void itemLogic(int *cs, Rectangle plyrColl, int *life, int *gameover, float tl){
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

                        // Sorteando qual minério vai cair
                        int sorteio = GetRandomValue(1, 5); // 1 a 4 para os minérios, 5 para a bomba
                        switch (sorteio){
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

                    float multiplicadorVel = 1.0f + (*cs / 5000.0f) * 0.1f; // Aumenta a velocidade de queda com base na pontuação
                    // GRAVIDADE: Aumentando o eixo Y para ele descer
                    listaItens[i].hitBox.y += (GetFrameTime() * 65) * listaItens[i].tipo.fallspd * multiplicadorVel;
                    listaItens[i].tipo.rot += 2;

                    // DESENHO: Desenha o sprite do minério na posição X e Y da hitBox
                    Rectangle recorteOriginal = {0.0f, 0.0f, (float)listaItens[i].tipo.sprite.width, (float)listaItens[i].tipo.sprite.height};
                    DrawTexturePro(listaItens[i].tipo.sprite, recorteOriginal, listaItens[i].hitBox, (Vector2){16, 16}, listaItens[i].tipo.rot, WHITE);
                    // COLETA: Checa se o retângulo do item encostou no retângulo do jogador (plyrColl)
                    if (CheckCollisionRecs(listaItens[i].hitBox, plyrColl))
                    {
                        if (listaItens[i].tipo.points == 0)
                        {
                            *life--;
                            if (life <= 0)
                            {
                                *gameover = 1;
                            }
                        }
                        else
                        {
                            *cs += listaItens[i].tipo.points;
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
    for (int i = 0; i < MAX_ITENS; i++){
        listaItens[i].ativo = 0; // desativa todos os itens na tela
    }
}