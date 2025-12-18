#include "Apple.h"
#include "Resources.h"
Apple::Apple(sf::Vector2f size) {
	texture.setFillColor(sf::Color(220, 20, 60));
	texture.setSize(size);
	float randomForApplex = Resources::randomNumber(-1000, 1000);
	float randomForAppley = Resources::randomNumber(-1000, 1000);

	texture.setPosition({randomForApplex,randomForAppley });
}
void Apple::render(sf::RenderWindow& window) {
	window.draw(texture);

}

sf::FloatRect Apple::getBounds() {
	return texture.getGlobalBounds();
}