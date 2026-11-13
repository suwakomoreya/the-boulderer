#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
struct player{
    Vector2 pos;
    Vector2 size;
    float speed;
    Color color;
};
struct stones{
    Vector2 pos;
    int key;
    int dropamt;
};
const int stonecount = 75;
stones stone[stonecount];
