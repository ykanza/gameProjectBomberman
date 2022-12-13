//
// Created by ilias on 07/06/2021.
//

#include <fstream>
#include "Engine.h"

//************************ ENGINE ***********************
Engine::Engine() : audio(100), gameMap(), bomb({ 0 }, { "assets/bomb/bomb.iqm", "assets/bomb/bomb_animation.iqm", "assets/bomb/Bomb.png" }),
fire({ 0 }, "assets/bomb/fire.iqm", "assets/bomb/Fire.png")
{
    this->audio.loadMusic("assets/audio/in_game.wav", "ost");
    this->audio.loadSound("assets/audio/bomb_drop.wav", "bomb_drop");
    this->audio.loadSound("assets/audio/bomb_explosion.wav", "bomb_explosion");
    this->isInGameOverMenu = false;
    playersModel = {
        {{ 0 }, { "assets/character/kid.iqm", "assets/character/kid_run.iqm", "assets/character/kid_texture_j1.png" }},
        {{ 0 }, { "assets/character/kid.iqm", "assets/character/kid_run.iqm", "assets/character/kid_texture_j2.png" }},
        {{ 0 }, { "assets/character/kid.iqm", "assets/character/kid_run.iqm", "assets/character/kid_texture_j3.png" }},
        {{ 0 }, { "assets/character/kid.iqm", "assets/character/kid_run.iqm", "assets/character/kid_texture_j4.png" }}
    };
}

int Engine::getAlivePlayer() {
    int i = 0;
    for (i = 0; i < this->players.size(); i++) {
        if (!this->players[i]->getIsDead()) {
            return i;
        }
    }

    return -1;
}

int Engine::getDeadPlayer() {
    int i = 0;
    int nbPlayers = this->players.size();
    for (i = 0; i < this->players.size(); i++) {
        if (this->players[i]->getIsDead()) {
            nbPlayers--;
        }
    }

    return nbPlayers;
}
