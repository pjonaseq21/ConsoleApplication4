#pragma once
#include <SFML/Graphics.hpp>
class Throngle
{
public:
	Throngle(sf::Vector2f position = { 750.f, 580.f }, sf::Vector2f size = { 40.f, 140.f });
	void render(sf::RenderWindow& window);
	void move(int moveToX, int moveToY);

private:
	sf::RectangleShape texture;
	int hunger=0;
};

