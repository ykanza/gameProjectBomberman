//
// Created by ilias on 03/06/2021.
//

#ifndef BOMBERMAN_AUDIO_H
#define BOMBERMAN_AUDIO_H

#include <string>
#include <map>
#include "raylib.h"

namespace RL {
    class Audio {
    public:
        explicit Audio(float volume = 100);

        ~Audio() = default;

        void loadMusic(const std::string &file, const std::string &name);

        void playMusic(const std::string &musicName);

        void loadSound(const std::string &file, const std::string &name);

        void playSound(const std::string &soundName);

        void updateMusic(const std::string &name);

        std::map<std::string, Music> &getMusic();
        std::map<std::string, Sound> &getSound();

    private:
        std::map<std::string, Music> musics;
        std::map<std::string, Sound> sounds;
    };

}

#endif //BOMBERMAN_AUDIO_H
