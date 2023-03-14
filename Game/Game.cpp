//
// Created by Colin Stroble on 8/26/22.
//
#include <math.h>
#include <array>
#include <time.h>
#include <cfloat>
#include "Game.h"

#define X_MAX 1000
#define X_STEP 20
#define Y_MAX 500
#define Y_STEP 20

void Game::run_setup() {
    static bool ran = false;
    if (!ran) {
        if (!ball_texture.loadFromFile("/Users/colinstroble/CLionProjects/GolfGame/Sprites/2760.png")) {
            std::cout << "Error loading ball texture" << std::endl;
        }

        // initialize ball
        ball = new Ball(sf::Vector2f(getSettings().windowWidth / 2, getSettings().windowHeight / 2),
                        sf::Vector2f(0.0f, 0.0f));

        ran = true;
    }
}

void Game::update_keystate(sf::Event::EventType event) {
    key_state.m_vMousePos = sf::Mouse::getPosition(*window);
    key_state.m_bPressed = false;
    if (event == sf::Event::MouseButtonPressed) {
        key_state.m_bPressed = true;
        key_state.m_bDown = true;
    } else if (event == sf::Event::MouseButtonReleased) {
        key_state.m_bDown = false;
    }
    ball->handle_input(event, *window);
}

void Game::generate_map() {
    if (!map.empty()) {
        return;
    }

    const int rows = getSettings().windowHeight / getSettings().tileSize;
    const int cols = getSettings().windowWidth / getSettings().tileSize;
    const auto ballPos = ball->get_position();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            map.emplace_back(
                    GameTile{sf::Vector2f(j * getSettings().tileSize, i * getSettings().tileSize), false, false,
                             false});
        }
    }
    generate_hole();
}


void Game::render_map() {
    bool contains_ball;
    for (auto &tile: map) {

        const auto ballPos = ball->get_position();
        float alpha = 5.0f + (255.0f - 5.0f) * (1.0f - (sqrt(pow(ballPos.x - tile.position.x, 2) +
                                                             pow(ballPos.y - tile.position.y, 2)) /
                                                        getSettings().windowWidth));
        float padding = 8.0f;
        float touch_time = tile.m_flLastTouchTime;
        float current_time = gClock.getElapsedTime().asMilliseconds();
        float time_diff = current_time - touch_time;
        if (touch_time > 0) {
            printf("%f - %f = %f\n", current_time, touch_time, time_diff);
        }
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f((float) getSettings().tileSize, (float) getSettings().tileSize));
        rect.setPosition(tile.position + sf::Vector2f(padding, padding));
        rect.setFillColor(sf::Color(55, 55, 55, 150));
        rect.setOutlineThickness(2.0f);
        rect.setOutlineColor(sf::Color(255, 192, 203));


        sf::CircleShape circle;
        circle.setRadius(5.f);
        circle.setPosition(tile.position + sf::Vector2f(getSettings().tileSize / 2, getSettings().tileSize / 2));
        circle.setFillColor(
                (touch_time > 0) ? sf::Color(255, 192, 203, (int) alpha)
                                 : sf::Color(
                        30, 30, 30,
                        (int) alpha));


        tile.m_bIsHole ? window->draw(rect) : window->draw(circle);
    }
}

void Game::generate_hole() {
    // seed rand func
    srand(time(nullptr));
    int hole_idx = rand() % map.size() - 1;
    // gen random hole
    map[hole_idx].m_bIsHole = true;
    hole = map[hole_idx];
}

void Game::touch_loop() {
    bool contains_ball = false;
    const auto ballPos = ball->get_position();
    int rows = getSettings().windowHeight / getSettings().tileSize;
    int cols = getSettings().windowWidth / getSettings().tileSize;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            const int32_t idx = i * cols + j;
            contains_ball = (i == (int) (ballPos.y / (float) getSettings().tileSize) &&
                             j == (int) (ballPos.x / (float) getSettings().tileSize));
            if (contains_ball) {
                map[idx].m_bHasBall = true;
                map[idx].m_flLastTouchTime = gClock.getElapsedTime().asMilliseconds();
            } else {
                map[idx].m_bHasBall = false;
                if (map[idx].m_flLastTouchTime > 0) {
                    if (gClock.getElapsedTime().asMilliseconds() - map[idx].m_flLastTouchTime > 400) {
                        map[idx].m_flLastTouchTime = -1;
                    }
                } else {
                    map[idx].m_flLastTouchTime = -1;
                }
            }
        }
    }
}


void Game::check_if_win() {
    touch_loop();
    for (const auto &tile: map) {
        if (tile.m_bIsHole && tile.m_bHasBall) {
            ball->fire_hole();
            game_over = true;
        }
    }
}


void Game::run() {
    static bool found_end = false;
    static bool found_start = false;
    generate_map();
    check_if_win();
    render_map();
    ball->draw(*window, shader);
    if (!game_over) {
        ball->update_state(window->mapPixelToCoords(key_state.m_vMousePos), game_time, key_state.m_bDown,
                           key_state.m_bPressed, *window);
    }
    // gClock.restart();
}
