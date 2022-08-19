#ifndef KEY_H
#define KEY_H

#include <iostream>
class Key {
public:
  friend std::ostream &operator<<(std::ostream &out, const Key &key) {
    out << key.str << std::endl;
    return out;
  }

  const char *str;
};
#endif
