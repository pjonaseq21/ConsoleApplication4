#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Throngle
{
public:
	Throngle(sf::Vector2f position = { 750.f, 580.f }, sf::Vector2f size = { 40.f, 140.f }, float startHunger = 0.3f);
	void render(sf::RenderWindow& window);
	void move(float moveToX, float moveToY);
	void hungerDecrease();
	bool reproduction();
	void update(float dt);
	sf::Vector2f getPosition()const;
	sf::FloatRect getBounds();
	void eat();
	float getHunger()const { return m_hunger; }// ciekawy sposob na zapisanie gettera
	void wasEatenFunc();
private:
	sf::RectangleShape texture;
	float m_hunger;
	float m_changeDirectionTimer = 0.0f;
	float m_speed= 20.0f;
	sf::Vector2f m_velocity;
	void grow();
	bool wasEatenThrongle = false;



};

