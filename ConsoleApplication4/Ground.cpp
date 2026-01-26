#include "Ground.h"
#include <iostream>
#include <cmath>


Ground::Ground() {
	screenWidth = 0;
	screenHeight = 0;
}
void Ground::init(unsigned int screenwidth, unsigned int  screenheight,bool singleGame) {
	vectorTiles.clear();
	unsigned int screenWidth = screenwidth;
	unsigned int screenHeight= screenheight;
	columns = (screenWidth ) / TILE_SIZE;
	rows = (screenHeight ) / TILE_SIZE;

	float totalGridWidth = columns * TILE_SIZE;
	float totalGridHeight = rows * TILE_SIZE;

	startX = (screenWidth - totalGridWidth) / 2.0f;
	startY = (screenHeight - totalGridHeight) / 2.0f;

	float gapPercentage = 0.20f;

	int gapWidthPixels = static_cast<int>(screenWidth * gapPercentage);
	int gapTiles = gapWidthPixels / TILE_SIZE;

	if (gapTiles % 2 != 0) gapTiles++;
	if (gapTiles < 2) gapTiles = 2;

	int bridgeHeightTiles = 4;


	centerCol = columns / 2;

	bridgeStart = centerCol - (bridgeHeightTiles / 2);
	bridgeEnd = centerCol + (bridgeHeightTiles / 2);

	gapStartCol = centerCol - (gapTiles / 2);
	gapEndCol = centerCol + (gapTiles / 2);


	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {


			if (singleGame) {
				if (c >= gapStartCol) {
					continue;
				}
			}
			else {
				if (c >= gapStartCol && c < gapEndCol) {
					continue;
				}
			}



			float posx = startX + (c * TILE_SIZE);
			float posy = startY + (r * TILE_SIZE);

			Tile newTile;
			newTile.isOccupied = false;
			newTile.cooldown = 0.0f;
			newTile.worldPos = { posx, posy };
			vectorTiles.push_back(newTile);
		}
	}
}
sf::Vector2f Ground::returnFreeTile() {
	std::vector<int> FreeIndices;
	for (int i = 0; i < vectorTiles.size(); i++) {
		if (vectorTiles[i].isOccupied == false && vectorTiles[i].cooldown <= 0.0f) {
			FreeIndices.push_back(i);
		}
	}
	int randomIndex = FreeIndices[rand() % FreeIndices.size()];
	vectorTiles[randomIndex].isOccupied = true;
	return vectorTiles[randomIndex].worldPos;
}


float Ground::getBridgeCenterY() const {
	int centerRow = rows / 2;
	float centerY = startY + (centerRow * TILE_SIZE);
	return centerY;
}
void Ground::update(float dt) {
	for (int i = 0; i < vectorTiles.size(); i++) {
		if (vectorTiles[i].isOccupied == false && vectorTiles[i].cooldown > 0) {
			vectorTiles[i].cooldown -= dt;
		}
	}
}
// jablko zostaje zjedzone wywolujemy ta funkcje zeby powiedziec hej mozemy zaczac timer dla tego pola
void Ground::ReleasePosition(sf::Vector2f EatenPosition) {
	for (int i = 0; i < vectorTiles.size(); i++) {
		
		if (std::abs(vectorTiles[i].worldPos.x-EatenPosition.x) <1.0f && std::abs(vectorTiles[i].worldPos.y - EatenPosition.y) <1.0f) {
			vectorTiles[i].isOccupied = false;
			vectorTiles[i].cooldown = 4.0f;

		}
		else {
			
		}
	}

}
void Ground::render(sf::RenderWindow& window) {
	sf::RectangleShape debugShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	debugShape.setFillColor(sf::Color::Transparent);
	debugShape.setOutlineThickness(2.0f);

	for (auto& tile : vectorTiles) {
		debugShape.setPosition(tile.worldPos);
		if (tile.isOccupied) {
			debugShape.setOutlineColor(sf::Color::Red);
			}
		if(!tile.isOccupied && tile.cooldown >0) {
			debugShape.setOutlineColor(sf::Color::Magenta);
		}
		else {
			debugShape.setOutlineColor(sf::Color::Blue);

		}
		window.draw(debugShape);
	}
}