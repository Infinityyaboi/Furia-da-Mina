#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once


typedef struct{
    int points;
    float fallspd;
    Texture2D sprite;
    float rot;
    float rotRate;
} Ore;

typedef struct{
    Rectangle hitBox;
    int ativo;
    Ore tipo;
} ItemCaindo;

// Bombs

// Health Potion

extern Ore Gold;
extern Ore Ruby;
extern Ore Diamond;
extern Ore Emerald;
extern Ore Bomb;

void ItemsStart();

float getTimeLimit(int cs);

void itemLogic(int *cs, Rectangle plyrColl, int *life, int *gameover, float tl, int f, int *h);

void clearItems();