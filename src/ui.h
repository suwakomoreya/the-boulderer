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
    float y = 800;

    for(int i =0;i<stonecount;i++){
        stone[i].pos = {x,y};
        stone[i].key = GetRandomValue(0,3);
        y -= GetRandomValue(80,150);
        x += GetRandomValue(-120,120);
        if(x<left+60) x = left + 60;
        if(x>right -60) x =right-60;

    }
    
}

void drawstones(stones stone[], player& p){
    for(int i=0;i<stonecount;i++){
        if(ColorToInt(p.color) == ColorToInt(RED)){
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
        }
        else{
            switch(stone[i].key){
                case 0:
                    stone[i].reqkey = 'I';
                    break;
                case 1: 
                    stone[i].reqkey = 'J';
                    break;
                case 2:
                    stone[i].reqkey = 'K';
                    break;
                case 3:
                    stone[i].reqkey = 'L';
                    break;
            }
        }
        // std::string akey = std::to_string(stone[i].key);
        DrawCircleV(stone[i].pos,20,GRAY);
        DrawText(TextFormat("%c", stone[i].reqkey),stone[i].pos.x - 5,stone[i].pos.y - 15,30,WHITE);

    }
}
// stone arrays are defined in main.cpp
// uistone generation (not actual interactable stones)

//creating ui
void drawp1gp(const player& p){
    DrawText("Player 1", 60, 40, 32, RED);
    DrawText(TextFormat("Height: %d / %d", p.rock + 1, stonecount), 60, 80, 24, RAYWHITE);
}
void drawp2gp(const player& p){
    const char* label = "Player 2";
    const char* height = TextFormat("Height: %d / %d", p.rock + 1, stonecount);
    int labelW = MeasureText(label, 32);
    int heightW = MeasureText(height, 24);
    DrawText(label, screenw - 60 - labelW, 40, 32, BLUE);
    DrawText(height, screenw - 60 - heightW, 80, 24, RAYWHITE);
}
//create player;
player createplayer(float x,float y,Color color){
    player p;
    p.pos = {x,y};
    p.size = {50,50};
    p.speed = 60;
    p.color = color;
    p.rock = 0;
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
    drawstones(p1stones, p1);
    drawplayer(p1);
    EndMode2D();
    EndTextureMode();
    
    //p2
    followplayer(camright, p2,screenw*3/4.0f);

    BeginTextureMode(righttex);
    ClearBackground(BLACK);
    BeginMode2D(camright);
    drawbg();
    drawstones(p2stones, p2);
    drawplayer(p2);
    EndMode2D();
    EndTextureMode();
}

void displaysplitscreen(){
    Rectangle src = {0,0,(float)lefftex.texture.width, -(float)lefftex.texture.height};
    DrawTextureRec(lefftex.texture, src, {0,0},WHITE);
    DrawTextureRec(righttex.texture, src, {screenw/2.0f,0},WHITE);
    DrawRectangle(screenw/2 -1,0,2,screenh,Color{255,255,255,180});
}

// gameclimb
void rockclimb(player&p, stones s[]){
    
    if(p.rock<0 || p.rock >= stonecount){
        p.rock =0;
    }
    Vector2 target = {s[p.rock].pos.x - 25, s[p.rock].pos.y-25};
    float smooth = 7.0f;
    p.pos.x += (target.x-p.pos.x) * smooth * GetFrameTime();
    p.pos.y += (target.y - p.pos.y) * smooth * GetFrameTime();
    // p.pos = {(s[(p.rock)].pos.x)-25,s[p.rock].pos.y-25}; 
    
    int pressed=0;
    if(ColorToInt(p.color) == ColorToInt(RED)){
        if(IsKeyPressed(KEY_W)){
            pressed = 'W';

        }
        else if(IsKeyPressed(KEY_D)){
            pressed = 'D';
        }
        else if(IsKeyPressed(KEY_A)){
            pressed = 'A';
        }
        else if(IsKeyPressed(KEY_S)){
            pressed = 'S';
        }
    }
    else{
        if(IsKeyPressed(KEY_I)){
            pressed = 'I';
        }
        else if(IsKeyPressed(KEY_J)){
            pressed = 'J';
        }
        else if(IsKeyPressed(KEY_K)){
            pressed = 'K';
        }
        else if(IsKeyPressed(KEY_L)){
            pressed = 'L';
        }
    }


    if(pressed){
        if(p.rock < stonecount-1 && pressed == s[p.rock+1].reqkey){
            p.rock++;
        }
        else if(p.rock >0){
            p.rock--;
        }
    }
    /*if(p.rock >= stonecount-1){
        return;
    }*/
   /*
    if(p.rock >stonecount -1){
        p.rock = stonecount-1;
    }*/
    
}
void gamewin(player&p, bool splitscreenMode){
    if(!p.won) return;
    const char* label = (ColorToInt(p.color) == ColorToInt(RED)) ? "Player 1 wins" : "Player 2 wins";
    const char* hint = "Esc to return to menu";
    int w = 360;
    int h = 110;
    int x = (screenw - w) / 2;
    int y = 430;
    if(splitscreenMode){
        x = (ColorToInt(p.color) == ColorToInt(RED)) ? (screenw/4 - w/2) : (screenw*3/4 - w/2);
    }
    DrawRectangle(x, y, w, h, Color{20, 20, 20, 200});
    DrawRectangleLines(x, y, w, h, Color{255,255,255,60});
    int textW = MeasureText(label, 34);
    int hintW = MeasureText(hint, 20);
    DrawText(label, x + (w - textW)/2, y + 22, 34, RAYWHITE);
    DrawText(hint, x + (w - hintW)/2, y + 66, 20, Color{220,220,220,255});
}