#include <iostream>
#include <fstream>

typedef struct Token {
  char info[21];
  int col;
  int linha;
  int classificacao;

}Token;


  
Token getToken(std::ifstream & fin, int *linha) {
  Token token;
  token.col=0;
  for (int i=0; i < 21; i++) {
    token.info[i]= 0;  
  }

  
  char ch;
  char ch2;
  int cont= 0;
  ch= fin.get();

  if (ch == ';') {
    token.col++;
     std::cout<<token.col<<"sss"<<std::endl;
    token.info[0]= ch;
    return token;
  }
  if (ch == '=') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '<') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '>') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ')') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '(') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '[') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ']') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '!') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '+') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '-') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '*') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '/') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ',') {
    token.col++;
    token.info[0]= ch;
    return token;
  }
  while(ch == ' ' || ch == '\n') {
    if(ch == ' ' ){
      token.col++;
    }else{
      *linha=*linha+1;
      token.col=0;
    //  std::cout<<*linha<<std::endl;
    }
    ch= fin.get(); 
  }
  if (ch == ':'){
        token.info[0]=ch;
        ch= fin.get(); 
    
    if (ch == '='){
      token.info[1]= ch;
    return token;
    }
    fin.unget();
  return token;
  }
  
  
  
  while ( ch!= ' ' && fin.good()) {
    if ( ch!=';' && ch!='=' && ch!='<' && ch!=',' &&
     ch!='>' && ch!='(' && ch!=')' && ch!='[' && 
         ch!=']' && ch!='!' && ch!='+' && ch!='-' && 
         ch!='*' && ch!='/' && ch!=':' && ch!= '\n') {
       token.info[cont]=ch;
      cont++;
    }else {
      fin.unget();
      return token;
    } 
    ch= fin.get(); 
  }
  token.info[cont]='\0';
  token.linha= *linha;
  return token;
}


int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;
  int linha= 1;
  while (fin.good()) {
    std::cout << getToken(fin, &linha).info<< std::endl;
    //std::cout << getToken(fin, &linha).linha<< std::endl;
    std::cout << getToken(fin, &linha).col<< std::endl;
  }
  
  return 0;
}