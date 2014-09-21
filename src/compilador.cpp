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
//    char ch2;
    int cont= 0;
    ch= fin.get();

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
    if (ch == '=') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '<') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '>') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
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
    if (ch == '(') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '[') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == ']') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '!') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '+') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '-') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '*') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == '/') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }
    if (ch == ',') {
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        return token;
    }

    //    while(ch == ' ' || ch == '\n') {
    //        if(ch == ' ' ){
    ////            token.col++;
    //        }else{
    //            *linha=*linha+1;
    //            *col=0;
    //            //  std::cout<<*linha<<std::endl;
    //        }
    //        ch= fin.get();
    //    }



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
//                if (ch== '\n'){
//                    *linha=*linha+1;
//                    *col=0;
//                }
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
    //    std::cout << "paaaaaaaaaaaaaaaaaaa cont->" << cont<<std::endl;

    token.info[cont]='\0';
    //    token.linha= *linha;
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
