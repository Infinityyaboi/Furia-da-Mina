#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>


typedef struct{
    int points;
    float fallspd;
    const char *spritePath;
    Texture2D sprite;
} Ore;

// Bombs

// Health Potion

Ore Gold = {500, 1.0f, "sprites/Gold.png",{0}};
Ore Ruby = {1000, 2.0f, "sprites/Ruby.png",{0}};
Ore Diamond = {1500, 2.5f, "sprites/Diamond.png",{0}};
Ore Emerald = {2500, 3.5f, "sprites/Emerald.png",{0}};