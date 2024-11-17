#include "MusicPlayer.h"

#include <stdexcept>

MusicPlayer::MusicPlayer() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("SDL_mixer could not initialize! Error: " + std::string(Mix_GetError()));
  }
}

MusicPlayer::~MusicPlayer() { destroy(); }

void MusicPlayer::play(const std::string musicPath) {
  Mix_Music *backgroundMusic = Mix_LoadMUS(musicPath.c_str());
  if (!backgroundMusic) {
    throw std::runtime_error("Failed to load background music! Error: " + std::string(Mix_GetError()));
  }

  if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
    throw std::runtime_error("Failed to play background music! Error: " + std::string(Mix_GetError()));
  }
}

void MusicPlayer::destroy() {
  Mix_HaltMusic();
  Mix_CloseAudio();
}
