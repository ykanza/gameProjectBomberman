//
// Created by ilias on 18/06/2021.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "Menu/Menu.hpp"

void setImagesMenu(std::unique_ptr<RL::Graphics> &visual)
{
    visual->setImage("Button", "assets/menu/button.png");
    visual->setImage("ButtonPushed", "assets/menu/buttonPushed.png");
    visual->setImage("ButtonArrow", "assets/menu/buttonArrow.png");
    visual->setImage("ButtonArrowPushed", "assets/menu/buttonArrowPushed.png");
    visual->setImage("Selector", "assets/menu/selector.png");
    visual->setImage("GameOver", "assets/menu/gameOver.png");
    visual->setImage("BackgroundMenu", "assets/menu/backgroundMenu.png");
}

void setHud(std::unique_ptr <RL::Graphics> &visual)
{
    visual->setImage("StatJ1", "assets/icon/StatJ1b.png");
    visual->setImage("StatJ2", "assets/icon/StatJ2b.png");
    visual->setImage("StatJ3", "assets/icon/StatJ3b.png");
    visual->setImage("StatJ4", "assets/icon/StatJ4b.png");
    visual->setImage("StatJ1Dead", "assets/icon/StatJ1b_dead.png");
    visual->setImage("StatJ2Dead", "assets/icon/StatJ2b_dead.png");
    visual->setImage("StatJ3Dead", "assets/icon/StatJ3b_dead.png");
    visual->setImage("StatJ4Dead", "assets/icon/StatJ4b_dead.png");
    visual->setImage("Cross", "assets/icon/cross.png");
}

void unLoadAllImages(std::unique_ptr <RL::Graphics> &visual)
{
    for (auto &e : visual->getImage())
        UnloadImage(e.second);
    for (auto &e : visual->getTexture())
        UnloadTexture(e.second);
}
