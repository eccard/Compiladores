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
<<<<<<< HEAD
//codigo commite 4
  
=======


  Testando lugao ta na escuta
>>>>>>> 8f85b6a63c3b0daa2272323a95a9b4752a9e9fe0
  return 0;
}
