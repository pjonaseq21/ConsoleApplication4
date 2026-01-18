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

	if (tempPosx >= 0 && tempPosx <= 1600) {
		currentPosition.x += moveToX;
	}
	if (tempPosy >= 0 && tempPosy <= 800) {
		currentPosition.y += moveToY;
	}
	hitbox.setPosition(currentPosition);
	throngleSprite.setPosition(currentPosition);
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
	
	if (canFight == true) {
		if (checkifEnemyPosition(familyId))
		{
			m_state = State::Fight;
		}
	}
	m_changeDirectionTimer -= dt;
	
	if (m_changeDirectionTimer <= -1) {
		float dirX = (rand() % 201 - 100) / 100.0f;
		float dirY = (rand() % 201 - 100) / 100.0f;
		m_velocity = sf::Vector2f(dirX, dirY);
		m_changeDirectionTimer = 1.0f + ((rand() % 200) / 100.0f);
	}
	this->move(m_velocity.x * m_speed * dt, m_velocity.y * m_speed * dt);
}
sf::Vector2f Throngle::throngleTerritoryPosition(int familyId) {
	switch (familyId) {
	case 0:  {
		float randomPositionFamilyx = Resources::randomNumber(100, 800);
		float randomPositionFamilyy = Resources::randomNumber(100, 800);
		return { randomPositionFamilyx,randomPositionFamilyy };
	}
	case 1: {
		float randomPositionFamilyx = Resources::randomNumber(800, 1550);
		float randomPositionFamilyy = Resources::randomNumber(100, 850);
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