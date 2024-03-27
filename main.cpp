#include "lib_src/entry_ems.hpp"
#include <iostream>

// int main(void) {
//   std::cout << "Loading Game of Life - Native" << std::endl;
//   return loop();
// };

int main(void) {
  std::cout << "Loading Game of Life - WASM" << std::endl;
  return loop();
};