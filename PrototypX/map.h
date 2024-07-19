#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Map : public sf::Drawable {
public:
    Map(int width, int height, int tileSize);
    bool isWall(int x, int y) const;
    int getTileSize() const { return m_tileSize; }
    sf::Vector2f getPlayerSpawnPoint() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void generate();
    void smoothMap();
    int countAdjacentWalls(int x, int y);
    void updateVertices();
    void addWallVertices(const sf::Vector2f& pos);

    int m_width;
    int m_height;
    int m_tileSize;
    std::vector<std::vector<bool>> m_tiles;
    sf::VertexArray m_vertices;
    std::mt19937 m_rng;
};

#endif
