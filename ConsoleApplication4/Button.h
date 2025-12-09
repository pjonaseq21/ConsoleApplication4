#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
//

class Button
{
public:
	Button(sf::Font& font, std::string text, sf::Vector2f postion, sf::Vector2f size = { 240.f, 50.f });
	void render(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousepos);
private:
	sf::RectangleShape button;
	sf::Text buttonText;

};

