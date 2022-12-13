/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/

#include "Menu.hpp"

Menu::Menu()
{
    selector.x = 178;
    selector.y = 486;
    menuSelector = MENU;
}

void Menu::restartMenu()
{
    menuSelector = MENU;
    selector.y = 486;
}

float Menu::getMapSize() const {
    return gameSettings.mapSize;
}

void Menu::setSelector(ButtonSelector selector) {
    menuSelector = selector;
}

void Menu::resetSelector() {
    selector.y = 486;
}

void Menu::displayMenu(std::unique_ptr<RL::Graphics> &visual)
{
    visual->clear();
    visual->beginDrawing();
    visual->drawImage("BackgroundMenu", 0, 0);
    visual->drawImage("Button", 200, 486);
    visual->drawImage("ButtonPushed", 200, selector.y);

    DrawText("PLAY", 298, 506, 25, BLACK);
    if (RL::Event::isKeyPressed(KEY_ENTER)) {
        menuSelector = PREGAME;
        selector.y = 300;
    }

    visual->drawImage("Selector", selector.x, selector.y);
    visual->endDrawing();
}


void Menu::displayPreGame(std::unique_ptr<RL::Graphics> &visual)
{
    visual->clear();
    visual->beginDrawing();
    visual->drawImage("BackgroundMenu", 0, 0);
    visual->drawImage("Button", 200, 300);
    visual->drawImage("ButtonArrow", 200, 400);
    visual->drawImage("ButtonArrow", 200, 500);
    visual->drawImage("ButtonArrow", 200, 600);
    if (selector.y == 300)
        visual->drawImage("ButtonPushed", 200, selector.y);
    else
        visual->drawImage("ButtonArrowPushed", 200, selector.y);
    std::string mapSize = "map: " + std::to_string((int)gameSettings.mapSize) + " x " + std::to_string((int)gameSettings.mapSize);
    std::string nbPlayer = "nb Player: " + std::to_string(gameSettings.nbHumanPlayer);
    std::string nbAI = "nb AI: " + std::to_string(gameSettings.nbAIPlayer);
    DrawText("START GAME", 243, 320, 25, BLACK);
    DrawText(mapSize.c_str(), 268, 420, 25, BLACK);
    DrawText(nbPlayer.c_str(), 253, 520, 25, BLACK);
    DrawText(nbAI.c_str(), 278, 620, 25, BLACK);
    int nbPlayers = gameSettings.nbAIPlayer + gameSettings.nbHumanPlayer;
    if (RL::Event::isKeyPressed(KEY_ENTER) && selector.y == 300)
        menuSelector = GAME;
    if (RL::Event::isKeyPressed(KEY_UP) && selector.y != 300)
        selector.y -= 100;
    if (RL::Event::isKeyPressed(KEY_DOWN) && selector.y != 600)
        selector.y += 100;
    if (RL::Event::isKeyPressed(KEY_LEFT)) {
        if (gameSettings.mapSize > 9 && selector.y == 400)
            gameSettings.mapSize -= 2;
        else if (nbPlayers > 2 && gameSettings.nbHumanPlayer > 0 && selector.y == 500)
            gameSettings.nbHumanPlayer--;
        else if (nbPlayers > 2 && gameSettings.nbAIPlayer > 0 && selector.y == 600)
            gameSettings.nbAIPlayer--;
    } else if (RL::Event::isKeyPressed(KEY_RIGHT)) {
        if (gameSettings.mapSize < 31 && selector.y == 400)
            gameSettings.mapSize += 2;
        else if (nbPlayers < 4 && gameSettings.nbHumanPlayer < 4 && selector.y == 500)
            gameSettings.nbHumanPlayer++;
        else if (nbPlayers < 4 && gameSettings.nbAIPlayer < 4 && selector.y == 600)
            gameSettings.nbAIPlayer++;
    }
    visual->drawImage("Selector", selector.x, selector.y);
    visual->endDrawing();
}

ButtonSelector Menu::getStatusPlay() const {
    return this->menuSelector;
}

GameSettings Menu::getGameSettings() const {
    return this->gameSettings;
}
