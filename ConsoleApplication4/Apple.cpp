#include "Apple.h"
#include "Resources.h"
#include "Ground.h"
#include <algorithm>
#include <cmath>

Apple::Apple(sf::Vector2f startPosition, const sf::Texture& texture) : appleSprite(texture) {
    this->logicalPosition = startPosition;

    appleSprite.setTexture(texture, true);

    sf::FloatRect localBounds = appleSprite.getLocalBounds();
    appleSprite.setOrigin(sf::Vector2f(localBounds.size.x / 2.0f, localBounds.size.y / 2.0f));

    float tileSize = 50.0f;
    float fillFactor = 3.f;

    float targetSize = tileSize * fillFactor;
    float maxDimension = std::max(localBounds.size.x, localBounds.size.y);
    float scale = targetSize / maxDimension;

    appleSprite.setScale(sf::Vector2f(scale, scale));

    float halfTile = tileSize / 2.0f;
    appleSprite.setPosition(sf::Vector2f(startPosition.x + halfTile, startPosition.y + halfTile));
}

void Apple::render(sf::RenderWindow& window) {
    window.draw(appleSprite);
}

sf::FloatRect Apple::getBounds() {
    return appleSprite.getGlobalBounds();
}

sf::Vector2f Apple::getPosition() const {
    return logicalPosition;
}