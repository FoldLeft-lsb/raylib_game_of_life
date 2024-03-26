# Raylib Game of Life made with c++ 

Learning C++, I followed this tutorial

https://github.com/educ8s/CPP-Game-Of-Life-with-raylib

### Setup

Install Raylib in some way, I built from source in static mode 

For now I'm using a shell script to build, I'm using clang because the editor plugin uses it

To compile 
```
chmod +x build_linux.sh
./build_linux.sh
```

Or edit the script for your platform


To execute 
```
./main 
```

### Controls 

- Space to play and pause 
- Square brackets to change fps, `[` to slow down, `]` to speed up

When paused 
- C to clear 
- R to random fill
