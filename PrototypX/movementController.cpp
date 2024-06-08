#include "MovementController.h"

MovementController::MovementController(Dot& dot) : dot(dot), moveSpeed(300.0f) {}

void MovementController::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (keys[sf::Keyboard::W]) movement.y -= moveSpeed * deltaTime;
    if (keys[sf::Keyboard::S]) movement.y += moveSpeed * deltaTime;
    if (keys[sf::Keyboard::A]) movement.x -= moveSpeed * deltaTime;
    if (keys[sf::Keyboard::D]) movement.x += moveSpeed * deltaTime;

    sf::Vector2f newPosition = dot.getPosition() + movement;
    dot.setPosition(newPosition.x, newPosition.y);
}
