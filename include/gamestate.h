#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "linkedlist.h"
#include "key.h"
#include "node.h"
#include "puzzle.h"

#include <nlohmann/json.hpp>
#include <fstream>

#define STATE_REMOTE_PATH "/home/izak/0.json"
#define STATE_LOCAL_PATH "https://www.bt251.com/0.json"

class GameState {
private:
  LinkedList<Puzzle *> mPuzzles;
  LinkedList<Key *> mKeys;
  
  nlohmann::json mJson;
  const char *mPath ;
  const char *mRemote;
  std::fstream f;

public:
  GameState(const char *path, const char *remote);
  ~GameState();

  void LoadState();
  void SaveState();

  static void http_request();
  // onStart, onStop
};

#endif
