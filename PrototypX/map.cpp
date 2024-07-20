#include "map.h"
#include <iostream>

Map::Map(int width, int height, int tileSize)
        : m_width(width), m_height(height), m_tileSize(tileSize),
          m_tiles(height, std::vector<bool>(width, true)),
          m_vertices(sf::Quads),
          m_rng(std::random_device{}()),
          m_chunkSize(16) {
    generate();
}

void Map::generate() {
    for (int y = 0; y < m_height; y += m_chunkSize) {
        for (int x = 0; x < m_width; x += m_chunkSize) {
            generateChunk(x, y);
        }
    }
    smoothMap();
    updateVertices();
}

void Map::generateChunk(int startX, int startY) {
    if (startX < 0 || startY < 0 || startX >= m_width || startY >= m_height) return;

    std::queue<sf::Vector2i> frontier;
    int centerX = std::min(startX + m_chunkSize / 2, m_width - 1);
    int centerY = std::min(startY + m_chunkSize / 2, m_height - 1);
    frontier.push(sf::Vector2i(centerX, centerY));
    m_tiles[centerY][centerX] = false;

    while (!frontier.empty()) {
        sf::Vector2i current = frontier.front();
        frontier.pop();

        std::vector<sf::Vector2i> directions = {
                {0, -2}, {2, 0}, {0, 2}, {-2, 0}
        };
        std::shuffle(directions.begin(), directions.end(), m_rng);

        for (const auto& dir : directions) {
            sf::Vector2i next(current.x + dir.x, current.y + dir.y);
            if (next.x >= startX && next.x < startX + m_chunkSize &&
                next.y >= startY && next.y < startY + m_chunkSize &&
                next.x < m_width && next.y < m_height &&
                m_tiles[next.y][next.x]) {
                m_tiles[next.y][next.x] = false;
                if (current.y + dir.y / 2 < m_height && current.x + dir.x / 2 < m_width) {
                    m_tiles[current.y + dir.y / 2][current.x + dir.x / 2] = false;
                }
                frontier.push(next);
            }
        }
    }
}

void Map::smoothMap() {
}

void Map::updateVertices() {
    m_vertices.clear();
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (m_tiles[y][x]) {
                sf::Vector2f pos(x * m_tileSize, y * m_tileSize);
                addWallVertices(pos);
            }
        }
    }
}

void Map::addWallVertices(const sf::Vector2f& pos) {
    sf::Color wallColor = sf::Color::Green;
    m_vertices.append(sf::Vertex(pos, wallColor));
    m_vertices.append(sf::Vertex(pos + sf::Vector2f(m_tileSize, 0), wallColor));
    m_vertices.append(sf::Vertex(pos + sf::Vector2f(m_tileSize, m_tileSize), wallColor));
    m_vertices.append(sf::Vertex(pos + sf::Vector2f(0, m_tileSize), wallColor));
}

bool Map::isWall(int x, int y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return true;
    return m_tiles[y][x];
}

sf::Vector2f Map::getPlayerSpawnPoint() const {
    for (int y = 1; y < m_height - 1; ++y) {
        for (int x = 1; x < m_width - 1; ++x) {
            if (!m_tiles[y][x]) {
                return sf::Vector2f(x * m_tileSize, y * m_tileSize);
            }
        }
    }
    return sf::Vector2f(m_tileSize, m_tileSize);
}

void Map::updateMap(const sf::Vector2f& playerPosition) {
    int playerTileX = static_cast<int>(playerPosition.x / m_tileSize);
    int playerTileY = static_cast<int>(playerPosition.y / m_tileSize);

    playerTileX = std::max(0, std::min(playerTileX, m_width - 1));
    playerTileY = std::max(0, std::min(playerTileY, m_height - 1));

    int chunkX = (playerTileX / m_chunkSize) * m_chunkSize;
    int chunkY = (playerTileY / m_chunkSize) * m_chunkSize;

    for (int y = chunkY - m_chunkSize; y <= chunkY + m_chunkSize; y += m_chunkSize) {
        for (int x = chunkX - m_chunkSize; x <= chunkX + m_chunkSize; x += m_chunkSize) {
            if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
                if (m_tiles[y][x]) {
                    generateChunk(x, y);
                }
            }
        }
    }
    updateVertices();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_vertices, states);
}
