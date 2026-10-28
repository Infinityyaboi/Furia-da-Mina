#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once

typedef struct{
    Texture2D texture;
    Vector2 pos;
}Button;

extern Button start = {0, {575, 325}};

int button_pressed(Button *butt, float h, float w){
    Rectangle size = {(*butt).pos.x, (*butt).pos.y, h, w};
    if(CheckCollisionPointRec(GetMousePosition(), size)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return 2;
        }
        return 1;
    }
    return 0;
}

int load_big_button(Button *butt, float size){
    float h = 32 * size;
    float w = 128 * size;
    int check = button_pressed(&(*butt), h, w);
    if(check == 1){
        DrawTexture((*butt).texture, (*butt).pos.x, (*butt).pos.y, WHITE);
        return 0;
    } else if(check == 1){
        DrawTexture((*butt).texture, (*butt).pos.x, (*butt).pos.y, BLACK);
        return 0;
    } else if(check == 1){
        DrawTexture((*butt).texture, (*butt).pos.x, (*butt).pos.y, WHITE);
        return 1;
    }

}



