//
// Created by Colin Stroble on 8/26/22.
//
#include <SFML/Graphics.hpp>
#include "../Ball/Ball.h"

#ifndef GOLFGAME_GAME_H
#define GOLFGAME_GAME_H


struct KeyState {
    bool m_bPressed = false;
    bool m_bHeld = false;
    bool m_bDown = false;
    sf::Vector2i m_vMousePos;
    sf::Vector2i m_vMousePosConverted;
};

struct GameTile {
    sf::Vector2f position;
    bool m_bIsHole = false;
    bool m_bIsWall = false;
    bool m_bHasBall = false;
    float m_flLastTouchTime = 0.0f;
};


class Game {
public:
    Game(sf::RenderWindow &game_window, float dt) {
        window = &game_window;
        game_time = dt;
    }

    void run();

    void run_setup();

    void update_keystate(sf::Event::EventType event);

    void update_time(float flTime) {
        game_time = flTime;
    }

private:
    KeyState key_state;
    sf::RenderWindow *window;
    Ball *ball;
    sf::Texture ball_texture;
    sf::Shader shader;
    float game_time;
    std::vector<GameTile> map;
    sf::Clock gClock;
    GameTile hole;
    bool game_over = false;

    void render_grid();

    void render_map();

    void generate_map();

    void find_path(sf::Vector2f start, sf::Vector2f end);

    void generate_hole();

    void check_if_win();

    void touch_loop();
};


#endif //GOLFGAME_GAME_H
