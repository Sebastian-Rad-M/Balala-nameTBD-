#include <iostream>
#include "GameManager.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
  #ifdef _WIN32
      SetConsoleOutputCP(CP_UTF8);
  #endif
  GameManager::instance().run();
  return 0;
}
