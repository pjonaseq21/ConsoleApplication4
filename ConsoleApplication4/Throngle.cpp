#include "Throngle.h"
#include "Ground.h"
#include <iostream>
Throngle::Throngle(int familyId,sf::FloatRect territory, sf::Vector2f size, float startHunger):throngleSprite(throngleTexture){
	if (!throngleTexture.loadFromFile("assets/throngleA.png")) {
		std::exit(1);
	}
	throngleSprite.setTexture(throngleTexture);
	rectSource = sf::IntRect({ 0, 0 }, { 32, 32 });
	throngleSprite.setTextureRect(rectSource);
	hitbox.setOrigin({ 10,10 });

	m_hunger = startHunger;
	this->familyId = familyId;
	this ->territory = territory;
	if (familyId == 0) {
		hitbox.setFillColor(sf::Color::Transparent);
	}
	else {
		hitbox.setFillColor(sf::Color::Transparent);
		throngleSprite.setColor(sf::Color::Red);

	}
	hitbox.setSize(size);
	hitbox.setPosition(throngleTerritoryPosition(familyId));
	throngleSprite.setPosition(hitbox.getPosition());

}

void Throngle::render(sf::RenderWindow& window)
{
	window.draw(throngleSprite);

}
//zmienic nazwe funkcji bo nie oznacza tego nawet, to ma zwiekszac glod
void Throngle::hungerIncrease() {
	if (wasEatenThrongle) {
		sf::Vector2f currSize = hitbox.getSize();
		currSize.x = currSize.x * 0.999;
		currSize.y = currSize.y * 0.999;
		hitbox.setSize(currSize);
	}
	else {
		m_hunger -= 0.01;
		m_speed += 1.5;
	}
	}
void Throngle::move(float moveToX, float moveToY) {

	sf::Vector2f currentPosition = hitbox.getPosition();
	float tempPosx = currentPosition.x + moveToX;
	float tempPosy = currentPosition.y + moveToY;


	hitbox.setPosition({tempPosx, tempPosy});
	throngleSprite.setPosition({ tempPosx, tempPosy });
}

void Throngle::wasEatenFunc() {
	wasEatenThrongle = true;
}

bool Throngle::reproduction() {
	//std::cout << m_hunger<<" glod   \n ";
	if (m_hunger >= 0.4f)
	{
		m_hunger = 0.2f;
		return true;
	}
	return false;
}
void Throngle::eat() {
	m_hunger += 0.5;
	grow();

}
void Throngle::grow() {
	sf::Vector2f currSize =hitbox.getSize();
	currSize.x += 15;
	currSize.y += 10;
	sf::Vector2f textureSize;
	textureSize.x = static_cast<float>(throngleSprite.getTextureRect().size.x);
	textureSize.y = static_cast<float>(throngleSprite.getTextureRect().size.y);
	throngleSprite.setScale({currSize.x / textureSize.x , currSize.y / textureSize.y });
	hitbox.setSize(currSize);

}

sf::FloatRect Throngle::getBounds() {
	return hitbox.getGlobalBounds();
}
void Throngle::setHunger() {
	m_hunger = -15;
}
void Throngle::update(float dt, bool canFight) {
	//std::cout << " czy ten throngle moze walczyc " << canFight <<  "\n";
	m_changeDirectionTimer -= dt;

	if (canFight == true&& hasBridgeTarget) {
		
			m_state = State::Fight;
			float missingY = bridgeYpos - hitbox.getPosition().y;
			float dirX = (rand() % 201 - 100) / 100.0f;
			float dirY = 0.0f;
			if (missingY > 2.0f) dirY = 1.0f;
			else if (missingY < -2.0f) dirY = -1.0f;
			else dirY = 0;
			m_velocity = sf::Vector2f(dirX, dirY);
	}
	else {
		
	if (m_changeDirectionTimer <= -1) {
		float dirX = (rand() % 201 - 100) / 100.0f;
		float dirY = (rand() % 201 - 100) / 100.0f;
		m_velocity = sf::Vector2f(dirX, dirY);
		m_changeDirectionTimer = 1.0f + ((rand() % 200) / 100.0f);
		}
	}
	this->move(m_velocity.x * m_speed * dt, m_velocity.y * m_speed * dt);
	
}
sf::Vector2f Throngle::throngleTerritoryPosition(int familyId) {
	switch (familyId) {
	case 0:  {
		float randomPositionFamilyx = Resources::randomNumber(50, 600);
		float randomPositionFamilyy = Resources::randomNumber(0, 1000);
		return { randomPositionFamilyx,randomPositionFamilyy };
	}
	case 1: {
		float randomPositionFamilyx = Resources::randomNumber(1100, 1800);
		float randomPositionFamilyy = Resources::randomNumber(0, 1000);
		return { randomPositionFamilyx,randomPositionFamilyy };
	}
	}
}

bool Throngle::checkifEnemyPosition(int familyId) {

	sf::Vector2f myPos = hitbox.getPosition();


	if (territory.contains(myPos)) {
		return false;
	}
	else {
		return true;  
	}
}
bool Throngle::getStateFight()const {
	if (m_state == State::Fight) {
		return true;
	}
	else {
		return false;
	}
}
float Throngle::bridgeYpos = 0.0f;
bool Throngle::hasBridgeTarget = false;
void Throngle::crossBridge(float yCoordinate){
	bridgeYpos = yCoordinate;
	hasBridgeTarget = true;
}