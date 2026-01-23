#pragma once
#include <SFML/Graphics.hpp>
struct Tile {
	bool isOccupied;
	sf::Vector2f worldPos;
	float cooldown = 0.0f;
	sf::RectangleShape texture;
};
class Ground
{
    const int TILE_SIZE = 50;
	
    unsigned int screenWidth;
    unsigned int screenHeight;
    int columns;
    int rows;
    float startX;
    float startY;

    int centerCol;
    int gapStartCol;
    int gapEndCol;
	std::vector<Tile>vectorTiles;

	int bridgeStart;
	int bridgeEnd;

public:
	float getBridgeCenterY() const;
	void update(float dt);
	void init(unsigned int screenwidth, unsigned int screenheight, bool singleGame);
	void ReleasePosition(sf::Vector2f eatenPosition);
	Ground();
	void render(sf::RenderWindow& window);
	sf::Vector2f returnFreeTile();
};

