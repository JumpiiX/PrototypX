// models/Dot.cpp
#include "Dot.h"

Dot::Dot(float x, float y) : shape(10) { // Radius des Punkts ist 10
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}

void Dot::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Dot::getPosition() {
    return shape.getPosition();
}
