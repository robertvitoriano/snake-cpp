#include "MusicPlayer.h"

#include <stdexcept>

MusicPlayer::MusicPlayer() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("SDL_mixer could not initialize! Error: " + std::string(Mix_GetError()));
  }
}

MusicPlayer::~MusicPlayer() { destroy(); }

void MusicPlayer::play(std::string musicPath, int loops) {
  Mix_Music *music = Mix_LoadMUS(musicPath.c_str());
  if (!music) {
    throw std::runtime_error("Failed to load background music! Error: " + std::string(Mix_GetError()));
  }

  if (Mix_PlayMusic(music, loops) == -1) {
    throw std::runtime_error("Failed to play background music! Error: " + std::string(Mix_GetError()));
  }
  Mix_VolumeMusic(64);
}

void MusicPlayer::setVolume(int volume) {
  if (volume < 0) volume = 0;
  if (volume > 128) volume = 128;
  Mix_VolumeMusic(volume);
}

void MusicPlayer::destroy() {
  Mix_HaltMusic();
  Mix_CloseAudio();
}
