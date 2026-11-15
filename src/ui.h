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
//bg generation
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
// stone generation
// makestones(p1stones, 0,500) (500,1000 for p2)
void genstones(stones stone[], float left, float right){
    float x = (left+right)/2;
    float y = 900;

    for(int i =0;i<stonecount;i++){
        stone[i].pos = {x,y};
        stone[i].key = GetRandomValue(0,3);
        y -= GetRandomValue(80,150);
        x += GetRandomValue(-120,120);
        if(x<left+60) x = left + 60;
        if(x>right -60) x =right-60;

    }
    
}

void drawstones(stones stone[]){
    for(int i=0;i<stonecount;i++){
        
        switch(stone[i].key){
            case 0:
                stone[i].reqkey = 'W';
                break;
            case 1:
                stone[i].reqkey = 'D';
                break;
            case 2:
                stone[i].reqkey = 'S';
                break;
            case 3:
                stone[i].reqkey = 'A';
                break;
        }
        
        // std::string akey = std::to_string(stone[i].key);
        DrawCircleV(stone[i].pos,20,GRAY);
        DrawText(TextFormat("%c", stone[i].reqkey),stone[i].pos.x - 5,stone[i].pos.y - 15,30,WHITE);

    }
}
stones p1stones[stonecount];
stones p2stones[stonecount];
// uistone generation (not actual interactable stones)

//creating ui
void drawp1gp(){
    DrawText("Player 1",200,100,40,RED);
    DrawText("Height",250,200,40,RED);

}
void drawp2gp(){
    drawp1gp();
    DrawText("Player 2", screenw-400,100,40,BLUE);
    DrawText("Height",screenw-350,200,40,BLUE);

}
//create player;
player createplayer(float x,float y,Color color){
    player p;
    p.pos = {x,y};
    p.size = {50,50};
    p.speed = 60;
    p.color = color;
    return p;
}
void drawplayer(const player& p){
    DrawRectangleV(p.pos,p.size,p.color);
}


// camera understanding
RenderTexture2D lefftex, righttex;
Camera2D cammain ={0}, camleft ={0}, camright ={0};
//lowkey just smoother camera transitions
void followplayer(Camera2D& cam, const player&p, float lanecenterX){
    const float trigger = 400; 
    const float smooth = 3.0f; // higher values will snap more
    float playerY = p.pos.y +p.size.y/2;

    float desired = playerY + (screenh/2.0f-trigger);
    if(desired> screenh/2.0f){
        desired = screenh/2.0f;
    }
    cam.target.y += (desired-cam.target.y)* smooth *GetFrameTime();
    cam.target.x = lanecenterX;

}


void splitscreen(){
    lefftex = LoadRenderTexture(screenw/2,screenh);
    righttex = LoadRenderTexture(screenw/2, screenh);
    cammain.zoom = 1.0f;
    camleft.zoom = 1.0f;
    camright.zoom = 1.0f;
    camleft.target = {screenw/4.0f, screenh/2.0f};
    camright.target = {screenw*3/4.0f, screenh/2.0f};
    cammain.target = {screenw/2.0f, screenh/2.0f};
    cammain.offset = {screenw/2.0f, screenh/2.0f};
    camleft.offset = {screenw/4.0f, screenh/2.0f};
    camright.offset= {screenw/4.0f, screenh/2.0f};
}
void drawsplitscreen(player& p1, player& p2, stones p1stones[], stones p2stones[]){
    followplayer(camleft, p1,screenw/4.0f);

    BeginTextureMode(lefftex);
    ClearBackground(BLACK);
    BeginMode2D(camleft);
    drawbg();
    drawstones(p1stones);
    drawplayer(p1);
    EndMode2D();
    EndTextureMode();
    
    //p2
    followplayer(camright, p2,screenw*3/4.0f);

    BeginTextureMode(righttex);
    ClearBackground(BLACK);
    BeginMode2D(camright);
    drawbg();
    drawstones(p2stones);
    drawplayer(p2);
    EndMode2D();
    EndTextureMode();
}

void displaysplitscreen(){
    Rectangle src = {0,0,(float)lefftex.texture.width, -(float)lefftex.texture.height};
    DrawTextureRec(lefftex.texture, src, {0,0},WHITE);
    DrawTextureRec(righttex.texture, src, {screenw/2.0f,0},WHITE);
    DrawRectangle(screenw/2 -2,0,4,screenh,WHITE);
}

// gameclimb

void rockclimb(player&p, stones s[]){
    p.pos = {(s[p.rock].pos.x)-25,s[p.rock].pos.y-25};
    if(p.rock != stonecount){
        if(p.keypress == stone[p.rock+1].reqkey){ // remember that raylib keypresses are actually asci inputs
            p.rock++;
        }
        else{
            p.rock--;
        }
    }
    else{
        p.rock =0;
    }
}