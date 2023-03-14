#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <iostream>

#ifndef GOLFGAME_BALL_H
#define GOLFGAME_BALL_H


class Ball {
public:
    Ball(sf::Vector2f position, sf::Vector2f velocity) {
        this->position = position;
        this->velocity = velocity;
    }

    void draw(sf::RenderWindow &window, sf::Shader &shader) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(position);
        shape.setFillColor({25, 25, 25, 255});
        shape.setOutlineColor({255, 102, 102, 255});
        shape.setOutlineThickness(2);
        window.draw(shape, &shader);
    }

    void handle_input(sf::Event::EventType event, sf::Window &window);

    void update_position();

    sf::Vector2f get_position();

    void set_position(sf::Vector2f position);

    void set_velocity(sf::Vector2f velocity);

    float get_radius();

    sf::Vector2f get_velocity();

    void
    update_state(sf::Vector2f mousePos, double deltaTime, bool mouseDown, bool mousePressed, sf::RenderWindow &window);


    void render_sprite(sf::Texture &texture, sf::RenderWindow &window);

    void initialize_sprite(sf::Texture &texture);

    void hole_animation();

    void fire_hole();

private:
    bool started = false;
    bool dragging = false;
    bool pressing = false;
    float radius = 25;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::RectangleShape pointer;
    float abs_velocity;
    sf::Vector2f launch_velocity;
    bool launched;
    int dirX = 1, dirY = 1;
    sf::CircleShape shape;
    sf::Vector2f launch_pos;
    float speed = 10;
    sf::Sprite sprite;
    float gravity = 9.8;


    sf::Vector2f get_charge_velocity(sf::Vector2f mousePos);

    sf::Vector2f get_pullback_velocity(sf::Vector2f mousePos, sf::Vector2f launchPos);
};


#endif //GOLFGAME_BALL_H


#define VECTOR_EMPTY(v) (v.x == 0 && v.y == 0)