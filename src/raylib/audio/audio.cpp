//
// Created by ilias on 03/06/2021.
//

#include "audio.h"

RL::Audio::Audio(float volume) {
    InitAudioDevice();
    SetMasterVolume(volume);
}

void RL::Audio::loadMusic(const std::string &file, const std::string &name) {
    this->musics[name] = LoadMusicStream(file.c_str());
}

void RL::Audio::playMusic(const std::string &soundName) {
    PlayMusicStream(this->musics[soundName]);
}

void RL::Audio::updateMusic(const std::string &musicName) {
    UpdateMusicStream(this->musics[musicName]);
}

void RL::Audio::loadSound(const std::string &file, const std::string &name) {
    this->sounds[name] = LoadSound(file.c_str());
}

void RL::Audio::playSound(const std::string &soundName) {
    PlaySound(this->sounds[soundName]);
}

std::map<std::string, Music> &RL::Audio::getMusic() {
    return this->musics;
}

std::map<std::string, Sound> &RL::Audio::getSound() {
    return this->sounds;
}
