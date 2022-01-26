//
// Created by Matt Miller on 1/25/22.
//

#ifndef SDL2TEST_AUDIO_PLAYER_H
#define SDL2TEST_AUDIO_PLAYER_H

#include <string>
#include <memory>
#include "SDL.h"
#include "SDL_mixer.h"

class audio_sample {
public:
    audio_sample(const std::string &path, int volume);
    void play();
    void play(int times);
    void set_volume(int volume);

private:
    std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk *)> chunk;
};

#endif //SDL2TEST_AUDIO_PLAYER_H
