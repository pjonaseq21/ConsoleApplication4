#include "Throngle.h"
#include <iostream>
Throngle::Throngle(sf::Vector2f position, sf::Vector2f size) {
	texture.setFillColor(sf::Color(255, 234, 0));
	texture.setSize(size);
	texture.setPosition(position);
	newBornReproduction();
}
void Throngle::render(sf::RenderWindow& window)
{
	window.draw(texture);

}
void Throngle::hungerDecrease() {
	m_hunger -= 0.1;
	m_speed += 0.6;
}
void Throngle::move(float moveToX, float moveToY) {
	
	sf::Vector2f currentPosition = texture.getPosition();
	currentPosition.x += moveToX;
	currentPosition.y += moveToY;
	texture.setPosition(currentPosition);
}


bool Throngle::reproduction() {
	if (m_hunger >= 0.9)
	{
		newBorn = true;
		return true;
	}
	return false;
}
void Throngle::newBornReproduction() {
	if (newBorn == true) {
		m_hunger = 0.7;
	}
}

int Throngle::randomNumber() {
	sf::Clock clock;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(-10, 10);
	return dist(mt);
}
void Throngle::update(float dt) {
	int random = randomNumber();
	m_changeDirectionTimer -= dt;

	if (m_changeDirectionTimer <= -1) {
		float dirX = (rand() % 201 - 100) / 100.0f;
		float dirY = (rand() % 201 - 100) / 100.0f;
		m_velocity = sf::Vector2f(dirX, dirY);
		m_changeDirectionTimer = 1.0f + ((rand() % 200) / 100.0f);
	}
	this->move(m_velocity.x * m_speed * dt, m_velocity.y * m_speed * dt);
}