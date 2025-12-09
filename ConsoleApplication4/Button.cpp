#include <string>
#include "Button.h"

Button::Button(sf::Font& font, std::string text, sf::Vector2f position, sf::Vector2f size):buttonText(font) {
	if (!font.openFromFile("assets/ARIAL.ttf")) std::exit(1);

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
		button.getPosition().x + button.getSize().x / 4.0f,
		button.getPosition().y + button.getSize().y / 2.0f
		});

}

void Button::render(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2f mousepos) {
	
	if (button.getGlobalBounds().contains(mousepos)) {
		std::cout << "KLIKNIETO NOWA GRA!" << std::endl;
		return true;
	}
}