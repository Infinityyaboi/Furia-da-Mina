#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#include "menu.h"
#pragma once

Button start = {{0}, {500, 325}, 32, 24};
Button controls = {{0},{450, 400}, 64, 24};
Button credits = {{0}, {450, 475}, 64, 24};
Button leave = {{0}, {500, 550}, 32, 24}; 
Button gamePause = {{0},{1100,20},24, 24};
Button gameResume = {{0}, {470, 200}, 64, 24};
Button gameRestart = {{0}, {470, 280}, 64, 24};
Button gameMainMenu = {{0}, {470, 360}, 64, 24};
Button submit = {{0}, {470, 400}, 64, 24};
Button hsRestart = {{0}, {470, 475}, 64, 24};
Button hsMainMenu = {{0}, {470, 550}, 64, 24};

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


int hl = 0;

void CheckHealth(int life, int **go, Texture2D h1, int **f, Rectangle org1, Rectangle org2, Rectangle loc1, Rectangle loc2, Rectangle loc3){
    if(life == 3){
        DrawTexturePro(h1,org1,loc1,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org1,loc2,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org1,loc3,(Vector2){0,0},0, WHITE);
    }else if(life == 2){
        DrawTexturePro(h1,org2,loc1,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org1,loc2,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org1,loc3,(Vector2){0,0},0, WHITE);
    }else if(life == 1){
        DrawTexturePro(h1,org2,loc1,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org2,loc2,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org1,loc3,(Vector2){0,0},0, WHITE);
    } else if(life >= 0){
        DrawTexturePro(h1,org2,loc1,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org2,loc2,(Vector2){0,0},0, WHITE);
        DrawTexturePro(h1,org2,loc3,(Vector2){0,0},0, WHITE);
        **go = 1;
        **f = 1;
    }
}


void DrawHealth(int life, int *go, Texture2D h1, int *f, int *h){
    Rectangle org1 = {0,0,10,11};
    Rectangle org2 = {10,0,10,11};
    Rectangle loc1 = {980, 20, org1.width * 3, org1.height * 3};
    Rectangle loc2 = {1012, 20, org1.width * 3, org1.height * 3};
    Rectangle loc3 = {1044, 20, org1.width * 3, org1.height * 3};

    if(hl == 0){
        CheckHealth(life, &go, h1, &f, org1, org2, loc1, loc2, loc3);
    } else if(hl == 2){
        CheckHealth(life, &go, h1, &f, org1, org2, loc1, loc2, loc3);
    } else if(hl == 4){
        CheckHealth(life, &go, h1, &f, org1, org2, loc1, loc2, loc3);
    }else if(hl == 6){
        CheckHealth(life, &go, h1, &f, org1, org2, loc1, loc2, loc3);
    } else if(hl == 8){
        CheckHealth(life, &go, h1, &f, org1, org2, loc1, loc2, loc3);
    }

    if(*h == 1 && hl <= 9){
        hl++;
    } else{
        hl = 0;
        *h = 0;
    }
    
}