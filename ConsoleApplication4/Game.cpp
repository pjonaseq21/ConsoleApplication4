#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <SFML/Graphics.hpp>



    Game::Game() {
        window.create(sf::VideoMode({ 1600, 900 }), "Chmara");
        window.setFramerateLimit(60);
        m_state = GameState::MENU;
        throngles.emplace_back(); //stworzenie pierwszego stworka
    }

    void Game::run() {
        sf::Clock clock; 
        while (window.isOpen()) {
            sf::Time dt = clock.restart();
            processEvents();
            update(dt);
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
                    if (m_state == GameState::MENU) { //czy klikniecie znajduje sie w pozycji przycisku
                  
                                  if (m_resources.menuButton.isClicked(mousePos)) {
                                         m_resources.configPanel();
                                          m_state = GameState::CONFIG;
                                          return;
                                         }
                    
                   


                    }

                    else if (m_state == GameState::CONFIG)
                    {
                        std::vector<int> options = { 1,2,3 };

                        // std::cout << "Jestem w Stanie config";
                        for (size_t i = 0; i < m_resources.configButtons.size(); i++) {
                            if (m_resources.configButtons[i]->isClicked(mousePos)) {

                                m_resources.numberOfSettlements = options[i];
                                std::cout << "Wybrano ilość osad: ";
                          //tutaj dodac moze jakies podswietlenie na razie to dziala jako tako mozna przejsc do nastepnej rozgrywki
                                m_state = GameState::SIMULATION;
                                return;
                            }
                        }
                    }
                    else if (m_state == GameState::SIMULATION) {
                    //kod
                        std::cout << "znalezlismy sie tutaj";
                    }
                }
            }
        }
    }

    void Game::update(sf::Time dt) {
        
        if (m_state == GameState::SIMULATION) 
        {
                    m_timer += dt.asSeconds();
                    std::vector<Throngle> newBabies;


                    for (auto& throngle : throngles) {
                        throngle.update(m_timer);
                    if (m_timer > 0.5f) {

                   if (throngle.reproduction() == true)
                    {
                        newBabies.emplace_back();
                    }
                    
                    throngle.hungerDecrease();
                    }

                    for (const auto& baby : newBabies) {
                        throngles.push_back(baby);
                       // std::cout << throngles.size() << "  ilosc chmary"<<'\n';
                    }
                    }
        }


    }

    void Game::render() {
        window.clear();

        if (m_state == GameState::MENU) {
            window.draw(m_resources.backgroundMainMenu);
            m_resources.menuButton.render(window);
        }
        else if (m_state == GameState::CONFIG) {
             window.draw(m_resources.backgroundMainMenu);
            for (auto btn : m_resources.configButtons) {
                btn->render(window);
            }

        }
        
        else if (m_state == GameState::SIMULATION) {
            window.draw(m_resources.backgroundSimulation);
            for (auto& throngle : throngles) {
                throngle.render(window);
            }
        }
        window.display();
    }