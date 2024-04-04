# Raylib Game of Life made with C

Learning C also, this one I made up, it pretty much does the same stuff v1 did

I think I prefer it rather a lot

I toyed with a recursive render loop, it worked great, but ultimately we use the tail-recursion pattern so the compiler can figure out what we're trying to do and refactor it into a while loop, so if you're doing it right.. you're not really doing it at all 

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

### Controls 

- Space to play and pause 
- Square brackets to change fps, `[` to slow down, `]` to speed up

When paused 
- C to clear 
- R to random fill
- Left click to toggle a cell 