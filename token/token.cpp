#include "token.h"
#include <iostream>

void Token::print() {
  std::cout << "Token with value " << value << " with type " << (int)type
            << " with number value of " << number << std::endl;
}
