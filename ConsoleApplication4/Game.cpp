#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Throngle.h"


Game::Game() :m_resources(m_globalfont), fightSprite(fightSpriteTexture) {
    if (!m_globalfont.openFromFile("assets/ARIAL.ttf") || !fightSpriteTexture.loadFromFile("assets/miecze.png")) {
        std::exit(1);
    }
    fightSprite.setTexture(fightSpriteTexture, true);
    m_resources.menuButton.centerText();

    window.create(sf::VideoMode::getDesktopMode(), "Chmara", sf::State::Fullscreen);

    sf::View view(sf::FloatRect({ 0.f, 0.f, }, { Game::WIDTH, Game::HEIGHT }));
    window.setView(view);

    window.setFramerateLimit(60);
    m_state = GameState::MENU;
}

    void Game::run() {
         
        while (window.isOpen()) {
            sf::Time dt = clock.restart();
            processEvents();
            update(dt);
            render();
        }
    }
    void Game::processEvents() {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) { //sprawdzenie czy wcisnieto myszke
                if (mousePress->button == sf::Mouse::Button::Left) { //sprawdzenie czy lewy przycisk klikniety
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePress->position);

                    //przyciski w symulacji
                    if (m_state == GameState::SIMULATION) {
                        if (m_resources.speedUpSprite.getGlobalBounds().contains(mousePos)) {
                            fastForward = !fastForward;
                        }
                        else if (m_resources.appleSpawnSprite.getGlobalBounds().contains(mousePos)) {
                            spawnApples(totalSimTime,true);
                            std::cout << "testowe klikniecie \n";

                        }

                        else if (m_resources.throngleSpawnSprite1.getGlobalBounds().contains(mousePos)) {
                            spawnSingleThrongle(0); // rodzina lewa
                        }
                        else if (m_resources.throngleSpawnSprite2.getGlobalBounds().contains(mousePos)) {
                            spawnSingleThrongle(1); // rodzina prawa
                        }


                    }
                    if (m_state == GameState::MENU) { //czy klikniecie znajduje sie w pozycji przycisku
                  
                        if (m_resources.menuButton.isClicked(mousePos)) {
                             m_resources.configPanel();
                             m_state = GameState::CONFIG;
                             return;
                        }
                    
                  
                    }
                    if (m_state == GameState::SIMULATION_END) {
                        if (m_resources.simEndButton.isClicked(mousePos)) {
                            resetSimulation();
                            m_state = GameState::SIMULATION;
                        }
                    }


                    if (m_state == GameState::SIMULATION_MENU) {

                        for (int i = 0; i < m_resources.simStopButtons.size(); i++)
                        {//przycisk 2 reset przycisk 1 wznów przycisk 3 menu 
                            if (m_resources.simStopButtons[i].isClicked(mousePos)) {
                                switch(i) {
                                case 0: resetSimulation(), m_state = GameState::SIMULATION; break;
                                case 1: resetSimulation(), m_state = GameState::MENU; break;
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



                        for (size_t i = 0; i < m_resources.configButtons.size(); i++) {
                            if (m_resources.configButtons[i].isClicked(mousePos)) {
                                
                                if (options[i] == 2) {
                                    std::cout << "test tryb numer dwa";
                                    world_config.mode = gameMode::twoVillages;
                                   
                                }
                                else {
                                    world_config.mode = gameMode::oneVillage;
                                    
                                }
                                
                                resetSimulation();
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

                    if (fastForward) {
                        dtSeconds *= 3.0f; 
                    }
                    if (m_timer > 0.5f) {
                        logicTic = true;
                        m_timer = 0.0f;
                    }
                    spawnApples(totalSimTime,false);
                    handleAppleEating();
                    handleDeadThrongles();
                    handleFight();
                    endGame(totalSimTime);
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
        
        else if (m_state == GameState::SIMULATION || m_state == GameState::SIMULATION_MENU || m_state == GameState::SIMULATION_END) {
           

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
            window.draw(m_resources.throngleSpawnSprite1);
            window.draw(m_resources.throngleSpawnSprite2);
            window.draw(m_resources.speedUpSprite);
            window.draw(m_resources.appleSpawnSprite);

            if (m_state == GameState::SIMULATION_END) {
                m_resources.endGamePanel(window, winningFamily);
                m_resources.simEndButton.render(window);
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

    //manipulacja iloscia jablek
    void Game::spawnApples(float totalSimTime,bool force) {
       if (apples.size() < 40- totalSimTime||force) {
           int count = force ? 2 : Resources::randomNumber(0, 5);
           for (int i = 0; i < count; i++) {
               apples.emplace_back(m_ground.returnFreeTile(),m_resources.appleTexture);
           }
       }
       if (apples.size() < 20 && world_config.mode== gameMode::twoVillages && totalSimTime >12 && !canFight ) {
           canFight = true;
           //tutaj chyba dodac 
           float bridgePos = m_ground.getBridgeCenterY();
           Throngle::crossBridge(bridgePos);
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
               
                            throngle->setHungerFight();
                        }
                        else {
                            throngle->setHunger();
                           
                            throngleSecond->setHungerFight();

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

                if (throngle->getBounds().findIntersection(it->getBounds()))
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
                if ((*it)->getHunger() <-0.15)
                {
                    if ((*it)->familyIdGet() == 0) {
                        countFamily_one -= 1;
                    }else{
                        countFamily_two -= 1;
                    }

                    it = throngles.erase(it); //zwraca iterator do nastepnego elementu
                    starvingThrongle = true;

                }

                if (!starvingThrongle) {
                    it++;
                }

            
            
        }
    }
    void Game::spawnThrongles(bool logicTic,float dtSeconds, std::vector<std::unique_ptr<Throngle>>& newBabies) {
        int babyHunger = 0.8f;
            for (auto& throngle : throngles) {
                throngle->update(dtSeconds, canFight);
                
                if (logicTic) {
                    if (throngles.size() < 60) {
                        if (throngle->reproduction() == true)
                        {
                            newBabies.push_back(std::make_unique<Throngle>(throngle->familyIdGet(), throngle->getTerritory(), sf::Vector2f{64,64}, babyHunger));
                            if (throngle->familyIdGet() == 0) countFamily_one++;
                            else countFamily_two++;
                        }
                    }
                    //throngle->hungerDecrease();
                }

            }
        
        
    }
    sf::FloatRect Game::setTerritory(int familyId) const
    {
        if (world_config.mode == gameMode::oneVillage)
        {
            return { {0.f, 0.f}, {Game::WIDTH, Game::HEIGHT} };
        }
        else
        {
            if (familyId == 0)
                return { {0.f, 0.f}, {Game::WIDTH / 2.0f, Game::HEIGHT} };
            else
                return { {Game::WIDTH / 2.0f, 0.f}, {Game::WIDTH / 2.0f, Game::HEIGHT} };
        }
    }
    void Game::resetSimulation() {
        throngles.clear();
        apples.clear();
        totalSimTime = 0;
        countFamily_one = 0;
        countFamily_two = 0;
        fastForward = false;
        canFight = false;

        if (world_config.mode == gameMode::twoVillages) {

            m_ground.init((unsigned int)Game::WIDTH, (unsigned int)Game::HEIGHT, false);

            throngles.push_back(std::make_unique<Throngle>(0, setTerritory(0)));
            throngles.push_back(std::make_unique<Throngle>(1, setTerritory(1)));
            countFamily_one += 1;
            countFamily_two += 1;
            apples.emplace_back(m_ground.returnFreeTile(), m_resources.appleTexture);
        }
        else {
            world_config.mode = gameMode::oneVillage;

            m_ground.init((unsigned int)Game::WIDTH, (unsigned int)Game::HEIGHT, true);

            throngles.push_back(std::make_unique<Throngle>(0, setTerritory(0)));
            apples.emplace_back(m_ground.returnFreeTile(), m_resources.appleTexture);
        }
    }

    void Game::endGame(float totalSimTime) {
        if (world_config.mode==gameMode::twoVillages) {

                if (totalSimTime > 2) {
                    if (countFamily_one <= 0) {
                        std::cout << " wygrala rodzina czerwona";
                        winningFamily = 1;
                        m_state = GameState::SIMULATION_END;
      

                    }
                    else if (countFamily_two <= 0) {
                        std::cout << " wygrala rodzina żółta";
                        winningFamily = 0;
                        m_state = GameState::SIMULATION_END;
                     


                    }

                }
        }
    }
    void Game::spawnSingleThrongle(int familyId) {
  
        throngles.push_back(std::make_unique<Throngle>(
            familyId,
            setTerritory(familyId),
            sf::Vector2f{ 64, 64 },
            0.8f
        ));

        if (familyId == 0) countFamily_one++;
        else countFamily_two++;

    }