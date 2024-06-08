// physics/MovementController.cpp
#include "MovementController.h"

MovementController::MovementController(Dot& dot) : dot(dot) {}

void MovementController::handleInput(const sf::Keyboard::Key& key) {
    sf::Vector2f position = dot.getPosition();

    switch (key) {
    case sf::Keyboard::W: position.y -= 10; break;
    case sf::Keyboard::S: position.y += 10; break;
    case sf::Keyboard::A: position.x -= 10; break;
    case sf::Keyboard::D: position.x += 10; break;
    default: break;
    }

    dot.setPosition(position.x, position.y);
}
