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

typedef struct No{
    Token token;
    struct No* filho;
    struct No* prox;
}No;

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
         ch==',' || ch=='#' || ch=='$' || ch=='%' ||
         ch=='@' || ch=='š' || ch=='¬' || ch=='&' ||
         ch=='`' || ch=='Ž' || ch=='ª' || ch=='º' ||
         ch=='§' || ch=='|' || ch=='°' || ch=='~' ||
         ch=='^'){
        *col=*col+1;
        token.col++;
        token.info[0]= ch;
        token.tipo=checkTipoToken(token.info);
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
        token.tipo=checkTipoToken(token.info);
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
        token.tipo=checkTipoToken(token.info);
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
            token.tipo=checkTipoToken(token.info);
            return token;
        }
        fin.unget();
        token.tipo=checkTipoToken(token.info);
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
            token.tipo=checkTipoToken(token.info);
            return token;
        }
        ch= fin.get();
    }
    token.info[cont]='\0';
    token.tipo=checkTipoToken(token.info);
    return token;
}

// funções do sintatico
void imprimirLista(No * l){
    No * r=l;
    while(r!=NULL){
        std::cout<< r->token.info <<std::endl;
        std::cout<< r->token.linha <<std::endl;
        std::cout<< r->token.tipo<<std::endl;
        r=r->prox;
    }
}
int altura(No *a)
{
    int x =0 ,y =0;
    if(a==NULL)
    {
               return 0;
    }
    else
    {
               x=altura(a->filho)+1;
               y=altura(a->prox); // aki pode estar acontecendo um problema
               if(x>y)
               {
                      return x;
               }
               else
               {
                      return y;
               }
    }
}
void imprimenotacao(No *a)
{
     std::cout <<"("<< std::ends;
     if(a==NULL)
     {
     std::cout <<"-1)"<< std::ends;
     }
     if(a!=NULL)
     {
                std::cout <<a->token.info<< std::ends;
                imprimenotacao(a->prox);
                printf(")");
                imprimenotacao(a->prox);
     }
}


void imprimeNivel(No *a,int n)
{
       if(a!=NULL)
       {
                  if(n==0)
                  {
                          fflush(stdout);
                          printf("%s ",a->token.info);
                          imprimeNivel(a->prox,n);
                  }
                  else
                  {
                          imprimeNivel(a->filho,n-1);
                          imprimeNivel(a->prox,n);
                  }
       }
}

void imprimeLargura(No *a)
{
     int h=3;//altura(a);
     int i;

     for(i=0;i<h;i++)
     {
                     imprimeNivel(a,i);
                     fflush(stdout);
                     printf("\n");
     }
}

No * insereLista(No * l,Token token){
    No * r=l;
    No * t=NULL;

    if(l==NULL){
        l=(No*)malloc(sizeof(No));
        l->token= token;
        l->prox=NULL;
        l->filho=NULL;

        return l;
    }
    else{
        while(r->prox!=NULL){
            r=r->prox;
        }

        t=(No*)malloc(sizeof(No));
        t->token=token;
        t->prox=NULL;
        t->filho=NULL;
        r->prox = t;
        return l;
    }
}

No * corpo(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col)
{
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CORPO>");
    tk=getToken(fin, linha,col);
    if(tk.tipo == VARIAVEL || tk.tipo == CONSTANTE || tk.tipo == TIPO ||   tk.tipo == FUNCAO ){

        larv->filho=declaracoes();
        printf(">> %s <<", t->token);
        larv->filho->prox=bloco();
        printf(">> %s <<", t->token);
        return larv;
    }
    else if(tk.tipo == INICIO){
        larv->filho=bloco();
        return larv;
    }
    else{
           std::cout << "inicio nao encontrado" <<std::endl;
            return NULL;
    }

}
//No* identificador(std::ifstream & fin,Token tk,int *linha,int *col){
No* identificador(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col){
    No *larv=(No*)malloc(sizeof(No));
    tk=getToken(fin, linha,col);
     if(tk.tipo==IDENTIFICADOR){
        strcpy(larv->token.info,"<IDENTIFICADOR>");
        larv->filho=insereLista(larv->filho,tk);
        return larv;
     }else{
         std::cout <<"identificador não encontrado" <<std::endl;
         return NULL;
     }
}


No* sintatico(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col){
    No * arv= NULL;
    strcpy(tkn.info,"<PROGRAMA>");

    arv=insereLista(arv,tkn); //cabeça da regra
    tk=getToken(fin, linha,col);
//    std::cout<< tk.info <<std::endl;

    if(tk.tipo==INICIADOR){
        arv->filho=insereLista(arv->filho,tk);
        arv->filho->prox=identificador(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col);
        if(tk.tipo==PVIRGULA){
            arv->filho->prox->prox=insereLista(arv->filho->prox->prox,tk);
//            arv->filho->prox->prox->prox=corpo();
            return arv;
        }else{
            std::cout<< "; não encontrado"<<std::endl;
            return NULL;
        }
    }else{
            std::cout<< "iniciador não encontrado"<<std::endl;
            return NULL;
    }
}


int main() {
    std::ifstream fin("file.lug", std::fstream::in);
//    std::ifstream fin("file2.lug", std::fstream::in);
    int linha= 1;
    int coluna=1;

//    Token *tk=(Token*)malloc(sizeof(Token));
    Token tk,tkn;
    tkn.linha=-1;
    tkn.col=-1;
    tkn.tipo=-1;
//    No *arv=(No*)malloc(sizeof(No));
     No *arv=NULL;

//    while (fin.good()) {
//        *tk=getToken(fin, &linha,&coluna);
//        std::cout << tk->info << " " << tk->linha << " " << tk->col << " "<< tk->tipo <<std::endl;
    arv=sintatico(fin,tk,tkn, &linha,&coluna);
    imprimeLargura(arv);
//    }

    return 0;
}
