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