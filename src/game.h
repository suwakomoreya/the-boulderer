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
    int rock=0; //how high up you are
    bool won=false;
    int keypress;  // ascii?
    // 0 = up w
    // 1 = right d
    // 2 = down a
    // 3 = left a
};
struct stones{
    Vector2 pos;
    int key; // required key
    char reqkey; // required key displayed
    int dropamt =2; // how far you be dropping
};
const int stonecount = 75;
stones stone[stonecount];
