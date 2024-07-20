#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <queue>
#include <algorithm>

class Map : public sf::Drawable {
public:
    Map(int width, int height, int tileSize);
    bool isWall(int x, int y) const;
    int getTileSize() const { return m_tileSize; }
    sf::Vector2f getPlayerSpawnPoint() const;
    void updateMap(const sf::Vector2f& playerPosition);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void generate();
    void generateChunk(int startX, int startY);
    void smoothMap();
    void updateVertices();
    void addWallVertices(const sf::Vector2f& pos);

    int m_width, m_height, m_tileSize;
    std::vector<std::vector<bool>> m_tiles;
    sf::VertexArray m_vertices;
    std::mt19937 m_rng;
    int m_chunkSize;
};
