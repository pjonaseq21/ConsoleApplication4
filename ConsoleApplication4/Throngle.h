#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Throngle
{
public:
	Throngle(sf::Vector2f position = { 750.f, 580.f }, sf::Vector2f size = { 40.f, 140.f });
	void render(sf::RenderWindow& window);
	void move(float moveToX, float moveToY);
	void hungerDecrease();
	bool reproduction();
	void update(float dt);
	bool canReproduce();
	int randomNumber();

private:
	sf::RectangleShape texture;
	float m_hunger= 1;
	float m_changeDirectionTimer = 0.0f;
	float m_speed= 20.0f;
	sf::Vector2f m_velocity;
	bool newBorn;
	void newBornReproduction();

};

