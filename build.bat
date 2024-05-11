g++ -c .\src\main.cpp -o .\build\main.o -I W:\SFML\include
g++ -c .\src\Game.cpp -o .\build\Game.o -I W:\SFML\include
g++ -c .\src\GameSounds.cpp -o .\build\GameSounds.o -I W:\SFML\include
g++ -c .\src\TetrisShape.cpp -o .\build\TetrisShape.o -I W:\SFML\include

::g++ .\main.o .\TetrisShape.o -o main.exe -L W:\SFML\lib -lsfml-system -lmingw32 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-main -mwindows -lopengl32 -lwinmm -lgdi32 -DSFML_STATIC
g++ .\build\main.o .\build\Game.o .\build\GameSounds.o .\build\TetrisShape.o -o .\build\main.exe -L W:\SFML\lib -lsfml-system -lmingw32 -lsfml-graphics -lsfml-window -lsfml-audio -lopengl32 -lwinmm -lgdi32 -DSFML_STATIC
::Second command removes -lsfml-main -mwindows which allows you to use the terminal