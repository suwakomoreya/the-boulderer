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
        //update
        if(current == Screen::Menu){
            if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
                selected = (selected+1)% count;

            }
            if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
                selected = (selected-1+count)% count;
            }
            if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)){
                if(selected == 0){ // one player
                    current = Screen::P1;
                    genstones(p1stones,100,1000);
                    p1 = createplayer(750,900,RED);
                }
                if(selected==1){ // split screen
                    current = Screen::P2;
                    genstones(p1stones,100,500);
                    genstones(p2stones,750,1500);
                    p1 = createplayer(250,900,RED);
                    p2 = createplayer(1000,900,BLUE);
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
        /*
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
        */
        
        BeginDrawing();
        ClearBackground(BLACK);
        //select choice
        if(current == Screen::Menu){
            drawbg();
            DrawRectangle(300, 70, 900, 420, Color{0, 0, 0, 110});
            const char* title = "The Boulderer";
            int titleW = MeasureText(title, 72);
            DrawText(title, (screenw - titleW)/2, 120, 72, RAYWHITE);
            for(int i =0;i<count;i++){
                Color c =(i ==selected) ? RAYWHITE : Color{200,200,200,255};
                int itemW = MeasureText(items[i], 42);
                int x = (screenw - itemW)/2;
                int y = 260 + i*70;
                if(i==selected){
                    DrawText(">", x - 36, y, 42, RAYWHITE);
                }
                DrawText(items[i], x, y, 42, c);
            }
        }  
        else if(current == Screen::P1){
            followplayer(cammain,p1,screenw/2.0f);
            BeginMode2D(cammain);
            drawbg();
            drawstones(p1stones,p1);
            drawplayer(p1);
            EndMode2D();
            rockclimb(p1,p1stones);
            drawp1gp(p1);
            if(p1.rock == stonecount-1){
                p1.won = true;
            }
            gamewin(p1,false);
        }
        else if(current == Screen::P2){
            displaysplitscreen();
            rockclimb(p1,p1stones);
            rockclimb(p2,p2stones);
            drawp1gp(p1);
            drawp2gp(p2);
            if(p1.rock == stonecount-1){
                p1.won = true;
            }
            if(p2.rock == stonecount-1){
                p2.won = true;
            }
            gamewin(p1,true);
            gamewin(p2,true);
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