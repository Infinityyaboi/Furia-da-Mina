#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once

typedef struct score{
    int score;
    char nm[50];
    struct score* next;
}score;


void add_score(score** curr, int s, char *nm, int *hs);

void DrawLB(score ** curr);