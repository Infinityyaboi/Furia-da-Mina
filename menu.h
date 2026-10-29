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

extern Button start = {{0}, {500, 325}, 32, 24};
Color shift = {155, 169, 196, 180};

int button_pressed(Button *butt, float h, float w){
    Rectangle size = {(*butt).pos.x, (*butt).pos.y, w, h};
    if(CheckCollisionPointRec(GetMousePosition(), size)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            return 2;
        }
        return 1;
    }
    return 0;
}

int load_button(Button *butt, float size){
    float h = (*butt).h * size;
    float w = (*butt).w * size;
    int check = button_pressed(butt, h, w);
    if(check == 0){
        DrawTextureEx((*butt).texture, (*butt).pos, 0, size, WHITE);
        return 0;
    } else if(check == 1){
        DrawTextureEx((*butt).texture, (*butt).pos, 0, size, shift);
        return 0;
    } else if(check == 2){
        DrawTextureEx((*butt).texture, (*butt).pos, 0, size, WHITE);
        return 1;
    }

}



