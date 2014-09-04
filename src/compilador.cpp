#include <iostream>
#include <fstream>

typedef struct Token {
  char info[21];
  int linha;
  int classificacao;

}Token;


  
Token getToken(std::ifstream & fin, int *linha) {
  Token token;
  for (int i=0; i < 21; i++) {
    token.info[i]= 0;  
  }

  
  char ch;
  char ch2;
  int cont= 0;
  ch= fin.get();

  if (ch == ';') {
	  *linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '=') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '<') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '>') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ')') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '(') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '[') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ']') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '!') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '+') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '-') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '*') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '/') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == ',') {
	  linha++;
    token.info[0]= ch;
    return token;
  }
  if (ch == '\n') {
	  linha++;
    ch= fin.get(); 
  }
  if (ch == ' ') {
	  linha++;
    ch= fin.get(); 
  }
  if (ch == ':'){
   	    token.info[0]=ch;
	    cont++;
	    *linha++;
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
       
    if(ch == '='){
       fin.unget();
       return token;
      }

   
    ch= fin.get(); 
  }
  *linha++;
  
  token.info[cont]='\0';
  token.linha= *linha;
  return token;
}


int main() {
  std::ifstream fin("file.lug", std::fstream::in);
  char ch;
  int linha= 0;
  while (fin.good()) {
    std::cout << getToken(fin, &linha).info<< std::endl;
  }
  
  return 0;
}
