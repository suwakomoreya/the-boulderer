#include <bits/stdc++.h>
#include <raylib.h>
#include "ui.h"
#include "game.h"

int main(){
    InitWindow(screenw,screenh,"Boulderer");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    //init
    
    //Start menu
    enum class Screen {
        Menu,
        P1,
        P2,
        Exit
    };
    Screen current = Screen::Menu;
    const char*items[] = {
        "One player",
        "Two player",
        "Exit"
    };
    const int count =3;
    int selected =0;
    bool running = true;
    player player{
        .pos = {0,0},
        .size = {0,0},
        .speed = 60,
        .color = RED,
    };

    stones p1stones[stonecount];
    stones p2stones[stonecount];


    // startmenu
    //loadbg();
    while(running && !WindowShouldClose()){
        // drawbg();
        //update
        if(current == Screen::Menu){
            if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
                selected = (selected+1)% count;

            }
            if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
                selected = (selected-1+count)% count;
            }
            if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)){
                if(selected == 0){
                    current = Screen::P1;
                    genstones(p1stones,0,500);
                }
                if(selected==1){
                    current = Screen::P2;
                    genstones(p1stones,0,500);
                    genstones(p2stones,500,100);     
                }
                if(selected ==2){
                    running=false;
                }
            }
        }
        if(current == Screen::P1){
            
        }
        BeginDrawing();
        ClearBackground(BLACK);
        
        //select choice
        if(current == Screen::Menu){
            DrawText("The Boulderer", 250, 100, 80,WHITE);
            for(int i =0;i<count;i++){
                Color c =(i ==selected) ?YELLOW : GRAY;
                DrawText(items[i],350,250+i*70,50,c);
                if(i==selected){
                    DrawText(">",320,250 +i *70,50, YELLOW);
                }

            }

        }  
        else if(current == Screen::P1){
            current = Screen::P1;
            DrawText("P1",200,280,25,WHITE);
            drawstones(p1stones);
        }
        else if(current == Screen::P2){
            current = Screen::P2;
            DrawText("P2",200,280,25,WHITE);
            drawstones(p1stones);
            drawstones(p2stones);
        }
        EndDrawing();
    }
    CloseWindow();
}