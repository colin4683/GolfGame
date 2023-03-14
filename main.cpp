#include <SFML/Graphics.hpp>
#include "Game/Game.h"
#include "Rendering/Gadient.h"


bool mousePressed = false;
bool mouseDown = false;
sf::Clock GameClock;
sf::Time deltaTime;

int main() {

    if (!sf::Shader::isAvailable()) {
        std::cout << "Shaders not supported" << std::endl;
        return EXIT_FAILURE;
    }

    const auto windowSize = sf::Vector2(1920, 1080);
    sf::RenderWindow window(sf::VideoMode(getSettings().windowWidth, getSettings().windowHeight), "GolfGamer");
    window.setFramerateLimit(60);


    sf::Texture texture;
    if (!texture.loadFromFile("/Users/colinstroble/CLionProjects/GolfGame/Sprites/2760.png")) {
        std::cout << "Error loading ball texture" << std::endl;
    }
    // golfBall->InitializeSprite(texture);


    sf::RectangleShape mousePoint;
    mousePoint.setSize(sf::Vector2f(1, 1));
    mousePoint.setFillColor(sf::Color::Red);

    Draw::GradientRect *background = new Draw::GradientRect(sf::FloatRect(4, 6, 1920, 1080),
                                                            Draw::GradientType::TopToBottom, {62, 119, 250},
                                                            {252, 96, 242});
    sf::CircleShape circle;

    circle.setRadius(100.f);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(sf::Vector2f(window.getSize()) / 2.f);
    circle.setFillColor(sf::Color::Transparent);
    // Load Shaders
    sf::Shader shader;
    //if (!shader.loadFromFile("/Users/colinstroble/CLionProjects/GolfGame/Shader.frag", sf::Shader::Fragment)) {
    // std::cout << "Error loading shader" << std::endl;
    //}
    //shader.setUniform("windowHeight",
    // 1920.0f); // this must be set, but only needs to be set once (or whenever the size of the window changes)

    // Initialize game environment
    Game *game = new Game(window, deltaTime.asSeconds());
    game->run_setup();

    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        mousePressed = false;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);


        deltaTime = GameClock.restart();
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            // Update game key_state
            game->update_keystate(event.type);


            // golfBall->HandleInput(event.type, window);
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                mousePressed = true;
                mouseDown = true;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //Get the mouse position:

                    //Map Pixel to Coords:
                    //Set position of the mouse to the rectangle:
                    mousePoint.setPosition(mouseWorldPosition.x, mouseWorldPosition.y);
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseDown = false;
            }
        }
        game->update_time(deltaTime.asSeconds());
        window.clear();
        window.draw(mousePoint);
        //background->Draw(window);
        game->run();
        //golfBall->draw(window, shader);
        //golfBall->UpdateState(mouseWorldPosition, deltaTime.asSeconds(), mouseDown, mousePressed, window);
        //golfBall->RenderSprite(texture, window);
        window.display();

        // deltaTime = sf::Time::Zero;
    }
    return 0;
}
