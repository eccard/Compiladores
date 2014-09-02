// "Copyright [year] <Copyright Owner>"
#include <iostream>
#include <fstream>

char getChar(std::ifstream & fin) {
  return fin.get();
}
int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;

  //ch = getChar(fin);
  // printf(" %c",ch);
  
  // getChar(fin);
  //  std::cout << getChar(fin) << std::endl;

  while (!fin.eof()) {
     std::cout << getChar(fin) << std::endl;
  }

  //  ch = getChar(fin);
//testando rafael
//codigo commite 4
  
  return 0;
}
