#include "bits/stdc++.h"
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
   

    stones p1stones[stonecount];
    stones p2stones[stonecount];
    player p1 = createplayer(250,900,RED);
    player p2 = createplayer(1000,900,BLUE);


    // startmenu
    loadbg();
    splitscreen();
    while(running && !WindowShouldClose()){
        drawbg();
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
                    
                    genstones(p1stones,100,500);
                    genstones(p2stones,750,1500);     
                    
                }
                if(selected ==2){
                    running=false;
                }
            }
        }
        if(current == Screen::P1 || current == Screen::P2){
            if(IsKeyPressed(KEY_ESCAPE)){
                current = Screen::Menu;
            }
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
            drawstones(p1stones);
            drawp1gp();
            
            
            drawplayer(p1);
        }
        else if(current == Screen::P2){
            current = Screen::P2;
            

            drawstones(p1stones);
            drawstones(p2stones);
            
            drawp2gp();

           
            drawplayer(p1);

            
            drawplayer(p2);
            
        }
        EndDrawing();
    }
    UnloadRenderTexture(lefttex);
    UnloadRenderTexture(righttex);
    for(int i=0;i<lvlcount;i++){
        UnloadTexture(levels[i]);
        UnloadTexture(climblvl[i]);
    }
    CloseWindow();
}