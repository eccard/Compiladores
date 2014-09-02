// "Copyright [year] <Copyright Owner>"
#include <iostream>
#include <fstream>

typedef struct Token {
  char info[21];
  int linha;
  int classificacao;

}Token;

  
  
Token getToken(std::ifstream & fin) {
  Token token;
  
  char ch;
  int cont= 0;
  while ( ch=fin.get()  && ch!= ' ' ) {
    std::cout << ch << std::endl;
    token.info[cont]=ch;
    cont++;
  }

  return token;
}

int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;


  //  while (!fin.eof()) {
    //     std::cout << getChar(fin) << std::endl;
  Token token = getToken(fin);
  
  //std::cout << getToken(fin).linha << std::endl;

    //}

  return 0;
}
