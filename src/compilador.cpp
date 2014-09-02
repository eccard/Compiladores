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
  ch= fin.get();
  while ( ch!= ' ' ) {
    token.info[cont]=ch;
    cont++;
    
    ch= fin.get();
    
  }

  return token;
}

int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;

  std::cout << getToken(fin).info << std::endl;

  return 0;
}
