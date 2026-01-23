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
	Throngle(int familyId, sf::FloatRect territory, sf::Vector2f size = { 32, 32.f }, float startHunger = 0.3f);
	void render(sf::RenderWindow& window);
	void move(float moveToX, float moveToY);
	void hungerIncrease();
	bool reproduction();
	void update(float dt, bool canFight);
	sf::Vector2f getPosition()const;
	sf::FloatRect getBounds();
	void eat();
	float getHunger()const { return m_hunger; }
	void wasEatenFunc();
	int familyIdGet()const { return familyId; }
	void fightHandle();
	bool getStateFight()const;
	sf::FloatRect getTerritory() { return territory; }
	void setHunger();
	static void crossBridge(float yCoordinate);

private:
	static bool hasBridgeTarget;
	sf::Texture throngleTexture;
	sf::Sprite throngleSprite;
	sf::IntRect rectSource;
	sf::Clock animClock;
	static float bridgeYpos;
	float timererFrame = 0.1f;
	int currentFrame = 0;
	int animRow = 0;
	sf::FloatRect territory;
	bool checkifEnemyPosition(int familyId);
	int familyId;
	State m_state;
	sf::RectangleShape hitbox;
	float m_hunger;
	float m_changeDirectionTimer = 0.0f;
	float m_speed= 20.0f;
	sf::Vector2f m_velocity;
	void grow();
	bool wasEatenThrongle = false;
	sf::Vector2f throngleTerritoryPosition(int familyId);


};

