#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include <SFML/Graphics.hpp>

class Crosshair {
public:
    sf::CircleShape circle;
    sf::RectangleShape verticalLine, horizontalLine;

    Crosshair(float centerX, float centerY) {
        circle.setRadius(10);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Green);
        circle.setOrigin(10, 10);
        circle.setPosition(centerX, centerY);

        verticalLine.setSize(sf::Vector2f(2, 40));
        verticalLine.setFillColor(sf::Color::Green);
        verticalLine.setOrigin(1, 20);
        verticalLine.setPosition(centerX, centerY);

        horizontalLine.setSize(sf::Vector2f(40, 2));
        horizontalLine.setFillColor(sf::Color::Green);
        horizontalLine.setOrigin(20, 1);
        horizontalLine.setPosition(centerX, centerY);
    }

    void updatePosition(float x, float y) {
        circle.setPosition(x, y);
        verticalLine.setPosition(x, y);
        horizontalLine.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(circle);
        window.draw(verticalLine);
        window.draw(horizontalLine);
    }
};

#endif
