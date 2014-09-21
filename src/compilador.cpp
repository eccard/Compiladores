#include <iostream>
#include <fstream>
#include <cstdlib>

//estrutura do token
typedef struct Token {
  char info[21];
  int col;
  int linha;
  int classificacao;

}Token;


  
Token getToken(std::ifstream & fin, int *linha,int *coluna) {
  Token token;
  for (int i=0; i < 21; i++) {
    token.info[i]= 0;  
  }


  char ch;
  char ch2;
  int cont= 0;
  ch= fin.get();

  // if (ch == ';') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '=') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '<') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '>') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == ')') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '(') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '[') {
  //   *coluna=*coluna+1;
  //   token.col= *coluna;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == ']') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '!') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '+') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '-') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '*') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == '/') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }
  // if (ch == ',') {
  //   token.col++;
  //   token.info[0]= ch;
  //   return token;
  // }

  if ( ch==';' || ch=='=' || ch=='<' || ch==',' ||
       ch=='>' || ch=='(' || ch==')' || ch=='[' || 
       ch==']' || ch=='!' || ch=='+' || ch=='-' || 
       ch=='*' || ch=='/'){
    
    *coluna=*coluna+1;
     token.col= *coluna;
     token.col++;
     token.info[0]= ch;
     return token;
  }
  while(ch == ' ' || ch == '\n') {
    if(ch == ' ' ){
      *coluna=*coluna+1;
     token.col= *coluna;
    }else{
      *linha=*linha+1;
      *coluna=0;
    //  std::cout<<*linha<<std::endl;
    }
    ch= fin.get(); 
  }
  if (ch == ':'){
     *coluna=*coluna+1;
     token.col= *coluna;
     token.info[0]=ch;
     ch= fin.get(); 
    
    if (ch == '='){
      *coluna=*coluna+1;
      token.col= *coluna;
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
       *coluna=*coluna+1;
        token.col= *coluna;
      cont++;
    }else {
      fin.unget();
      return token;
    } 
    ch= fin.get(); 
  }
  token.info[cont]='\0';
  token.linha= *linha;
  std::cout <<token.col<< std::endl;
  return token;
}


int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;
  int linha= 1;
  int coluna= 1;

  Token *tk=(Token*)malloc(sizeof(Token));
  while (fin.good()) {
    *tk=getToken(fin, &linha,&coluna);
    std::cout << tk->info << " " << tk->linha << " " << tk->col << std::endl;
  }
  
  return 0;
}