#include "Ball.h"
#include <cmath>
#include <math.h>
#include "../Rendering/Gadient.h"

void Ball::handle_input(sf::Event::EventType event, sf::Window &window) {
    if (event == sf::Event::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            started = true;
            launch_pos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            pressing = true;
        }
    }
    if (event == sf::Event::MouseButtonReleased) {
        dragging = false;
        pressing = false;
    }
}

void Ball::set_position(sf::Vector2f _position) {
    position = _position;
}

sf::Vector2f Ball::get_position() {
    return position;
}

void Ball::set_velocity(sf::Vector2f _velocity) {
    velocity = _velocity;
}

sf::Vector2f Ball::get_velocity() {
    return velocity;
}

void Ball::update_position() {
    position += {10, 10};
    shape.setPosition(position);
}

void Ball::initialize_sprite(sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setPosition(get_position());
    sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5, sprite.getTexture()->getSize().y * 0.5);
}


void Ball::render_sprite(sf::Texture &texture, sf::RenderWindow &window) {
    sprite.setPosition(get_position());
    window.draw(sprite);
}

template<typename T>
T Vector2length(const sf::Vector2<T> &v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}


sf::Vector2f Ball::get_charge_velocity(sf::Vector2f mousePos) {

    if (!started) {
        return {0, 0};
    }
    launch_velocity.x = (launch_pos.x - mousePos.x) * 5;
    launch_velocity.y = (launch_pos.y - mousePos.y) * 5;
    float maxSpeed = 100000;
    float launchSpeed = sqrt(pow(launch_velocity.x, 2) + pow(launch_velocity.y, 2));
    if (launchSpeed > maxSpeed) {
        launch_velocity *= maxSpeed / launchSpeed;
    }

    abs_velocity = sqrt(pow(launch_velocity.x, 2) + pow(launch_velocity.y, 2));

    dirX = launch_velocity.x / abs(launch_velocity.x);
    dirY = launch_velocity.y / abs(launch_velocity.y);

    sf::Vector2f normalized = launch_velocity / abs_velocity;

    float angle = atan2(normalized.y, normalized.x);
    angle = angle * (180 / M_PI);
    auto pointerPos = position;
    pointerPos.x += radius * cos(angle * (M_PI / 180));
    pointerPos.y += radius * sin(angle * (M_PI / 180));
    sf::Transform rotation;
    // Rotate around circle
    pointer.setRotation(angle);
    pointer.setPosition(pointerPos);
    pointer.setFillColor(sf::Color::Blue);
    pointer.setSize(sf::Vector2f(abs_velocity, 4));

    return launch_velocity;
}

void Ball::update_state(sf::Vector2f mousePos, double deltaTime, bool mouseDown, bool mousePressed,
                        sf::RenderWindow &window) {
    sf::Vector2f initialPos = {0, 0};
    if (mousePressed) {
        initialPos = position;
    }
    float friction = 0.98;

    if (!pressing) {
        // Apply friction and do bounds checking
        const auto check_bounds = [&]() -> void {
            if (position.x < 0 + radius) {
                position.x = 0 + radius;
                velocity.x *= -1;
            }
            if (position.x > window.getSize().x - radius) {
                position.x = window.getSize().x - radius;
                velocity.x *= -1;
            }
            if (position.y < 0 + radius) {
                position.y = 0 + radius;
                velocity.y *= -1;
            }
            if (position.y > window.getSize().y - radius) {
                position.y = window.getSize().y - radius;
                velocity.y *= -1;
            }
            position += velocity * (float) deltaTime;
            velocity.x *= friction;
            velocity.y *= friction;

            if (fabs(velocity.x) < 0.01f) {
                velocity.x = 0;
            }
            if (fabs(velocity.y) < 0.01f) {
                velocity.y = 0;
            }
        };
        check_bounds();
        // reset the velocity if the ball is not moving
        if (velocity.x == 0 && velocity.y == 0) {
            velocity = {0, 0};
        }
        // rest launch velocity'
        launch_velocity = {0, 0};
    } else {
        set_velocity(get_charge_velocity(mousePos));
        // Draw velocity arrow
        pointer.setFillColor(sf::Color::White);
        pointer.setSize(sf::Vector2f(abs_velocity, 4));
        window.draw(pointer);
    }
}

float Ball::get_radius() {
    return radius;
}

void Ball::hole_animation() {
    if (radius > 0) {
        radius -= 0.3;
    }
    shape.setRadius(radius);
}

void Ball::fire_hole() {
    hole_animation();
}