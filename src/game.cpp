
#include "gamestate.h"
#include "key.h"
#include "node.h"
#include "game.h"

PuzzleGame::PuzzleGame() {
  std::cout << "Constructing Puzzle Game" << std::endl;  
  mGameState = new GameState("/home/izak/0.json", "https://bt251.com/0.json");
}

PuzzleGame::~PuzzleGame() {
  std::cout << "Distructing Puzzle Game" << std::endl;  
}

void PuzzleGame::Start() {
  // load state
  
}

void PuzzleGame::Stop() {
  // save state
}

int main() {
  PuzzleGame pg;
  pg.Start();
  bool quit = false;;
  char ch;
  while (!quit) {    
    std::cin>>ch;    
    switch (ch) {
    case 'q':
      pg.Stop();
      quit = true;
      break;
    }
  }  
  return 0;
}


int main_test() {
  
  Key *key0 = new Key();
  key0->str = "key0";

  Key *key1 = new Key();
  key1->str = "key1";


  LinkedList<Key *> keys;
  
  keys.addAtFront(key0);
  keys.addAtBack(key1);
  
  
  std::cout << keys << std::endl;;

  std::cout << keys.size() << std::endl;

  GameState gs("/home/izak/0.json", "https://www.bt251.com/0.json");

  gs.LoadState();
  
  return 0;
}
