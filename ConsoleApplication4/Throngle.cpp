#include "Throngle.h"
#include <iostream>
Throngle::Throngle(sf::Vector2f position, sf::Vector2f size, float startHunger) {
	m_hunger = startHunger;
	texture.setFillColor(sf::Color(255, 234, 0));
	texture.setSize(size);
	texture.setPosition(position);
}
void Throngle::render(sf::RenderWindow& window)
{
	window.draw(texture);

}
void Throngle::hungerDecrease() {
	m_hunger -= 0.01;
	m_speed += 0.6;
}
void Throngle::move(float moveToX, float moveToY) {
	
	sf::Vector2f currentPosition = texture.getPosition();
	currentPosition.x += moveToX;
	currentPosition.y += moveToY;
	texture.setPosition(currentPosition);
}


bool Throngle::reproduction() {
	std::cout << m_hunger<<" glod   \n ";
	if (m_hunger >= 0.4f)
	{
		m_hunger = 0.2f;
		return true;
	}
	return false;
}
void Throngle::eat() {
	m_hunger += 0.5;
}

sf::FloatRect Throngle::getBounds() {
	return texture.getGlobalBounds();
}

void Throngle::update(float dt) {
	int random = Resources::randomNumber(-10,10);
	m_changeDirectionTimer -= dt;

	if (m_changeDirectionTimer <= -1) {
		float dirX = (rand() % 201 - 100) / 100.0f;
		float dirY = (rand() % 201 - 100) / 100.0f;
		m_velocity = sf::Vector2f(dirX, dirY);
		m_changeDirectionTimer = 1.0f + ((rand() % 200) / 100.0f);
	}
	this->move(m_velocity.x * m_speed * dt, m_velocity.y * m_speed * dt);
}