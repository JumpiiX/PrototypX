#include "MovementController.h"

MovementController::MovementController(Dot& dot, const Map& map)
        : dot(dot), map(map), moveSpeed(300.0f) {}

void MovementController::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (keys[sf::Keyboard::W]) movement.y -= moveSpeed * deltaTime;
    if (keys[sf::Keyboard::S]) movement.y += moveSpeed * deltaTime;
    if (keys[sf::Keyboard::A]) movement.x -= moveSpeed * deltaTime;
    if (keys[sf::Keyboard::D]) movement.x += moveSpeed * deltaTime;

    sf::Vector2f currentPos = dot.getPosition();
    sf::Vector2f newPos = currentPos + movement;

    if (!checkCollision(sf::Vector2f(newPos.x, currentPos.y))) {
        currentPos.x = newPos.x;
    }
    if (!checkCollision(sf::Vector2f(currentPos.x, newPos.y))) {
        currentPos.y = newPos.y;
    }

    dot.setPosition(currentPos.x, currentPos.y);
}

bool MovementController::checkCollision(const sf::Vector2f& position) {
    int tileSize = map.getTileSize();
    int tileX = static_cast<int>(position.x / tileSize);
    int tileY = static_cast<int>(position.y / tileSize);
    return map.isWall(tileX, tileY);
}
