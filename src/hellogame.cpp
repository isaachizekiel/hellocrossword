#include <cstdio>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <thread>
#include <cstring>
#include <fstream>
#include <nlohmann/json.hpp>

#define GAME_STATE_PATH "/home/izak/gamestate.json"

template <typename T> 
struct Node {
  T *item;
  Node *next;
};

struct PuzzleNode {
  const char *str;
  bool isFound = false;
  PuzzleNode *next;
};

struct LevelPass {
  const char *password;
  LevelPass *next;
};

struct User {
  int bonus, level;
};

struct GameStateX {
  PuzzleNode *puzzleList;
  LevelPass *levelPass;
  User user;
};


/*
  game state  
  {
  "puzzle": {
  "seed": "s",
  "words": [],
  "solved": 0
  },
  "key": {
  "seed": "s",
  "words": []
  },
  "bonus": 0,
  "level": 0
  }
 */

void serialize(GameStateX *state, const char *filename) {
#if 0
  GameStateX *gamestateX = state;
  PuzzleNode *puzzleNode = gamestateX->puzzleList;
  LevelPass *levelPass = gamestateX->levelPass;

  int i = 0; // words counter
  const char *words[16];
  
  // initialize the words list
  while (puzzleNode != nullptr) {
    words[i++] = puzzleNode->str;
    puzzleNode = puzzleNode->next;
  }

  nlohmann::json p;
  p["s"] = words[0];
  p["words"] = *(words)+1; // shifting the array by one element

  std::cout<<p;
    
  while (levelPass != nullptr) {
    levelPass = levelPass->next;
  }
#endif
  
}

void deserialize(GameStateX *state, const char *filename) {
  }


static Node<struct T> *create_node(Node<struct T> *n) {
  n->next = nullptr;
  return n;
}

static PuzzleNode* create_puzzle_node(const char *str) {
  PuzzleNode *p = new PuzzleNode;
  p->str = str;
  p->next = nullptr;
  return p;
}

static void insert_puzzle_node(PuzzleNode *head, PuzzleNode *p) {
  if (head == nullptr) {
    p->next = nullptr;
  }

  while(head->next != nullptr) head = head->next;

  head->next = p;
  p->next = nullptr; 
    
}

static void display_puzzle_node(PuzzleNode *head) {  
  while (head != nullptr) {
    printf("%s is found: %d\n", head->str, head->isFound);
    head = head->next;
  }  
}

// the game has two states
// the first state is all puzzel answers are found, (game finish)
// the second state is not all puzzels are solved
enum GameState {FOUND, NOT_FOUND};

class PuzzleGame {  
  GameState state;
  std::string answer;
  bool quit;
  PuzzleNode *puzzleNode;
  GameStateX *mGameState;
  nlohmann::json mStateJson;

  void GiveBonus() {
    printf("giving bonus");
  }
  
  void NextLevel() {
    // load the nextlevel
  }

  bool CheckAnser() {
    while (puzzleNode != nullptr) {
      printf("checking %s with %s\n", answer.c_str(), puzzleNode->str);
      if (0 == strcmp(puzzleNode->str, answer.c_str()) && !puzzleNode->isFound) {
	puzzleNode->isFound = true;
	return true;
      }
   
      puzzleNode = puzzleNode->next;
    }

    return false;
  }

  // theis function will be replaced with LoadState()
  void Init() {
    const char *data[4] = {"fruit0", "fruit1", "fruit2", "fruit3"};  
    puzzleNode = create_puzzle_node("seed");
    PuzzleNode *element;

    for (int i = 0; i < 4; i++) {
      element = create_puzzle_node(data[i]);
      insert_puzzle_node(puzzleNode, element);
    }
    
  }
  
  void Stop() {
    printf("stopping the game...\n");
    quit = true;
  }

  bool LoadState() {
    std::fstream f;
    f.open(GAME_STATE_PATH, std::fstream::in | std::fstream::out | std::fstream::app);
    if (f.fail()) {
      printf("failed to open %s\n", GAME_STATE_PATH);
      return false;
    }

    if (f.peek() == std::fstream::traits_type::eof()) {
      GameStateX *gs = new GameStateX;
      PuzzleNode *pn = new PuzzleNode;
      LevelPass *lp = new LevelPass;
      User usr = User();


      usr.bonus = 0;
      usr.level = 0;
      
      gs->puzzleList = pn;
      gs->levelPass = lp;
      gs->user = usr;

    }
    
    mStateJson = nlohmann::json::parse(f);
    std::cout << mStateJson;

    return true;
  }

  void SaveState() {
    serialize(mGameState, GAME_STATE_PATH);
  }

public:
  PuzzleGame() {
    printf("constructing the game...\n");
    quit = false;
    state = NOT_FOUND;
    mGameState = new GameStateX;
    Init();
    LoadState();    
  }

  ~PuzzleGame() {
    printf("distructing the game...\n");
  }
  
  void Run() {
    display_puzzle_node(puzzleNode);

    while (!quit) {      
      switch (state) {	
      case FOUND:
	GiveBonus();
	NextLevel();	
	break;
      case NOT_FOUND:
	std::cin >> answer;
	if (answer == "e" || answer == "q") {
	  Stop();
	  break;
	}
	if(CheckAnser()) SaveState();
	break;	  
      }

    }
    
  }
  
};

int main() {
  PuzzleGame pg;
  pg.Run();
  return 0;
}
