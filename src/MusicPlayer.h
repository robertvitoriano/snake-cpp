#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include <SDL2/SDL_mixer.h>

class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void destroy();
  void play(const std::string musicPath);
};

#endif
