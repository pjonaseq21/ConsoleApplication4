#include <string>
#include "Button.h"



Button::Button(sf::Font& font, std::string text, sf::Vector2f position, sf::Vector2f size):buttonText(font) {
	

	button.setSize(size);
	button.setPosition(position);
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(20);

	button.setFillColor(sf::Color(76, 107, 125));
	button.setOutlineThickness(3.f);
	button.setOutlineColor(sf::Color(35, 45, 60));


	sf::FloatRect textRect = buttonText.getLocalBounds();


	buttonText.setOrigin({
		textRect.position.x + textRect.size.x / 2.0f,
		textRect.position.y + textRect.size.y / 2.0f
		});

	buttonText.setPosition({
		button.getPosition().x + button.getSize().x / 2.2f,
		button.getPosition().y + button.getSize().y / 2.5f
		});

}



void Button::render(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2f mousepos) {
	
	if (button.getGlobalBounds().contains(mousepos)) {
		return true;
	}
	else {
		return false;
	}
}