#include <cstdio>
#include <fstream>
#include <iostream>
#include <istream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include "http_client.h"
#include "gamestate.h"
#include "node.h"
#include "puzzle.h"

GameState::GameState(const char *path, const char *remote)  : mPath(path), mRemote(remote) {
  f.open(mPath, std::fstream::in | std::fstream::out | std::fstream::app);
  if (f.fail()) {
    std::cout << "can not open file " << path << std::endl;
  }
}

GameState::~GameState() {
  if (!f.fail()) f.close();
}

void GameState::LoadState() {
  nlohmann::json j;
  if (f.peek() == std::fstream::traits_type::eof()) {
    // request new game state from the server
    HTTPCLient hc;
    struct memory chunk;     
    hc.get(mRemote, &chunk);  
    j = nlohmann::json::parse(chunk.response);    
  } else {
    // load the state from the server
    std::ifstream f(mPath);
    j = nlohmann::json::parse(f);
  }
  
  std::cout << j["puzzle"]["seed"] << std::endl;
  
  
  // and load it aka deserialize.
}

void GameState::SaveState() {
  // write the json object to file aka serialize;
}
