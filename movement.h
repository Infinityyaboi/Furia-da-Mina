#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <raylib.h>
#pragma once

extern Vector2 playerPos;

void move(int s);

void DrawPlayer(Texture2D player, Texture2D wheel, int s);

void reset_pos();