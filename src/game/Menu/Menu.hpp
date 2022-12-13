/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** TODO: add description
*/
#ifndef BOMBERMAN_MENU_HPP
#define BOMBERMAN_MENU_HPP

#include <vector>
#include <memory>
#include "../../raylib/graphics/graphics.hpp"
#include "../../raylib/events/event.h"
#include "../Engine/Engine.h"

typedef struct selectorPos_s {
    int x;
    int y;
} selectorPos_t;

enum ButtonSelector {
    GAME,
    PREGAME,
    SETTINGS,
    MENU
};

class Menu {
    public:
        Menu();
        ~Menu() = default;

    public:
        void displayMenu(std::unique_ptr<RL::Graphics> &visual);
        void displayPreGame(std::unique_ptr<RL::Graphics> &visual);
        void restartMenu();

    public:
        ButtonSelector getStatusPlay() const;
        float getMapSize() const;
        void setSelector(ButtonSelector);
        void resetSelector();
        GameSettings getGameSettings() const;

    private:
        ButtonSelector menuSelector;
        selectorPos_t selector;
        GameSettings gameSettings;
};

#endif //BOMBERMAN_MENU_HPP
