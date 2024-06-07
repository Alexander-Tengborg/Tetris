cmake_minimum_required(VERSION 3.16)
project(Tetris LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

add_executable(Tetris src/main.cpp src/Game.cpp src/GameSounds.cpp src/TetrisShape.cpp src/Ui.cpp)
target_link_libraries(Tetris PRIVATE sfml-graphics sfml-audio)
target_compile_features(Tetris PRIVATE cxx_std_17)

add_custom_command(
    TARGET Tetris POST_BUILD
    COMMENT "Copying resource folder to the build folder"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources/
            $<TARGET_FILE_DIR:Tetris>/resources/
)

if(WIN32)
    add_custom_command(
        TARGET Tetris PRE_BUILD
        COMMENT "Copy OpenAL DLL" 
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
                $<TARGET_FILE_DIR:Tetris> VERBATIM)
endif()