#include <bits/stdc++.h>
#include <raylib.h>
#include "ui.h"

const int screenw =1920;
const int screenh = 1080;


int main(){
    InitWindow(screenw,screenh,"Boulderer");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
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

    while(running && !WindowShouldClose()){
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
                }
                if(selected==1){
                    current = Screen::P2;
                }
                if(selected ==2){
                    running=false;
                }
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        if(current == Screen::Menu){
            DrawText("The Boulderer", 250, 100, 40,WHITE);
            for(int i =0;i<count;i++){
                Color c =(i ==selected) ?YELLOW : GRAY;
                DrawText(items[i],350,250+i*50,30,c);
                if(i==selected){
                    DrawText(">",320,250 +i *50,30, YELLOW);
                }

            }

        }  
        else if(current == Screen::P1){
            DrawText("P1",200,280,25,WHITE);
        }
        else if(current == Screen::P2){
            DrawText("P2",200,280,25,WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
}