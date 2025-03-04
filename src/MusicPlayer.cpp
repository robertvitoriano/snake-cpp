#include "MusicPlayer.h"

#include <stdexcept>

MusicPlayer& MusicPlayer::getInstance() {
  static MusicPlayer instance;
  return instance;
}

MusicPlayer::MusicPlayer() : globalVolume(100) {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("SDL_mixer could not initialize! Error: " + std::string(Mix_GetError()));
  }
}

MusicPlayer::~MusicPlayer() { destroy(); }

void MusicPlayer::playMusic(const std::string& musicPath, int loops) {
  if (musicTracks.find(musicPath) == musicTracks.end()) {
    Mix_Music* music = Mix_LoadMUS(musicPath.c_str());
    if (!music) {
      throw std::runtime_error("Failed to load music! Error: " + std::string(Mix_GetError()));
    }
    musicTracks[musicPath] = music;
  }

  if (Mix_PlayMusic(musicTracks[musicPath], loops) == -1) {
    throw std::runtime_error("Failed to play music! Error: " + std::string(Mix_GetError()));
  }
  Mix_VolumeMusic(globalVolume);
}

void MusicPlayer::playSound(const std::string& soundPath, int loops) {
  if (soundEffects.find(soundPath) == soundEffects.end()) {
    Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());
    if (!sound) {
      throw std::runtime_error("Failed to load sound effect! Error: " + std::string(Mix_GetError()));
    }
    soundEffects[soundPath] = sound;
  }

  if (Mix_PlayChannel(-1, soundEffects[soundPath], loops) == -1) {
    throw std::runtime_error("Failed to play sound effect! Error: " + std::string(Mix_GetError()));
  }
  Mix_VolumeMusic(globalVolume);
}

void MusicPlayer::setVolume(int volume) {
  if (volume < 0) volume = 0;
  if (volume > 128) volume = 128;
  globalVolume = volume;
  Mix_VolumeMusic(globalVolume);
}

void MusicPlayer::destroy() {
  for (std::map<std::string, Mix_Music*>::iterator it = musicTracks.begin(); it != musicTracks.end(); ++it) {
    Mix_FreeMusic(it->second);
  }
  musicTracks.clear();

  for (std::map<std::string, Mix_Chunk*>::iterator it = soundEffects.begin(); it != soundEffects.end(); ++it) {
    Mix_FreeChunk(it->second);
  }
  soundEffects.clear();

  Mix_HaltMusic();
  Mix_CloseAudio();
}
