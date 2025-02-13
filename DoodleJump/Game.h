#pragma once
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Doodle.h"
#include "Platform.h"

namespace DoodleJump
{
    typedef std::vector<Platform> PlatformHolder;

    class Game
    {
    public:
        Game(
            sf::Texture& backgroud_t,
            sf::Texture& platform_t,
            sf::Texture& doodle_t,
            sf::Font& font);

        void update();
        void render(sf::RenderWindow& window);
        void reset();
        void setBestScore(float score);
        float getBestScore() const;
        bool isGameOver() const;
        
    private:
        sf::Sprite background_s;
        sf::Text score_text, bestscore_text, restart_text, gameover_text, left_control_text, right_control_text;
        sf::SoundBuffer startSoundBuffer, fallSoundBuffer;
        sf::Sound startSound, fallSound;
        Doodle doodle;
        PlatformHolder platforms;
        sf::Clock clock;

        bool gameOver;
        bool hasPlayedFallSound;
        float gameOverTimer;
        float bestScore;
        float score;
    };
}
#endif