#pragma once
#include <bits/stdc++.h>
#include "game.h"
#include "raylib.h"

const int screenw = 1500;
const int screenh = 1000;
Texture2D lvl1;
Texture2D lvl2;
Texture2D lvl3;
//bg
const int lvlcount = 3;
Texture2D levels[lvlcount];
Texture2D climblvl[lvlcount];
int clmetermax = 3;
void loadbg() {
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
void drawbg(){
    DrawTexture(levels[0],0,0,WHITE);
    int levelheight = 1000+clmetermax*1000;
    for(int i =0;i<lvlcount;i++){
        int bottom = -i*levelheight;
        for(int b=0;b<clmetermax;b++){
            DrawTexture(climblvl[i],0,bottom-(b+1)*1000,WHITE);
        }
        DrawTexture(levels[i],0,bottom,WHITE);
    }
}

// makestones(p1stones, 0,500) (500,1000 for p2)
void genstones(stones stone[], float left, float right){
    float x = (left+right)/2;
    float y = 900;
    for(int b=0;b<3;b++){
    for(int i =0;i<stonecount;i++){
        stone[i].pos = {x,y};
        stone[i].key = GetRandomValue(0,3);
        y -= GetRandomValue(150,300);
        x += GetRandomValue(-120,120);
        if(x<left+60) x = left + 60;
        if(x>right -60) x =right-60;
        

        }
    }
    //draw
    
}
void drawstones(stones stone[]){
    for(int i=0;i<stonecount;i++){
        DrawCircleV(stone[i].pos,20,GRAY);
    }
}
stones p1stones[stonecount];
stones p2stones[stonecount];
//creating ui
void drawplayer1(){
    Texture2D player1;
    int hitboxx;
    int hitboxy;
    
}