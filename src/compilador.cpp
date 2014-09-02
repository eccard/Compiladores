#include <iostream>
#include <fstream>

char getChar(std::ifstream & fin) {
  return 'C';  
}

int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;

  while (!fin.eof()) {
     std::cout << getChar(fin) << std::endl;
  }

  return 0;
}
