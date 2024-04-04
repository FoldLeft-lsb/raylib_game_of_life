# Raylib Game of Life made with c++ 

Learning C++, I followed this tutorial

https://github.com/educ8s/CPP-Game-Of-Life-with-raylib

### Setup

Install Raylib in some way, I built from source in static mode 

For now I'm using a shell script to build, I'm using clang because the editor plugin uses it

### Target Native 

Raylib built in static mode for PLATFORM_DESKTOP

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

### Target Web 

Emscripten installed, Raylib built with PLATFORM_WEB 

To compile 
```
chmod +x build_web_ems.sh
./build_web_ems.sh
```

Use a Python or Node simple http server on public/ to run

```
http-server public
```

Navigate to localhost:8080 

### Controls 

- Space to play and pause 
- Square brackets to change fps, `[` to slow down, `]` to speed up

When paused 
- C to clear 
- R to random fill
- Left click to toggle a cell 