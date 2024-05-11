#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class GameSounds {
    sf::SoundBuffer m_move_buffer;    
    sf::SoundBuffer m_line_clear_buffer;

    sf::Sound m_move_sound;
    sf::Sound m_line_clear_sound;

    sf::Music m_theme;

public:
    GameSounds() = default;

    void loadSounds();

    void playMoveSound();

    void playLineClearSound();

    void playTheme();
};