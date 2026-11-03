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

score* new_score(int s);

void add_score(score** curr, int s);