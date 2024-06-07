
# Tetris
Tetris written in C++ using the SFML library. Uses the latest development version of SFML, SFML 3.
By pressing the V key you can enable a very distracting moving background :D
![image](https://github.com/Alexander-Tengborg/Tetris/assets/14126933/a52d1393-01a0-4904-987b-8421bc86b267)


## Controls
**Left arrow key**: Move Left
**Right arrow key**: Move Right
**Up arrow key**: Rotate Clockwise
**Down arrow key**: Soft Drop
**Space**: Hard Drop
**C**: Hold Piece
**V**: Enable/Disable the shader for the game background

## Downloading the game
Install Git and CMake, then clone this repo.
On Linux, the following dependencies may need to be downloaded:
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```


## Building the game

Run one of the two following sets of command, depending on if you have a single-configuration or multi-configuration generator.

For a single-configuration generator (typically the case on Linux and macOS):
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

For a multi-configuration generator (typically the case on Windows):
```
cmake -S . -B build
cmake --build build --config Release
```

Running these commands will download and build SFML, as well as build the game into the ```/build/bin/``` folder.

## Running the game
The game's executable can now be run, and is found in ```/build/bin/```
