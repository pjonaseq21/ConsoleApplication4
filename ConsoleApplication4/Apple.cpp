#include "Apple.h"
#include "Resources.h"
#include "Ground.h"
Apple::Apple(sf::Vector2f startPosition, sf::Vector2f size ) {
	texture.setFillColor(sf::Color(220, 20, 60));
	texture.setSize(size);
	

	texture.setPosition(startPosition);
}
void Apple::render(sf::RenderWindow& window) {
	window.draw(texture);

}

sf::FloatRect Apple::getBounds() {
	return texture.getGlobalBounds();
}
sf::Vector2f Apple::getPosition()const {
	return texture.getPosition();
}