#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>

class Puzzle {
public:
  friend std::ostream &operator<<(std::ostream &out, const Puzzle &puzzle) {
    out << puzzle.str << std::endl;
    out << puzzle.isSolved << std::endl;
    return out;
  }

  const char *str;
  bool isSolved;
};


#endif
