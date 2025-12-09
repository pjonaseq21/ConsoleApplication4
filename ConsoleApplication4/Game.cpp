#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <SFML/Graphics.hpp>
Game::Game() {
    window.create(sf::VideoMode({ 1600, 900 }), "Chmara");
    window.setFramerateLimit(60);
    m_state = GameState::MENU;
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}
//glowna funkcja
void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) { //sprawdzenie czy wcisnieto myszke
            if (mousePress->button == sf::Mouse::Button::Left) { //sprawdzenie czy lewy przycisk klikniety
                sf::Vector2f mousePos = window.mapPixelToCoords(mousePress->position);
                if (m_resources.menuButton.isClicked(mousePos)) { //czy klikniecie znajduje sie w pozycji przycisku
                    std::cout << "KLIKNIETO NOWA GRA!" << std::endl;
                    m_state = GameState::SIMULATION;

                }
            }
        }
    }
}

void Game::update() {
}

void Game::render() {
    window.clear();

    if (m_state == GameState::MENU) {
        window.draw(m_resources.backgroundMainMenu);
        m_resources.menuButton.render(window);
    }
    else if (m_state == GameState::CONFIG) {
        window.draw(m_resources.backgroundMainMenu);
        m_resources.menuButton.render(window);

    }
    window.display();
}