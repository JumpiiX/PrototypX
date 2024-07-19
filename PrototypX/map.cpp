#include "map.h"

Map::Map(int width, int height, int tileSize)
        : m_width(width), m_height(height), m_tileSize(tileSize),
          m_tiles(height, std::vector<bool>(width, true)),
          m_vertices(sf::Quads),
          m_rng(std::random_device{}()) {
    generate();
}

void Map::generate() {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            m_tiles[y][x] = true;
        }
    }

    int currentX = m_width / 2;
    int currentY = m_height / 2;
    int pathLength = m_width * m_height / 3;

    std::uniform_int_distribution<int> dist(0, 3);

    for (int i = 0; i < pathLength; ++i) {
        m_tiles[currentY][currentX] = false;

        int direction = dist(m_rng);
        switch(direction) {
            case 0: if(currentX > 1) currentX--; break;
            case 1: if(currentX < m_width-2) currentX++; break;
            case 2: if(currentY > 1) currentY--; break;
            case 3: if(currentY < m_height-2) currentY++; break;
        }
    }

    for (int i = 0; i < 5; ++i) {
        smoothMap();
    }

    updateVertices();
}

void Map::smoothMap() {
    std::vector<std::vector<bool>> newTiles = m_tiles;
    for (int y = 1; y < m_height-1; ++y) {
        for (int x = 1; x < m_width-1; ++x) {
            int walls = countAdjacentWalls(x, y);
            if (walls > 4)
                newTiles[y][x] = true;
            else if (walls < 4)
                newTiles[y][x] = false;
        }
    }
    m_tiles = newTiles;
}

int Map::countAdjacentWalls(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (x+j < 0 || x+j >= m_width || y+i < 0 || y+i >= m_height)
                count++;
            else if (m_tiles[y+i][x+j])
                count++;
        }
    }
    return count;
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

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_vertices, states);
}