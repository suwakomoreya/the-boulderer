#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
typedef struct{
    Vector2 pos;
    Vector2 size;
    float speed;
    Color color;
} player;
typedef struct{
    Vector2 pos;
    int key;
    int dropamt;
} stones;
const int stonecount = 75;
stones stone[stonecount];
