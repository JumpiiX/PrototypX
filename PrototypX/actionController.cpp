#include "ActionController.h"
#include <cmath>
#include <cstdlib>

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir) : direction(dir), speed(1000.0f) {
    shape.setSize(sf::Vector2f(10, 2));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(pos);
    shape.setRotation(atan2(dir.y, dir.x) * 180 / 3.14159265);
}

ActionController::ActionController() {}

void ActionController::handleShooting(sf::RenderWindow& window, const sf::Vector2f& position) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y) - position;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;
    projectiles.emplace_back(position, direction);
}

void ActionController::updateProjectiles(sf::RenderWindow& window, float deltaTime) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->shape.move(it->direction * it->speed * deltaTime);
        bool removed = false;
        for (auto eit = enemies.begin(); eit != enemies.end() && !removed;) {
            if (it->shape.getGlobalBounds().intersects(eit->shape.getGlobalBounds())) {
                eit = enemies.erase(eit);
                it = projectiles.erase(it);
                removed = true;
            }
            else {
                ++eit;
            }
        }
        if (!removed) {
            ++it;
        }
    }
    while (enemies.size() < 5) {
        float x = std::rand() % window.getSize().x;
        float y = std::rand() % window.getSize().y;
        enemies.emplace_back(x, y);
    }
}

void ActionController::drawProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        window.draw(projectile.shape);
    }
}

void ActionController::drawEnemies(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        window.draw(enemy.shape);
    }
}
