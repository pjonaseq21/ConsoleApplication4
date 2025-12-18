#pragma once
#include <SFML/Graphics.hpp>

class Apple
{
public:
	Apple(sf::Vector2f size = { 40.f, 40.f });
	void render(sf::RenderWindow& window);
	sf::Vector2f getPosition()const;
	sf::FloatRect getBounds();

private:
	sf::Vector2f position;
	sf::RectangleShape texture;
	float nutritiousness = 0.2;
	
};

