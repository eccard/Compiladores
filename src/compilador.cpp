#include <stdlib.h>
#include <iostream>
#include <fstream>

typedef struct Token {
    char info[21];
    int col;
    int linha;
    int classificacao;

}Token;



Token getToken(std::ifstream & fin, int *linha,int *col) {
    Token token;
    token.col=*col;
    token.linha=*linha;

    for (int i=0; i < 21; i++) {
        token.info[i]= 0;
    }


    char ch;
    int cont= 0;
    ch= fin.get();
    if ( ch=='=' || ch=='<' || ch=='<' || ch=='>' ||
         ch=='(' || ch=='[' || ch==']' || ch=='!' ||
         ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
         ch==',' ){
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == ';') {
        token.col++;
        token.info[0]= ch;

        ch= fin.get();
        if (ch== '\n'){
            *linha=*linha+1;
            *col=0;
        }
        fin.unget();

        return token;
    }
    if (ch == ')') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;

        ch= fin.get();
        if (ch== '\n'){
            *linha=*linha+1;
            *col=0;
        }
        fin.unget();

        return token;
    }

    if (ch == ':'){
        *col=*col+1;
        token.col++;
        token.info[0]=ch;
        ch= fin.get();

        if (ch == '='){
            token.col++;
            token.info[1]= ch;
            return token;
        }
        fin.unget();
        return token;
    }



    while(ch == ' ' || ch == '\n') {
        ch= fin.get();
    }


    while ( ch!= ' ' && fin.good()) {

        if ( ch!=';' && ch!='=' && ch!='<' && ch!=',' &&
             ch!='>' && ch!='(' && ch!=')' && ch!='[' &&
             ch!=']' && ch!='!' && ch!='+' && ch!='-' &&
             ch!='*' && ch!='/' && ch!=':' && ch!= '\n') {
            token.info[cont]=ch;
            cont++;
        }else {
            if (ch== '\n'){
                *linha=*linha+1;
                *col=0;
            }


            fin.unget();
            *col=*col+1;
            token.col=*col;
            return token;
        }
        ch= fin.get();
    }
    token.info[cont]='\0';
    return token;
}


int main() {
    std::ifstream fin("file.lug", std::fstream::in);
    char ch;
    int linha= 1;
    int coluna=1;

    Token *tk=(Token*)malloc(sizeof(Token));

    while (fin.good()) {
        *tk=getToken(fin, &linha,&coluna);
        std::cout << tk->info << " " << tk->linha << " " << tk->col <<std::endl;
    }
    return 0;
}
