#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
struct player{
    Vector2 pos;
    Vector2 size;
    float speed;
    Color color;
    enum checkpoint{
        Ground,
        One,
        Two,
        Three
    };
    int rock=0;
    bool won=false;
    int keypress; 
    // 0 = up w
    // 1 = right d
    // 2 = down a
    // 3 = left a
};
struct stones{
    Vector2 pos;
    int key;
    char reqkey;
    int dropamt =2;
};
const int stonecount = 75;
stones stone[stonecount];
