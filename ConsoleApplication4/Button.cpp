#include <string>
#include "Button.h"

Button::Button(sf::Font& font, sf::String text, sf::Vector2f position, sf::Vector2f size)
    : buttonText(font)
{
    button.setSize(size);

  
    button.setOrigin({ size.x / 2.0f , size.y / 2.0f });

    button.setPosition(position);

    buttonText.setString(text);
    buttonText.setCharacterSize(20);

    button.setFillColor(sf::Color(76, 107, 125));
    button.setOutlineThickness(3.f);
    button.setOutlineColor(sf::Color(35, 45, 60));

    centerText();
}

void Button::render(sf::RenderWindow& window) {
    window.draw(button);
    centerText();
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

void Button::centerText() {
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin({
        textRect.position.x + textRect.size.x / 2.0f,
        textRect.position.y + textRect.size.y / 2.0f
        });


    buttonText.setPosition(button.getPosition());
}