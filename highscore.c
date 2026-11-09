#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include <math.h>
#include <stdbool.h>
#include "highscore.h"




// top 5 scores salvos

score* new_score(int s, char *nm){
    score* ns = (score*) malloc(sizeof(score));
    ns -> score = s;
    strcpy(ns->nm, nm);
    ns -> next = NULL;
    return ns;
} 

void make_five(score **curr){
    if(*curr == NULL){
        return;
    }

    int count = 0;
    score* aux = *curr;
    for(int i = 0; i < 4; i++){
        if(aux ->next == NULL){
            break;
        }
        aux = aux -> next;
        count += 1;
    }
    if(aux -> next != NULL && count >= 4){
        free(aux -> next);
        aux -> next = NULL;
    }
}

void add_score(score** curr, int s, char *nm, int *hs){
    score* ns = new_score(s, nm);
    if (*curr == NULL || (*curr)->score < s) {
        ns->next = *curr;
        *hs = s;
        *curr = ns;
    } else{
        score* aux = *curr;

        while(aux -> next != NULL && aux->next->score >= s){
            aux = aux->next;
        }
        ns->next = aux->next;
        aux->next =ns;
    }
    make_five(&(*curr));

}

Color SILVER = {157, 161, 168, 255};
Color BRONZE = {138, 76, 34, 255};

void DrawLB(score ** curr){
    if(*curr == NULL){
        DrawText(TextFormat("No current scores"), 450, 250, 20, WHITE);
    } else{
        score *aux = *curr;
        int cs = 1;
        int h = 150;
        while(aux != NULL){
            if (cs == 1){
                DrawRectangle(350, h, 50, 50, GOLD);
                DrawRectangle(410, h, 250, 50, (Color){12, 22, 41, 255});
            } else if (cs == 2){
                DrawRectangle(350, h, 50, 50, SILVER);
                DrawRectangle(410, h, 250, 50, (Color){12, 22, 41, 255});
            } else if (cs == 3){
                DrawRectangle(350, h, 50, 50, BRONZE);
                DrawRectangle(410, h, 250, 50, (Color){12, 22, 41, 255});
            } else{
                DrawRectangle(350, h, 50, 50, (Color){12, 22, 41, 255});
                DrawRectangle(410, h, 250, 50, (Color){12, 22, 41, 255});
            }

            DrawText(TextFormat("%d", cs), 370, h + 10, 30, WHITE);
            DrawText(aux->nm, 450, h + 10, 30, WHITE);
            DrawText(TextFormat("%d", aux->score), 670, h+10, 30, WHITE);
            h += 60;
            cs++;
            aux = aux ->next;
        }
    }

}