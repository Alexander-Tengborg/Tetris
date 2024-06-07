#include "GameSounds.h"

//If we can't load a sound, the game can still keep running
void GameSounds::loadSounds() {
    if(!m_move_buffer.loadFromFile("./resources/sounds/stop.wav")) {
        std::cout << "Failed to load stop.wav" << "\n";
    }
    m_move_sound.setBuffer(m_move_buffer);

    if(!m_line_clear_buffer.loadFromFile("./resources/sounds/success-fanfare-trumpets-6185.mp3")) {
        std::cout << "Failed to load success-fanfare-trumpets-6185.mp3" << "\n";
    }
    m_line_clear_sound.setBuffer(m_line_clear_buffer);

    if(!m_theme.openFromFile("./resources/music/tetris_theme.mp3")) {
        std::cout << "Failed to load tetris_theme.mp3" << "\n";
    }
    m_theme.setLoop(true);
}

void GameSounds::playMoveSound() {
    m_move_sound.play();
}

void GameSounds::playLineClearSound() {
    m_line_clear_sound.play();
}

void GameSounds::playTheme() {
    m_theme.play();
}