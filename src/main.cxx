// "Copyright [year] <Copyright Owner>"
#include <iostream>
#include <fstream>

char getChar(std::ifstream & fin) {
  return 'C';
  
  // faguin_28 picagrroooooooooossa
  
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
  // teste acertando erros

  return 0;
}
