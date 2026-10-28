#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once

typedef struct score{
    int score;
    char nm[5];
    struct score* next;
}score;

// top 5 scores salvos

score* new_score(int s){
    score* ns = (score*) malloc(sizeof(score));
    ns -> score = s;
    fgets(ns -> nm, 5, stdin);
    ns -> nm[strcspn(ns -> nm, "\n")] = '\0';
    ns -> next = NULL;
    return ns;
} 

void make_five(score **curr){
    int count = 0;
    score* aux = *curr;
    for(int i = 0; i < 5; i++){
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

void add_score(score** curr, int s){
    score* ns = new_score(s);
    if(*curr == NULL){
        *curr = ns;
    } else if((*curr) -> score < ns -> score){
        ns -> next = *curr;
        *curr = ns;
    } else{
        score* aux = *curr;

        while(aux -> next != NULL){
            if(aux -> score > ns -> score){
                if (aux -> next -> score < ns -> score){
                    ns -> next = aux ->next;
                    aux -> next = ns;
                } else if(aux -> next -> score >= ns -> score){
                    aux = aux -> next;
                }
            } else if(aux -> score == ns -> score){
                if (aux -> next -> score < ns -> score){
                    ns -> next = aux -> next;
                    aux -> next = ns;
                } else{
                    aux = aux -> next;
                }
            } 
        }
        if(aux -> next == NULL){
            aux -> next = ns;
        }
        
    }
    make_five(&(*curr));

}