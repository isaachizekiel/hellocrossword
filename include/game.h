
#include "gamestate.h"
class PuzzleGame {
public:
  PuzzleGame();
  ~PuzzleGame();
  
  void Start();
  
  void Stop();

private:
  GameState *mGameState;
};
