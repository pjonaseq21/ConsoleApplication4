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
	float nextX = currentPosition.x + moveToX;
	float nextY = currentPosition.y + moveToY;

	float screenW = static_cast<float>(desktop_Size.size.x);
	float screenH = static_cast<float>(desktop_Size.size.y);
	std::cout << screenW;
	if (nextX < screenH*0.05) nextX = screenH*0.05;
	if (nextX > screenW*0.95) nextX = screenW*0.95;
	if (nextY < screenH*0.05) nextY = screenH*0.05;
	if (nextY > screenH*0.95) nextY = screenH*0.95;

	float gapWidth = screenW * 0.3f;
	float centerX = screenW / 2.0f;
	
	float cliffLeft = centerX - (gapWidth / 2.0f);
	float cliffRight = centerX + (gapWidth / 2.0f);

	float bridgeHeight = 250.0f;
	float centerY = screenH / 2.0f;
	float bridgeTop = centerY - (bridgeHeight / 2.0f);
	float bridgeBottom = centerY + (bridgeHeight / 2.0f);

	bool isInsideGapX = (nextX > cliffLeft && nextX < cliffRight);
	bool isOutsideBridgeY = (nextY < bridgeTop || nextY > bridgeBottom);
//	std::cout << isInsideGapX << std::endl;
	if (isInsideGapX && isOutsideBridgeY) {
		if (nextX < centerX) {
			nextX = cliffLeft;
		}
		else {
			nextX = cliffRight;
		}
	}

	hitbox.setPosition({ nextX, nextY });
	throngleSprite.setPosition({ nextX, nextY });
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
	currSize.x *= 1.1;
	currSize.y *= 1.05;
	
		sf::Vector2f textureSize;
		textureSize.x = static_cast<float>(throngleSprite.getTextureRect().size.x);
		textureSize.y = static_cast<float>(throngleSprite.getTextureRect().size.y);
		throngleSprite.setScale({ currSize.x / textureSize.x , currSize.y / textureSize.y });
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
			float dirX = 0;

			float dirY = 0.0f;
			if (std::abs(missingY) > 10) {
				dirY = (missingY > 0) ? 1.0f : -1.0f;
				dirX = (rand() % 201 - 100) / 100;

			}
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
	float firstFamilyS = desktop_Size.size.x * 0.07;
	float firstFamilyE = desktop_Size.size.x * 0.3;
	float secondFamilyS = desktop_Size.size.x * 0.7;
	float secondFamilyE = desktop_Size.size.x * 0.9;

	float yAxis = desktop_Size.size.y * 0.7;

	switch (familyId) {
	case 0:  {
		float randomPositionFamilyx = Resources::randomNumber(firstFamilyS, firstFamilyE);
		float randomPositionFamilyy = Resources::randomNumber(50, yAxis);
		return { randomPositionFamilyx,randomPositionFamilyy };
	}
	case 1: {
		float randomPositionFamilyx = Resources::randomNumber(secondFamilyS, secondFamilyE);
		float randomPositionFamilyy = Resources::randomNumber(5, yAxis);
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