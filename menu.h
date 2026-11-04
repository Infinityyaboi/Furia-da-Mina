#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once


typedef struct{
    Texture2D texture;
    Vector2 pos;
    int w;
    int h;
}Button;

extern Button start;
extern Button controls;
extern Button leave;
extern Button gameResume;
extern Button gameRestart;
extern Button gameMainMenu;
extern Button gamePause;
int button_pressed(Button *butt, float h, float w);

int load_button(Button *butt, float size);

void DrawHealth(int life, int *go, Texture2D h1, int *f);