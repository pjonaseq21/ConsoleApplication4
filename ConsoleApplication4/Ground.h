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
	const int PADDING = 50;
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;
	int columns = (SCREEN_WIDTH - (2 * PADDING)) / TILE_SIZE; 
	int rows = (SCREEN_HEIGHT - (2 * PADDING)) / TILE_SIZE;
	
	std::vector<Tile>vectorTiles;
public:
	void update(float dt);
	void ReleasePosition(sf::Vector2f eatenPosition);
	Ground();
	void render(sf::RenderWindow& window);
	sf::Vector2f returnFreeTile();
};

