# the-boulderer
tested with g++
the games written in c++ and uses the raylibs library 

# the game itself
the game has split screen capabilities, using IJKL and WASD as the controls. (up left down right)
in the game.h header, you can adjust the amount of rocks you can climb in the game btw (const int stonecount)

## how to build
download and install MSYS2 from:

    https://www.msys2.org/

use the default install location (C:\msys64) if possible.

open from the ucrt64 shell (make sure its ucrt64 msys, nothing else)

pop this command
pacman -S --needed mingw-w64-ucrt-x86_64-gcc \
        mingw-w64-ucrt-x86_64-raylib \
        mingw-w64-ucrt-x86_64-glfw

in the ucrt64 terminal, go to the project folder, for example:

    cd "/c/Users/YourName/Desktop/the-boulderer"

    
then compile with 
 g++ src/main.cpp -o game.exe -std=c++17 -O2 -lraylib \
        -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++

in the same terminal run ./game.exe or just open your newly created exe from the project folder

if theres any bugs lowkey let me know i actually do like the game idea a little bit and i actually wanna dev it a bit morre when i have time. 
thannkkkkss (my friend told me i should list how it correlates to theme also, so i was hoping that "split" would kinda follow the background where the mountain is split in half) ( and dcause theres splitscreen)
#sad that i ddi this on week 4 and not week 5