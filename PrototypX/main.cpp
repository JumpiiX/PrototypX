#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "dot.h"
#include "movementController.h"
#include "enemy.h"
#include "actionController.h"
#include "crosshair.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PrototypeX.exe");
    window.setMouseCursorVisible(false);

    Dot dot(960, 540);
    MovementController controller(dot);
    ActionController actionController;
    Crosshair crosshair(960, 540);

    std::srand(std::time(nullptr));
    sf::Clock clock;

    controller.keys[sf::Keyboard::W] = false;
    controller.keys[sf::Keyboard::A] = false;
    controller.keys[sf::Keyboard::S] = false;
    controller.keys[sf::Keyboard::D] = false;

    while (window.isOpen()) {
        sf::Event event;
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                controller.keys[event.key.code] = true;
            }

            if (event.type == sf::Event::KeyReleased) {
                controller.keys[event.key.code] = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                actionController.handleShooting(window, dot.getPosition());
            }
        }

        controller.handleInput(deltaTime);
        actionController.updateProjectiles(window, deltaTime);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        crosshair.updatePosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        window.clear(sf::Color::Black);
        window.draw(dot.shape);
        actionController.drawEnemies(window);
        actionController.drawProjectiles(window);
        crosshair.draw(window);
        window.display();
    }

    return 0;
}
