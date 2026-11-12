#include <bits/stdc++.h>
#include "raylib.h"

const int screenw = 1000;
const int screenh = 1000;
Texture2D lvl1;
Texture2D lvl2;
Texture2D lvl3;
//bg
const int lvlcount = 3;
Texture2D levels[lvlcount];
Texture2D climblvl[lvlcount];
int clmetermax = 3;
void drawbg() {
    for(int i=0; i<lvlcount; i++){
        levels[i] = LoadTexture(TextFormat("assets/level/bg%d.png",i));
        climblvl[i] = LoadTexture(TextFormat("assets/levelc/bg%d.png",i));
    }
    DrawTexture(levels[0],0,0,WHITE);
    int levelheight = 1000+clmetermax*1000;
    for(int i=0; i<lvlcount; i++){
        int bottom = -i * levelheight;
        for(int b=0; b<clmetermax; b++){
            DrawTexture(climblvl[i],0,bottom-(b+1)*1000,WHITE);
        }
        DrawTexture(levels[i],0,bottom,WHITE);
    }
    
}

//creating ui
void drawplayer1(){
    Texture2D player1;
    int hitboxx;
    int hitboxy;
    
}