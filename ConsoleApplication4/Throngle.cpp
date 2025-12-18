#include "Throngle.h"
#include <iostream>
Throngle::Throngle(sf::Vector2f position, sf::Vector2f size) {
	texture.setFillColor(sf::Color(255, 234, 0));
	texture.setSize(size);
	texture.setPosition(position);
}
void Throngle::render(sf::RenderWindow& window)
{
	window.draw(texture);

}
void Throngle::move(int moveToX, int moveToY) {
	sf::Vector2f currentPosition = texture.getPosition();
	currentPosition.x += moveToX;
	currentPosition.y += moveToY;
	texture.setPosition(currentPosition);

}