#pragma once
#include <SFML/Graphics.hpp>
#include <string>
//

class Button
{
public:
	Button(sf::Font& font, sf::String text, sf::Vector2f postion, sf::Vector2f size = { 240.f, 50.f });
	void render(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousepos);
	void centerText();
private:
	sf::RectangleShape button;
	sf::Text buttonText;

};

