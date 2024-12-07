#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include <SDL2/SDL_mixer.h>

#include <string>
class MusicPlayer {
 public:
  MusicPlayer();
  ~MusicPlayer();
  void destroy();
  void play(std::string musicPath, int loops);
  void setVolume(int volume);
};

#endif
