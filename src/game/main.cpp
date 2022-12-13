#include <list>
#include "Menu/Menu.hpp"
#include <cmath>
#include <algorithm>
#include "../raylib/myRaylib.h"
#include "Engine/Engine.h"
#include "Engine/Player/Player.hpp"
#include "prototypes.h"
#include "Engine/Player/AI.h"

#include <iostream>

void playerManagement(std::unique_ptr <Engine> &engine,
std::unique_ptr <RL::Graphics> &visual, std::unique_ptr<APlayer> &player)
{
    static bool moving = false;

    moving = player->move(engine->gameMap.getMapBlocks());
    player->getModel().playAnimation(!moving);
    player->getModel().draw({
        player->getPosition(),
        player->getRotation(),
        player->getScale(),
        player->getRotationAngle()
    });
}

int run(GameSettings gameSettings, std::unique_ptr <RL::Graphics> &visual, std::unique_ptr<RL::Window> &window, std::unique_ptr <Engine> &engine)
{
    std::vector <bombAnimation_t> listBombAnimation;
    engine->audio.playMusic("ost");
    engine->gameMap.setMap(gameSettings.mapSize);
    pos_t tempPos[4] = {{ gameSettings.mapSize * 2.4f - 4.8f, -1, (gameSettings.mapSize * 2.4f) - 6.0f },
                        { 2.5f, -1, 1.5f },
                        { gameSettings.mapSize * 2.4f - 4.8f, -1, 1.5f },
                        { 2.5f, -1, (gameSettings.mapSize * 2.4f) - 6.0f }};
    int nbPlayers = gameSettings.nbHumanPlayer + gameSettings.nbAIPlayer, i = 0;
    for (; i < gameSettings.nbHumanPlayer; i++)
        engine->createNewPlayer<Player>(tempPos[i], engine->playersModel[i], static_cast<playerNum> (i));
    for (; i < nbPlayers; i++)
        engine->createNewPlayer<AI>(tempPos[i], engine->playersModel[i], static_cast<playerNum> (i));
    visual->createCamera({ gameSettings.mapSize * 1.143f - 0.6f, gameSettings.mapSize * 2.5f, gameSettings.mapSize * 0.8f - 0.9f }, { gameSettings.mapSize * 1.143f - 0.6f, 0.0f, gameSettings.mapSize * 1.08f - 0.9f }, { 0.0f, 1.0f, 0.0f });

    std::vector<RL::NonAnimatedModel> bonus;
    setBonusPosition(bonus, engine->gameMap.getMapBlocks());
    while (window->isOpen() && !window->getShouldClose()) {
        visual->clear();
        engine->audio.updateMusic("ost");
        if (engine->getDeadPlayer() == 1 && !engine->isInGameOverMenu) {
            RL::Graphics::playVideo("assets/video/game_over.mpg", 150);
            window->setCursorState(true);
            engine->isInGameOverMenu = true;
        }
        if (engine->isInGameOverMenu) {
            int ret = displayGameOver(visual, window, engine, gameSettings);
            if (ret == 1)
                return 1;
            else if (ret == 2)
                break;
        } else {
            visual->beginDrawing();
            visual->start3Dscene();
            visual->clear();
            engine->gameMap.draw();
            engine->gameMap.drawBackGround();
            for (auto &powerup : bonus)
                powerup.draw();
            for (int i = 0; i < nbPlayers; i++) {
                if (!engine->players[i]->getIsDead()) {
                    playerManagement(engine, visual, engine->players[i]);
                    bombManagement(engine, visual, listBombAnimation, engine->players[i]);
                    checkBonus(bonus, engine->players[i], engine);
                }
            }
            engine->bomb.playAnimation();
            for (int i = 0; i < nbPlayers; i++) {
                for (auto &e : engine->players[i]->getBomb())
                    engine->bomb.draw({e.position, {1.00f, 0.00f, 0.00f}, {2.00f, 2.00f, 2.00f}});
            }
            visual->stop3Dscene();
            drawHud(visual, engine, gameSettings.nbHumanPlayer + gameSettings.nbAIPlayer);
            visual->endDrawing();
        }
    }
    engine->players.clear();
    engine->gameMap.clearMap();
    bonus.clear();
    for (auto &e : bonus) {
        UnloadTexture(e.getTexture());
        UnloadModel(e.getModel());
    }
    return 0;
}

void unloadAll(std::unique_ptr <Engine> &engine)
{
    for (auto &e : engine->players) {
        UnloadTexture(e->getModel().getTexture());
        UnloadModel(e->getModel().getModel());
        UnloadModelAnimation(e->getModel().getAnimation());
    }

    UnloadTexture(engine->bomb.getTexture());
    UnloadModel(engine->bomb.getModel());
    UnloadModelAnimation(engine->bomb.getAnimation());

    UnloadTexture(engine->fire.getTexture());
    UnloadModel(engine->fire.getModel());

    for (auto &e : engine->gameMap.getMapModels())
        UnloadModel(e.getModel());

    UnloadTexture(engine->gameMap.getBackGround().getTexture());
    UnloadModel(engine->gameMap.getBackGround().getModel());

    CloseAudioDevice();
    for (auto &music : engine->audio.getMusic())
        UnloadMusicStream(music.second);
    for (auto &sound : engine->audio.getSound())
        UnloadSound(sound.second);
}

int main(void)
{
    std::unique_ptr <RL::Window> window(new RL::Window(1920, 1080, "Indie studio", 60));
    std::unique_ptr <RL::Graphics> visual(new RL::Graphics());
    std::unique_ptr <Menu> menu(new Menu());
    std::unique_ptr <Engine> engine(new Engine());
    RL::Graphics::playVideo("assets/video/splash.mpg", 220);
    setImagesMenu(visual);
    setHud(visual);
    while (window->isOpen() && !window->getShouldClose()) {
        visual->clear();
        if (menu->getStatusPlay() == MENU)
            menu->displayMenu(visual);
        if (menu->getStatusPlay() == PREGAME)
            menu->displayPreGame(visual);
        if (menu->getStatusPlay() == GAME) {
            int ret = run(menu->getGameSettings(), visual, window, engine);
            menu->setSelector(MENU);
            menu->resetSelector();
            engine->isInGameOverMenu = false;
            window->setCursorState(false);
            if (ret == 1) {
                break;
            }
        }
    }
    unloadAll(engine);
    unLoadAllImages(visual);
    return 0;
}
