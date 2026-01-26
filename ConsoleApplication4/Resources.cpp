#include "Resources.h"
#include "Game.h" // Ważne: żeby widzieć Game::WIDTH i Game::HEIGHT
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

Resources::Resources(sf::Font& font)
    : sharedFont(font),
    menuButton(font, "Nowa Gra", { Game::WIDTH / 2.0f, Game::HEIGHT / 2.0f }, { 200.f, 50.f }),
    backgroundMainMenu(backgroundTexture),
    backgroundSimulation(simTexture),
    simEndButton(font, "Zrestartuj Gre", { Game::WIDTH / 2.0f, Game::HEIGHT / 2.0f }, { 150.f, 50.f }),
    endGameText(font),
    speedUpSprite(speedUpTexture),
    appleSpawnSprite(appleSpawnTexture),
    throngleSpawnSprite1(throngleSpawnTexture1),
    throngleSpawnSprite2(throngleSpawnTexture2)

{

    if (!throngleSpawnTexture1.loadFromFile("assets/spawnThrongle1.png")) {
        std::cerr << "texture error \n";
    }
    else {
        throngleSpawnSprite1.setTexture(throngleSpawnTexture1, true);
    }

    if (!throngleSpawnTexture2.loadFromFile("assets/spawnThrongle2.png")) {
        std::cerr << "texture error \n";
    }
    else {
        throngleSpawnSprite2.setTexture(throngleSpawnTexture2, true);
    }
    throngleSpawnSprite1.setPosition(sf::Vector2f(Game::WIDTH / 2.0f - 250.0f, Game::HEIGHT * 0.01f + 70.0f)); // lewo

    throngleSpawnSprite2.setPosition(sf::Vector2f(Game::WIDTH / 2.0f + 50.f, Game::HEIGHT * 0.01f + 70.0f)); // prawo




    endGameText.setFont(sharedFont);
    endGameText.setCharacterSize(60);
    endGameText.setFillColor(sf::Color::White);
    endGameText.setOutlineColor(sf::Color::Black);
    endGameText.setOutlineThickness(3.0f);

    if (!speedUpTexture.loadFromFile("assets/speedupButton.png")) {
        std::cerr << "texture error \n";
    }

    speedUpTexture.setSmooth(false);
    speedUpSprite.setTexture(speedUpTexture, true);
    auto bounds = speedUpSprite.getLocalBounds();
    speedUpSprite.setOrigin(bounds.size / 2.0f);

    speedUpSprite.setPosition(sf::Vector2f(Game::WIDTH / 2.f, Game::HEIGHT * 0.01f + 70.0f));
    speedUpSprite.setScale({ 2, 2 });

    if (!appleSpawnTexture.loadFromFile("assets/spawnAppleUi.png")) {
        std::cerr << "texture error \n";
    }
    appleSpawnSprite.setTexture(appleSpawnTexture, true);
    appleSpawnSprite.setPosition(sf::Vector2f(Game::WIDTH / 2.f - 100, speedUpSprite.getPosition().y + 150.0f));


    if (!appleTexture.loadFromFile("assets/apple.png")) {
        std::cerr << "texture error \n";
    }

    // Tła
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundMainMenu.setTexture(backgroundTexture, true);
    }

    if (!simTexture.loadFromFile("assets/unnamed.png")) {
        std::cerr << "BLAD: Nie udalo sie zaladowac tekstury!" << std::endl;
    }
    else {
        backgroundSimulation.setTexture(simTexture, true);
    }
}


float Resources::randomNumber(float x1, float x2) {
    std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(x1, x2);
    return dist(mt);
}

void Resources::scaleSprite(sf::RenderWindow& window) {
   

    sf::Vector2u simSize = simTexture.getSize();
    float simScaleX = Game::WIDTH / simSize.x;
    float simScaleY = Game::HEIGHT / simSize.y;
    backgroundSimulation.setScale({ simScaleX, simScaleY });

    sf::Vector2u menuSize = backgroundTexture.getSize();
    float menuScaleX = Game::WIDTH / menuSize.x;
    float menuScaleY = Game::HEIGHT / menuSize.y;
    backgroundMainMenu.setScale({ menuScaleX, menuScaleY });
}

void Resources::simMenu(sf::RenderWindow& window) {
    // Overlay na cały wirtualny ekran
    Overlay.setSize({ Game::WIDTH, Game::HEIGHT });
    Overlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(Overlay);

    simStopButtons.clear();
    float startY = Game::HEIGHT / 2 + 100;
    std::vector<int> options = { 1, 2, 3 };

    for (int optionValue : options) {
        if (optionValue == 1) {
            label = "Restartuj";
        }
        else if (optionValue == 2) {
            label = L"Menu Główne";
        }
        else {
            label = L"Wróc do gry";
        }

        simStopButtons.emplace_back(sharedFont, label, sf::Vector2f{ Game::WIDTH / 2.0f, startY }, sf::Vector2f{ 150.f, 50.f });
        startY -= 100.f;
    }
}

void Resources::endGamePanel(sf::RenderWindow& window, int winningFamily) {
    // Overlay na cały wirtualny ekran
    Overlay.setSize({ Game::WIDTH, Game::HEIGHT });
    Overlay.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(Overlay);

    switch (winningFamily) {
    case 0:
        endGameText.setString(L"wygrała rodzina żółtych");
        break;

    case 1:
        endGameText.setString(L"wygrała rodzina czerwonych");
        break;
    }

    // Centrowanie tekstu
    endGameText.setPosition(sf::Vector2f((Game::WIDTH / 2.0f) - 250.f, (Game::HEIGHT / 2.0f - 150.0f)));
    window.draw(endGameText);
}


void Resources::configPanel()
{
    float startX = Game::WIDTH / 2.0f + 50;

    configButtons.clear();
    std::vector<int> options = { 1, 2 };

    for (int optionValue : options) {
        if (optionValue > 1) {
            label = std::to_string(optionValue) + " osady";
        }
        else {
            label = std::to_string(optionValue) + " osada";
        }

        configButtons.emplace_back(sharedFont, label, sf::Vector2f{ startX, Game::HEIGHT / 2.0f }, sf::Vector2f{ 100.f, 50.f });
        startX -= 150;
    }
}