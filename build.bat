g++ -c main.cpp -o main.o -I W:\SFML\include
g++ .\main.o -o main.exe -L W:\SFML\lib -lsfml-system -lmingw32 -lsfml-graphics -lsfml-window -lsfml-main -mwindows -lopengl32 -lwinmm -lgdi32 -DSFML_STATIC
::g++ -L W:\SFML\lib .\main.o -o main.exe -l mingw32 -l sfml-graphics-s -l sfml-window-s -l sfml-system-s -l opengl32 -l freetype -l winmm -mwindows -l sfml-main -D SFML_STATIC