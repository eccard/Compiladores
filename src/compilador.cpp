#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

#define INICIADOR 1 //ok program
#define FUNCAO 2 //ok function
#define IDENTIFICADOR 3 //
#define CONSTANTE 4 //ok const
#define TIPO 5 //ok type
#define PVIRGULA 6 //ok ;
#define IGUAL 7 //ok =
#define VIRGULA 9 //ok ,
#define INTEIRO 10 //ok integer
#define REAL 11 //ok real
#define VETOR 12 //ok array
#define DE 13 //ok  of
#define INICIO 14 //ok begin
#define FIM 15 //ok end
#define SE 16 //ok if
#define ENTAO 17 //ok else
#define ESCREVER 18 //ok write
#define LER 19 //ok read
#define ENQUANTO 20 //ok while
#define ATRIBUIR 21 //ok :=
#define APARENTE 22 //ok (
#define FPARENTE 23 //ok )
#define MAIOR 24 //ok >
#define MENOR 25 //ok <
#define MAIS 26 //ok +
#define MENOS 27 //ok -
#define ASTERISCO 28 //ok *
#define BARRA 29 //ok /
#define PORCENTAGEM 30
#define EXCLAMACAO 31 //ok !
#define VARIAVEL 32 //ok var
#define ACOLCH 33 //ok [
#define FCOLCH 34 //ok ]
#define SENAO 35 //ok else
#define RESULTADO 36
#define ERRO 37 //ok
#define DOISPONTOS 38 //ok :
#define NUMERICO 39 //ok 2121

typedef struct Token {
    char info[21];
    int col;
    int linha;
    int tipo;
}Token;

int checkTipoToken(char token[21]){
    int x=0;
    int cont=0;
    int i=0;

    if(strcmp(token,"program")==0){ return INICIADOR; }
    if(strcmp(token,"var")==0){ return VARIAVEL; }
    if(strcmp(token,"function")==0){return FUNCAO;}
    if(strcmp(token,"type")==0){return TIPO;}
    if(strcmp(token,"begin")==0){return INICIO;}
    if(strcmp(token,"end")==0){return FIM;}
    if(strcmp(token,"write")==0){return ESCREVER;}
    if(strcmp(token,"read")==0){return LER;}
    if(strcmp(token,"while")==0){return ENQUANTO;}
    if(strcmp(token,"if")==0){return SE;}
    if(strcmp(token,"then")==0){return ENTAO;}
    if(strcmp(token,"integer")==0){return INTEIRO;}
    if(strcmp(token,"real")==0){return REAL;}
    if(strcmp(token,"array")==0){return VETOR;}
    if(strcmp(token,"else")==0){return SENAO;}
    if(strcmp(token,"of")==0){return DE;}
    if(strcmp(token,":=")==0){return ATRIBUIR;}
    if(strcmp(token,"const")==0){return CONSTANTE;}

    if(strcmp(token,";")==0){return PVIRGULA;}
    if(strcmp(token,":")==0){return DOISPONTOS;}
    if(strcmp(token,",")==0){return VIRGULA;}
    if(strcmp(token,"=")==0){return IGUAL;}
    if(strcmp(token,"(")==0){return APARENTE;}
    if(strcmp(token,")")==0){return FPARENTE;}
    if(strcmp(token,"[")==0){return ACOLCH;}
    if(strcmp(token,"]")==0){return FCOLCH;}

    if(strcmp(token,">")==0){return MAIOR;}
    if(strcmp(token,"<")==0){return MENOR;}
    if(strcmp(token,"!")==0){return EXCLAMACAO;}


    if(strcmp(token,"+")==0){return MAIS;}
    if(strcmp(token,"-")==0){return MENOS;}
    if(strcmp(token,"*")==0){return ASTERISCO;}
    if(strcmp(token,"/")==0){return BARRA;}


    x=strlen(token);


    for(i=0; i < x ; i++){
        switch(token[i]){
        case '@':
            return ERRO;
            break;
        case '#':
            return ERRO;
            break;
        case '$':
            return ERRO;
            break;
        case '%':
            return ERRO;
            break;
        case 'š':
            return ERRO;
            break;
        case '¬':
            return ERRO;
            break;
        case '&':
            return ERRO;
            break;
        case '`':
            return ERRO;
            break;
        case 'Ž':
            return ERRO;
            break;
        case 'ª':
            return ERRO;
            break;
        case 'º':
            return ERRO;
            break;
        case '§':
            return ERRO;
            break;
        case '|':
            return ERRO;
            break;
        case '°':
            return ERRO;
            break;
        case '~':
            return ERRO;
            break;
        case '^':
            return ERRO;
            break;

        }
    }

    for(i=0; i < x ; i++){

        if(token[i] >= '0' && token[i] <= '9' || (token[i] == '.')){
            cont++;
        }
    }
    if(cont==x){
        return NUMERICO;
    }

    if(token[0] >= '0' && token[0] <= '9' ){
        return ERRO;
    }

    // caso o algotmo chegue até esse ponto quer dizer que
    // token é um identificador
    return IDENTIFICADOR;


}

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
        tk->tipo=checkTipoToken(tk->info);
        std::cout << tk->info << " " << tk->linha << " " << tk->col << " "<< tk->tipo <<std::endl;
    }
    return 0;
}
