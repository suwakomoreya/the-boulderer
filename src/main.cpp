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
                if(selected == 0){ // one player bro bro bro 
                    current = Screen::P1;
                    genstones(p1stones,0,500);
                  
                }
                if(selected==1){ //SPLITSCREEN p2
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
        if(current == Screen::P2){
            drawsplitscreen(p1,p2,p1stones,p2stones);
        }

        // temporary movement (splitscreen test)
        if(current== Screen::P1 || current == Screen::P2){
            if(IsKeyPressed(KEY_W)){
                p1.pos.y-=40;
            }
            if(IsKeyPressed(KEY_A)){
                p1.pos.x-=40;

            }
            if(IsKeyPressed(KEY_S)){
                p1.pos.y+=40;
            }
            if(IsKeyPressed(KEY_D)){
                p1.pos.x+=40;
            }
            //p2 movement
            if(IsKeyPressed(KEY_UP)){
                p2.pos.y-=40;

            }
            if(IsKeyPressed(KEY_LEFT)){
                p2.pos.x-=40;

            }
            if(IsKeyPressed(KEY_DOWN)){
                p2.pos.y+=40;
            }
            if(IsKeyPressed(KEY_RIGHT)){
                p2.pos.x+=40;
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
            displaysplitscreen();

            drawp1gp();
            drawp2gp();

           
            
            
        }
        EndDrawing();
    }
    UnloadRenderTexture(lefftex);
    UnloadRenderTexture(righttex);
    for(int i=0;i<lvlcount;i++){
        UnloadTexture(levels[i]);
        UnloadTexture(climblvl[i]);
    }
    CloseWindow();
}