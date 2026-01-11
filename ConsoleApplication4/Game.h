#pragma once 
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <vector>
#include "Apple.h"
#include "Throngle.h"
#include "Ground.h"
#include "gameSettings.h"
enum class GameState {
    MENU,
    SIMULATION,
    SIMULATION_MENU,
    CONFIG,
    GAME_OVER
};

class Game {
public:
    Game(); 
    void run(); 

private:
    sf::Font m_globalfont;
    Ground m_ground;
    gameConfig world_config;
    float totalSimTime = 0.0f;
    bool canFight = false;
    void processEvents(); 
    void update(sf::Time dt);       
    void render();   
    GameState m_state;
    Resources m_resources;
    sf::RenderWindow window;
    std::vector<Throngle> throngles;
    void spawnThrongles(bool logicTic, float dtSeconds, std::vector<Throngle>& newBabies);
    float m_timer;
    std::vector<Apple> apples;
    void spawnApples(float totalSimTime);
    sf::FloatRect setTerritory(int familyId)const;
    void handleAppleEating();
    void handleDeadThrongles();
    void resetSimulation();

};