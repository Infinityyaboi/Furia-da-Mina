#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include <stdbool.h>
#include "items.h"
#include "movement.h"
#include "highscore.h"
#include "menu.h"

#define RAYGUY_IMPLEMENTATION
#include "raygui.h"


int init = 0;
int life = 3;
int menu = 0;
int cs = 0;
int gameover = 0;
Texture2D p;
Texture2D w;
Texture2D foreground;
Texture2D background;
Texture2D h1;
int framecheck = 0;
int freeze = 0;
int hittrue = 0;
bool editmode = false;
char fsn[50] = "NAME";

void resetGame(){
    if(menu == 1){
        reset_pos();
        life = 3; // restaura a vida do jogador
        cs = 0;     // reseta a pontuação
        gameover = 0;
        freeze = 0;
        clearItems();
    }
}


void main()
{
    p.id = 0;

    // X, Y
    InitWindow(1150, 650, "Furia da Mina");
    InitAudioDevice();



    SetTargetFPS(30);
    // load scores

    ItemsStart();


    while (!WindowShouldClose()){

        // caixa de collisão do jogador
        Rectangle plyrColl = {playerPos.x + 20, playerPos.y + 50, (32.0 * 3.5) - 20, ((32.0 * 3.5) - 50.0)};

        BeginDrawing();

        if (menu == 0){
            // main menu

            if (init == 0){
                if (start.texture.id == 0){
                    start.texture = LoadTexture("sprites/buttons/butstart.png");
                    controls.texture = LoadTexture("sprites/buttons/butcontrols.png");
                    leave.texture = LoadTexture("sprites/buttons/butexit.png");
                    credits.texture = LoadTexture("sprites/buttons/butcredits.png");
                }
                if (p.id > 0){
                    UnloadTexture(p);
                    UnloadTexture(w);
                    UnloadTexture(h1);
                    UnloadTexture(foreground);
                    UnloadTexture(background);
                    UnloadTexture(Gold.sprite);
                    UnloadTexture(Ruby.sprite);
                    UnloadTexture(Diamond.sprite);
                    UnloadTexture(Emerald.sprite);
                    UnloadTexture(Bomb.sprite);
                    UnloadTexture(gameResume.texture);
                    UnloadTexture(gameRestart.texture);
                    UnloadTexture(gameMainMenu.texture);
                    UnloadTexture(gamePause.texture);
                    UnloadTexture(submit.texture);
                    p.id = 0;
                }
                if(hsRestart.texture.id > 0){
                    UnloadTexture(hsRestart.texture);
                    UnloadTexture(hsMainMenu.texture);
                    hsRestart.texture.id = 0;
                }
                init = 1;
            }
            ClearBackground((Color){46, 52, 64, 255});
            // load_big_button(&start, 1);

            if (load_button(&start, 3) == 1 || IsKeyPressed(KEY_S)){
                menu = 1;
                init = 0;
                resetGame();
            }

            if (load_button(&controls, 3) == 1 || IsKeyPressed(KEY_C)){
                menu = 2;
            }
            if(load_button(&credits, 3) == 1){
                menu = 3;
            }
            if(load_button(&leave, 3) == 1){
                CloseWindow();
            }

        }
        else if (menu == 1){
            // game screen

            if (init == 0){
                if (start.texture.id > 0){
                    UnloadTexture(start.texture);
                    UnloadTexture(controls.texture);
                    UnloadTexture(leave.texture);

                    start.texture.id = 0;
                }
                if (p.id == 0){
                    foreground = LoadTexture("sprites/Background/Cave_fore.png");
                    background = LoadTexture("sprites/Background/Cave_back.png");
                    p = LoadTexture("sprites/player.png");
                    w = LoadTexture("sprites/wheels.png");
                    Gold.sprite = LoadTexture("sprites/Gold.png");
                    Ruby.sprite = LoadTexture("sprites/Ruby.png");
                    Diamond.sprite = LoadTexture("sprites/Diamond.png");
                    Emerald.sprite = LoadTexture("sprites/Emerald.png");
                    Bomb.sprite = LoadTexture("sprites/dynamite.png");
                    h1 = LoadTexture("sprites/Hearts.png");
                    gameResume.texture = LoadTexture("sprites/buttons/butresume.png");
                    gameRestart.texture = LoadTexture("sprites/buttons/butrestart.png");
                    gameMainMenu.texture = LoadTexture("sprites/buttons/butMainMenu.png");
                    gamePause.texture = LoadTexture("sprites/buttons/butpause.png");
                    submit.texture = LoadTexture("sprites/buttons/butsubmit.png");
                }
                if(hsRestart.texture.id > 0){
                    UnloadTexture(hsRestart.texture);
                    UnloadTexture(hsMainMenu.texture);
                    hsRestart.texture.id = 0;
                }
                init = 1;
            }

            ClearBackground(RAYWHITE);

            // 0,0 coordinate

            

            

            move(cs, freeze);
            DrawBackground(background);
            DrawPlayer(p, w, cs, freeze, &hittrue);

            // Soma o tempo que passou desde o último frame
            float tl = getTimeLimit(cs);
            // Se passou o tempo limite, tenta criar um item novo
            itemLogic(&cs, plyrColl, &life, &gameover, tl, freeze, &hittrue);

            DrawText(TextFormat("SCORE: %d", cs), 30, 60, 20, (Color){180, 167, 232, 240});
            DrawForeground(foreground);
            DrawHealth(life, &gameover, h1, &freeze, &hittrue);

            if (IsKeyPressed(KEY_G)){
                freeze = 1;
                gameover = 1;
            }
            if(load_button(&gamePause, 1.5) == 1 || IsKeyPressed(KEY_P)){
                freeze = 1;
                framecheck = 0;
            }
            if (IsKeyPressed(KEY_R) && gameover == 0){
                resetGame();
            }

            if(freeze == 1 && gameover == 0){
                DrawRectangle(0, 0, 1150, 650, (Color){46, 52, 64, 150});
                DrawRectangle(350, 160, 420, 300, (Color){46, 52, 64, 255});
                if(load_button(&gameResume, 3) == 1 || (IsKeyPressed(KEY_P) && framecheck >= 1)){
                    freeze = 0;
                    framecheck = 0;
                }
                framecheck++;
                if(load_button(&gameRestart, 3) == 1){
                    resetGame();
                }
                if(load_button(&gameMainMenu, 3) == 1 || IsKeyPressed(KEY_M)){
                    resetGame();
                    menu = 0;
                    init = 0;
                }
            }else if(freeze == 1 && gameover == 1){
                DrawRectangle(0, 0, 1150, 650, (Color){46, 52, 64, 150});
                DrawRectangle(330, 240, 450, 240, (Color){46, 52, 64, 255});
                DrawText(TextFormat("Final Score: %d", cs), 350, 270, 25, WHITE);

                // fix this
                //if(GuiTextBox((Rectangle) {350, 370}, &fsn, 25, editmode)){
                //    editmode = !editmode;
                //}

                if(load_button(&submit, 3) == 1){
                    menu = 4;
                    init = 0;
                }
            }

        }else if(menu == 2){
            // menu de controles
            ClearBackground((Color){46, 52, 64, 255});
            DrawText(TextFormat("Use as setas ou teclas A e D para se mover!", cs), 210, 60, 30, WHITE);
            DrawText(TextFormat("Colete minerios e evite as bombas", cs), 280, 120, 30, WHITE);
            DrawText(TextFormat("Ouro vale 500, Ruby 1000, Diamante 15000 e Esmeralda 25000", cs), 230, 180, 20, WHITE);
            DrawText(TextFormat("Use consegue recuperar vida com pontos", cs), 260, 230, 30, WHITE);
            DrawText(TextFormat("O Ima pode ser usado para atrair items boms", cs), 230, 280, 30, WHITE);
            DrawText(TextFormat("Começa com 3 vidas", cs), 400, 340, 30, WHITE);
            DrawText(TextFormat("Collete o escudo para defender contra um ataque", cs), 200, 390, 30, WHITE);


            if(load_button(&leave, 3) == 1){
                menu = 0;
            }
        }else if (menu == 3){
            ClearBackground((Color){46, 52, 64, 255});
            DrawText(TextFormat("Paulo André Lopes de Almeida", cs), 210, 60, 30, WHITE);
            DrawText(TextFormat("Enzo", cs), 210, 120, 30, WHITE);
            DrawText(TextFormat("@Rintrynter", cs), 210, 180, 30, WHITE);
            DrawText(TextFormat("Minecraft", cs), 210, 240, 30, WHITE);

            if(load_button(&leave, 3) == 1){
                menu = 0;
            }
        }else if (menu == 4){
            // Leaderboard
            if (init == 0){
                if (hsRestart.texture.id == 0){
                    hsRestart.texture = LoadTexture("sprites/buttons/butrestart.png");
                    hsMainMenu.texture = LoadTexture("sprites/buttons/butMainMenu.png");
                }
                if (p.id > 0){
                    UnloadTexture(p);
                    UnloadTexture(w);
                    UnloadTexture(h1);
                    UnloadTexture(foreground);
                    UnloadTexture(background);
                    UnloadTexture(Gold.sprite);
                    UnloadTexture(Ruby.sprite);
                    UnloadTexture(Diamond.sprite);
                    UnloadTexture(Emerald.sprite);
                    UnloadTexture(Bomb.sprite);
                    UnloadTexture(gameResume.texture);
                    UnloadTexture(gameRestart.texture);
                    UnloadTexture(gameMainMenu.texture);
                    UnloadTexture(gamePause.texture);
                    UnloadTexture(submit.texture);
                    p.id = 0;
                }
                init = 1;
            }

            ClearBackground((Color){46, 52, 64, 255});

            if(load_button(&hsRestart,3) == 1 || IsKeyPressed(KEY_R)){
                menu = 1;
                init = 0;
                resetGame();
                // save scores
            }
            if(load_button(&hsMainMenu,3) == 1 || IsKeyPressed(KEY_R)){
                menu = 0;
                init = 0;
                // save scores
            }
            
        }
            
        EndDrawing();
    }
    // save scores
    if (start.texture.id > 0)
    {
        UnloadTexture(start.texture);
        UnloadTexture(controls.texture);
        UnloadTexture(leave.texture);
    }
    if (p.id > 0)
    {
        UnloadTexture(h1);
        UnloadTexture(p);
        UnloadTexture(w);
        UnloadTexture(Gold.sprite);
        UnloadTexture(Ruby.sprite);
        UnloadTexture(Diamond.sprite);
        UnloadTexture(Emerald.sprite);
        UnloadTexture(Bomb.sprite);
        UnloadTexture(gameResume.texture);
        UnloadTexture(gameRestart.texture);
        UnloadTexture(gameMainMenu.texture);
        UnloadTexture(foreground);
        UnloadTexture(background);
    }

    CloseAudioDevice();
    CloseWindow();
}


// Codigo para manter os pontos 1/2
// Codigo para salvar o high score
// Leaderboard de score