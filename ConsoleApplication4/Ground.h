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
	//dynamiczny paddign, poprawa siatki
	const int TILE_SIZE = 50;
	const int PADDING = 5;
	sf::VideoMode desktop_Size = sf::VideoMode::getDesktopMode();
	unsigned int screenWidth = desktop_Size.size.x;
	unsigned int screenHeight = desktop_Size.size.y;
	int columns = (screenWidth - (2 * PADDING)) / TILE_SIZE;
	int rows = (screenHeight- (2 * PADDING)) / TILE_SIZE;
	float totalGridWidth = columns * TILE_SIZE;
	float totalGridHeight = rows * TILE_SIZE;
	float startX = (screenWidth - totalGridWidth) / 2.0f;
	float startY = (screenHeight - totalGridHeight) / 2.0f;
	std::vector<Tile>vectorTiles;

public:
	void update(float dt);
	void ReleasePosition(sf::Vector2f eatenPosition);
	Ground();
	void render(sf::RenderWindow& window);
	sf::Vector2f returnFreeTile();
};

