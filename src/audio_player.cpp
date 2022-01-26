//
// Created by Matt Miller on 1/25/22.
//

#include "audio_player.h"
#include <iostream>

audio_sample::audio_sample(const std::string &path, int volume) : chunk(Mix_LoadWAV(path.c_str()), Mix_FreeChunk) {
    if (!chunk.get()) {
        std::cout << "Could not load audio sample: " << path << std::endl;
    }
    Mix_VolumeChunk(chunk.get(), volume);
}

void audio_sample::play() {
    Mix_PlayChannel(-1, chunk.get(), 0);
}

void audio_sample::play(int times) {
    Mix_PlayChannel(-1, chunk.get(), times - 1);
}

void audio_sample::set_volume(int volume) {
    Mix_VolumeChunk(chunk.get(), volume);
}