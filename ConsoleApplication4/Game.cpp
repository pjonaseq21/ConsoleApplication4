#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <SFML/Graphics.hpp>



    Game::Game():m_resources(m_globalfont), fightSprite(fightSpriteTexture) {
        if (!m_globalfont.openFromFile("assets/ARIAL.ttf") || !fightSpriteTexture.loadFromFile("assets/miecze.png")) {
            std::exit(1);
        }
        fightSprite.setTexture(fightSpriteTexture, true);
        m_resources.menuButton.centerText();
        window.create(sf::VideoMode({ 1600, 900 }), "Chmara");
        window.setFramerateLimit(60);
        m_state = GameState::MENU;
        apples.emplace_back(m_ground.returnFreeTile()); //stworzenie pierwszego jablka
        
    }

    void Game::run() {
         
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
                    if (m_state == GameState::SIMULATION_MENU) {

                        for (int i = 0; i < m_resources.simStopButtons.size(); i++)
                        {//przycisk 2 reset przycisk 1 wznów przycisk 3 menu 
                            if (m_resources.simStopButtons[i].isClicked(mousePos)) {
                                switch(i) {
                                case 0: resetSimulation(); break;
                                case 1: m_state = GameState::MENU; break;
                                case 2: m_state = GameState::SIMULATION; break;
                                }
                            }

                        }
                    }

                    else if (m_state == GameState::CONFIG)
                    {
                        throngles.clear();
                        apples.clear();
                        
                        std::vector<int> options = { 1,2 };



                        // std::cout << "Jestem w Stanie config";
                        for (size_t i = 0; i < m_resources.configButtons.size(); i++) {
                            if (m_resources.configButtons[i].isClicked(mousePos)) {
                                
                                if (options[i] == 2) {
                                    std::cout << "test tryb numer dwa";
                                    world_config.mode = gameMode::twoVillages;
                                    throngles.push_back(std::make_unique<Throngle>(0,setTerritory(0)));
                                    throngles.push_back(std::make_unique<Throngle>(1, setTerritory(1)));
                                }
                                else {
                                    world_config.mode = gameMode::oneVillage;
                                    throngles.push_back(std::make_unique<Throngle>(0, setTerritory(0)));
                                }
                                
                               
                                std::cout << "Wybrano ilość osad: ";
                          //tutaj dodac moze jakies podswietlenie na razie to dziala jako tako mozna przejsc do nastepnej rozgrywki
                                m_state = GameState::SIMULATION;
                                return;
                            }
                        }
                    }
                  
                }

            }
            else if (m_state == GameState::SIMULATION && event->getIf<sf::Event::KeyPressed>()) {
                std::cout << "test1";
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        m_state = GameState::SIMULATION_MENU;
                        return;
                    }
                }

            }

        }
    }

    void Game::update(sf::Time dt) {
        
        if (m_state == GameState::SIMULATION) 
        {           
                    float dtSeconds = dt.asSeconds();
                    m_timer += dtSeconds;
                    
                    totalSimTime += dtSeconds;
                   

                    std::vector<std::unique_ptr<Throngle>> newBabies;
                    bool logicTic = false;
                    float groundCooldown = 0.0f;
                    m_ground.update(dtSeconds);
                    if (m_timer > 0.5f) {
                        logicTic = true;
                        m_timer = 0.0f;
                    }
                    spawnApples(totalSimTime);
                    handleAppleEating();
                    handleDeadThrongles();
                    handleFight();
                    spawnThrongles(logicTic,dtSeconds,newBabies);
                    for (auto& baby : newBabies) {
                        throngles.push_back(std::move(baby));
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
            for (auto& btn : m_resources.configButtons) {
                btn.render(window);
            }

        }
        
        else if (m_state == GameState::SIMULATION || m_state == GameState::SIMULATION_MENU) {
          

            window.draw(m_resources.backgroundSimulation);
            m_ground.render(window);
            for (auto& throngle : throngles) {
                throngle->render(window);
            }
            for (auto& apple : apples) {
                apple.render(window);
            }
            if (fightSpriteBool && fightClock.getElapsedTime().asSeconds() > 2.0f)fightSpriteBool = false;
            if (fightSpriteBool == true) {
                window.draw(fightSprite);
            }
            if (m_state == GameState::SIMULATION_MENU) {
                m_resources.simMenu(window);
                for (auto& btn : m_resources.simStopButtons) {
                    btn.render(window);
                }

            }
        }
        window.display();
    }


    void Game::spawnApples(float totalSimTime) {
       
       if (apples.size() < 60- totalSimTime) {
           for (int i = 0; i < Resources::randomNumber(0, 5); i++) {
               apples.emplace_back(m_ground.returnFreeTile());
               std::cout << apples.size()<<"\n";
           }
       }
       if (apples.size() < 40 && world_config.mode== gameMode::twoVillages && totalSimTime >12.0f) {
           canFight = true;
       }
    
    }
    void Game::handleFight() {
        if (canFight == true) {
            for (auto& throngle : throngles) {
                
                for (auto& throngleSecond : throngles) {
                    
                    if (&throngle == &throngleSecond || throngle->familyIdGet() == throngleSecond->familyIdGet()) {
                        continue;
                    }

                    if (throngle->getBounds().findIntersection(throngleSecond->getBounds())) {
                        if (throngle->getHunger() > throngleSecond->getHunger()) {

                            fightSprite.setPosition({throngle->getBounds().position.x, throngle->getBounds().position.y});
                            fightClock.restart();
                            fightSpriteBool = true;

                            throngleSecond->setHunger();
                            std::cout << "został ojebany \n";

                        }
                        else {
                            throngle->setHunger();
                            std::cout << " zostal ojebany \n";
                        }
                    }
                }
            }
        }
    }
    void Game::handleAppleEating() {
           for (auto it = apples.begin(); it != apples.end();) {
            bool wasEaten = false;
            for (auto& throngle : throngles) {

                if (throngle->getBounds().findIntersection(it->getBounds())&& !throngle->getStateFight())
                {
                    sf::Vector2f eatenPosition = it->getPosition();
                    m_ground.ReleasePosition(eatenPosition);
                    it = apples.erase(it); //zwraca iterator do nastepnego elementu
                    wasEaten = true;
                    throngle->eat();
                    throngle->wasEatenFunc();
                    break;
                }
               

               
            }
            if (!wasEaten) {
                it++;
            }
        }
    }
    void Game::handleDeadThrongles() {
        for (auto it = throngles.begin(); it != throngles.end();) {
            bool starvingThrongle = false;
                if ((*it)->getHunger() <-0.05)
                {
                    it = throngles.erase(it); //zwraca iterator do nastepnego elementu
                    starvingThrongle = true;
                }

                if (!starvingThrongle) {
                    it++;
                }

            
            
        }
    }
    void Game::spawnThrongles(bool logicTic,float dtSeconds, std::vector<std::unique_ptr<Throngle>>& newBabies) {
        
            for (auto& throngle : throngles) {

                throngle->update(dtSeconds, canFight);

                if (logicTic) {
                    if (throngles.size() < 70) {
                        if (throngle->reproduction() == true)
                        {
                            newBabies.push_back(std::make_unique<Throngle>(throngle->familyIdGet(), throngle->getTerritory()));
                        }
                    }
                    throngle->hungerDecrease();
                }

            }
        
        
    }
    sf::FloatRect Game::setTerritory(int familyId)const
    {
        if (world_config.mode == gameMode::oneVillage)
        {
            return { {0.f, 0.f}, {1600.f, 900.f} };
        }
        else
        {
            if (familyId == 0)
                return { {0.f, 0.f}, {800.f, 900.f} };
            else
                return { {800.f, 0.f}, {800.f, 900.f} };
        }
    }
    void Game::resetSimulation() {
        throngles.clear();
        apples.clear();
        totalSimTime =0;
        m_state = GameState::SIMULATION;
        if (world_config.mode ==gameMode::twoVillages) {
            throngles.push_back(std::make_unique<Throngle>(0, setTerritory(0)));
            throngles.push_back(std::make_unique<Throngle>(1, setTerritory(1)));
            apples.emplace_back(m_ground.returnFreeTile());
            
        }
        else {
            world_config.mode = gameMode::oneVillage;
            throngles.push_back(std::make_unique<Throngle>(0, setTerritory(0)));
            apples.emplace_back(m_ground.returnFreeTile());

        }

    }
