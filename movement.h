#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

void move(Vector2 *c){
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            c -> x -= GetFrameTime() * 270;
    } else if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            c -> x += GetFrameTime() * 270;
    }
}

extern int flip = 32;
extern int rot = 0;

//Player sprite is 32x32

void DrawPlayer(Texture2D player, Texture2D wheel, Vector2 *loc){
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            flip = -32;
            rot -= 15;
    }
        if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            flip = 32;
            rot += 15;
    }
    
    //Player refs
    Rectangle org1 = (Rectangle){0, 0, flip,32};
    Rectangle dest1 = (Rectangle){loc -> x, loc -> y,org1.width * 3.5,org1.height * 3.5};

    //Wheel refs

    Rectangle org2 = (Rectangle){0,0, 6, 6};
    Rectangle dest2 = (Rectangle){(loc -> x) + 86, (loc -> y) + 105, org2.width * 3.5,org2.height * 3.5};
    Rectangle dest3 = (Rectangle){(loc -> x) + 26, (loc -> y) + 105, org2.width * 3.5,org2.height * 3.5};
    
    //Player draw
    DrawTexturePro(player, org1, dest1, (Vector2) {0, 0}, 0, WHITE);
    

    //wheel draw
    DrawTexturePro(wheel, org2, dest2, (Vector2) {dest2.width/2, dest2.height/2}, rot, WHITE);
    DrawTexturePro(wheel, org2, dest3, (Vector2) {dest3.width/2, dest3.height/2}, rot, WHITE);


}