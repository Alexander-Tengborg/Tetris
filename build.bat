g++ -c main.cpp -o main.o -I W:\SFML\include
g++ -c Game.cpp -o Game.o -I W:\SFML\include
g++ -c GameSounds.cpp -o GameSounds.o -I W:\SFML\include
g++ -c TetrisShape.cpp -o TetrisShape.o -I W:\SFML\include

::g++ .\main.o .\TetrisShape.o -o main.exe -L W:\SFML\lib -lsfml-system -lmingw32 -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-main -mwindows -lopengl32 -lwinmm -lgdi32 -DSFML_STATIC
g++ .\main.o .\Game.o .\GameSounds.o .\TetrisShape.o -o main.exe -L W:\SFML\lib -lsfml-system -lmingw32 -lsfml-graphics -lsfml-window -lsfml-audio -lopengl32 -lwinmm -lgdi32 -DSFML_STATIC
::Second command removes -lsfml-main -mwindows which allows you to use the terminal