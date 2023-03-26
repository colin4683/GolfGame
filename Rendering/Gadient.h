#include <SFML/Graphics.hpp>

#ifndef GOLFGAME_GADIENT_H
#define GOLFGAME_GADIENT_H


#endif //GOLFGAME_GADIENT_H

namespace Draw {
    enum GradientType {
        LeftToRight,
        RightToLeft,
        TopToBottom,
        BottomToTop,
    };


    class GradientRect {
    public:
        GradientRect(sf::FloatRect pas, GradientType type, sf::Color colorA, sf::Color colorB) {
            std::vector<sf::Color> colors;
            rect.setPrimitiveType(sf::Quads);
            if (type == GradientType::LeftToRight) {
                for (int i = 0; i < 2; i++) {
                    colors.push_back(colorA);
                    colors.push_back(colorB);
                }
            } else if (type == GradientType::RightToLeft) {
                for (int i = 0; i < 2; i++) {
                    colors.push_back(colorB);
                    colors.push_back(colorA);
                }
            } else if (type == GradientType::TopToBottom) {
                colors.push_back(colorA);
                colors.push_back(colorA);

                colors.push_back(colorB);
                colors.push_back(colorB);
            } else if (type == GradientType::BottomToTop) {
                colors.push_back(colorB);
                colors.push_back(colorB);

                colors.push_back(colorA);
                colors.push_back(colorA);
            }
            this->rect.append(sf::Vertex(sf::Vector2f(pas.left, pas.top), colors[0]));
            this->rect.append(sf::Vertex(sf::Vector2f(pas.left + pas.width, pas.top), colors[1]));
            this->rect.append(sf::Vertex(sf::Vector2f(pas.left + pas.width, pas.top + pas.height), colors[3]));
            this->rect.append(sf::Vertex(sf::Vector2f(pas.left, pas.top + pas.height), colors[2]));

        }

        void Draw(sf::RenderWindow &window) {
            window.draw(rect);
        }

    private:
        sf::VertexArray rect;
    };


}
