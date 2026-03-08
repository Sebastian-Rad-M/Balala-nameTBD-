#include <iostream>
#include "GameManager.h"
 #include <ctime>
#include <cstdlib>


int main() {

  srand(static_cast<unsigned int>(time(nullptr)));
  GameManager::instance().run();
  return 0;
}
