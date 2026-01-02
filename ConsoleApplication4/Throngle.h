#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Throngle
{
public:
	enum class State {
		Fight,
		Starve,
		Replicate,
	};
	Throngle(int familyId, sf::Vector2f size = { 20.f, 70.f }, float startHunger = 0.3f);
	Throngle(sf::Vector2f position = { 750.f, 580.f }, sf::Vector2f size = { 20.f, 70.f }, float startHunger = 0.3f);
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
	int familyIdGet()const { return familyId; }
	State getState()const { return m_state; }
private:
	sf::Vector2f territory;
	int familyId;
	State m_state;
	sf::RectangleShape texture;
	float m_hunger;
	float m_changeDirectionTimer = 0.0f;
	float m_speed= 20.0f;
	sf::Vector2f m_velocity;
	void grow();
	bool wasEatenThrongle = false;
	sf::Vector2f throngleTerritoryPosition(int familyId);


};

