#pragma once
#include <SFML/Graphics.hpp>

class Apple
{
public:
	Apple(sf::Vector2f startPosition,const sf::Texture& texture);
	void render(sf::RenderWindow& window);
	sf::Vector2f getPosition()const;
	sf::FloatRect getBounds();

private:
	sf::Vector2f position;
	sf::Sprite appleSprite;
	sf::Vector2f logicalPosition;
	float nutritiousness = 0.2;
	
};

