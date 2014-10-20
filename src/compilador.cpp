#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include<QtGui/QApplication>
#include "Arvore.h"
#include "constants.h"
#include "simbolo.h"
#include <string>

//No* op_logico(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col);
No* exp_logica(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* op_matematico(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col);
No* exp_matematica(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* parametro(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* nome_numero(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No * funcao(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* indice(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
//No* expressao_logica(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col);

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

int QNTNOGLOB=0;
std::vector<Simbolo> smbs;
//typedef struct Token {
//    char info[21];
//    int col;
//    int linha;
//    int tipo;
//}Token;

//typedef struct No{
//    Token token;
//    struct No* filho;
//    struct No* prox;
//}No;

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
//        case 'š':
//            return ERRO;
//            break;
//        case '¬':
//            return ERRO;
//            break;
        case '&':
            return ERRO;
            break;
        case '`':
            return ERRO;
            break;
//        case 'Ž':
//            return ERRO;
//            break;
//        case 'ª':
//            return ERRO;
//            break;
//        case 'º':
//            return ERRO;
//            break;
//        case '§':
//            return ERRO;
//            break;
        case '|':
            return ERRO;
            break;
//        case '°':
//            return ERRO;
//            break;
        case '~':
            return ERRO;
            break;
        case '^':
            return ERRO;
            break;

        }
    }

    for(i=0; i < x ; i++){

        if((token[i] >= '0') && (token[i] <= '9') || (token[i] == '.')){
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
    if(ch==' '){
//        std::cout << " pegou o espaço "<< std::endl;
        ch= fin.get();
    }
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
    int h=10;//altura(a);
    int i;

    for(i=0;i<h;i++)
    {
        imprimeNivel(a,i);
        fflush(stdout);
        printf("\n");
    }
}
void impprimeGen(No *a){
    No* p;
    std::cout << a->token.info <<" "<< a->num<<std::endl;
    for (p=a->filho; p!=NULL; p=p->prox)
    impprimeGen(p);
}

int contarNos(No *a){
    if(a==NULL) return 0;
    else
        return 1+ contarNos(a->filho) + contarNos(a->prox);

}
void setarNumNos(No *a){
    if(a->prox!=NULL){
        a->prox->num=1+QNTNOGLOB;
        QNTNOGLOB++;
        setarNumNos(a->prox);
    }
    if(a->filho!=NULL){
        a->filho->num=1+QNTNOGLOB;
        QNTNOGLOB++;
        setarNumNos(a->filho);
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


No* identificador(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col);

No * const_valor(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONST_VALOR>");
    tk=getToken(fin, linha,col);

    if(tk.tipo==IDENTIFICADOR){  // o que ele diz de sequencia alfanumerica
        larv->filho=insereLista(larv->filho,tk);
        return larv;
    }
    else{
        larv->filho=nome_numero(fin,tk,tkn,linha,col);
        larv->filho->prox=exp_matematica(fin,tk,tkn,linha,col);
        return larv;
    }

    return larv;
}
No* constante(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);

No* constantes(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONSTANTES> ");

    tk=getToken(fin, linha,col);
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=constante(fin,tk,tkn,linha,col);

        tk=getToken(fin, linha,col);
        if (tk.tipo==PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            larv->filho->prox->prox=constantes(fin,tk,tkn,linha,col);

            return larv;

        }else{
            std::cout<< "erro na variaveis, falta ;" <<std::endl;
            return NULL;
        }

    }
    else{
        return larv;
    }
}

No* constante(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONSTANTE>");
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=identificador(fin,tk,tkn,linha,col);

         tk=getToken(fin, linha,col);
        if(tk.tipo==IGUAL){

            larv->filho->prox= insereLista(larv->filho->prox,tk);
            larv->filho->prox->prox=const_valor(fin,tk,tkn,linha,col);
            return larv;
        }
        else{
            std::cout<< "erro em <CONSTANTE>, falta =" <<std::endl;
            return larv;
        }
    }
    else{
        std::cout<< "Erro em <CONSTANTE>identificador não encontrado"<<std::endl;
        return larv;
    }

}
No* numero(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NUMERO>");
    if(tk.tipo==NUMERICO){
        larv->filho=insereLista(larv->filho,tk);
        std::cout<< "pappa "<< tk.info<< " "<<tk.linha<<std::endl;
            tk=getToken(fin, linha,col); //acabei de comentar ... ver isso
        return larv;
    }
    else{
        std::cout<< " número não encontrado" << std::endl;
        return NULL;
    }

}

No* tipo_dado(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPO_DADO>");
    if(tk.tipo==REAL || tk.tipo==INTEIRO ){
        larv->filho=insereLista(larv->filho,tk);
        return larv;
    }
    if(tk.tipo == VETOR){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo == ACOLCH){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col); // acabei de colocar pra tirar o problema de numero
            larv->filho->prox->prox=numero(fin,tk,tkn,linha,col);
            if(tk.tipo == FCOLCH){
                larv->filho->prox->prox->prox=insereLista(larv->filho->prox->prox->prox,tk);
                tk=getToken(fin, linha,col);
                if(tk.tipo == DE){
                larv->filho->prox->prox->prox->prox=insereLista(larv->filho->prox->prox->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox->prox->prox=tipo_dado(fin,tk,tkn,linha,col);
                return larv;
                }


            }

        }
    }
    else{
        if(tk.tipo==IDENTIFICADOR){
            larv->filho=identificador(fin,tk,tkn,linha,col);
            return larv;
        }
        else{
            std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }
    }

}

No* lista_id(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<LISTA_ID>");

    if(tk.tipo==VIRGULA){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo==IDENTIFICADOR){
        larv->filho->prox=identificador(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col);
            larv->filho->prox->prox=lista_id(fin,tk,tkn,linha,col);
            return larv;
    }else{
            std::cout<< "identificador não encontrado em lista_id"<<std::endl;
            return NULL;
        }

    }
    else return larv;
}
No * variavel(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No * variaveis(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VARIAVEIS> ");

    tk=getToken(fin, linha,col);
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=variavel(fin,tk,tkn,linha,col);

        tk=getToken(fin, linha,col);
        if (tk.tipo==PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            larv->filho->prox->prox=variaveis(fin,tk,tkn,linha,col);
            return larv;

        }else{
            std::cout<< "erro na variaveis, falta ;" <<std::endl;
            return larv;
        }

    }else{
        return larv;
    }
}

No* variavel(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VARIAVEL>");
    //    tk=getToken(fin, linha,col);
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=identificador(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col);
        larv->filho->prox = lista_id(fin,tk,tkn,linha,col);

        if(tk.tipo==DOISPONTOS){
            larv->filho->prox->prox= insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox->prox=tipo_dado(fin,tk,tkn,linha,col);
            return larv;
        }

    }
    else{
        std::cout<< "identificador não encontrado"<<std::endl;
        return NULL;
    }
}
No* tipo(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No * tipos(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPOS> ");

    tk=getToken(fin, linha,col);
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=tipo(fin,tk,tkn,linha,col);

        tk=getToken(fin, linha,col);
        if (tk.tipo==PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            larv->filho->prox->prox=tipos(fin,tk,tkn,linha,col);

            return larv;

        }else{
            std::cout<< "erro na variaveis, falta ;" <<std::endl;
            return larv;
        }

    }else{
        return larv;
    }
}
No* tipo(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPO>");
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=identificador(fin,tk,tkn,linha,col);
         tk=getToken(fin, linha,col);
        if(tk.tipo==IGUAL){
            larv->filho->prox= insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=tipo_dado(fin,tk,tkn,linha,col);

            return larv;
        }
        else{
            std::cout<< "erro em <TIPO>, falta =" <<std::endl;
            return larv;
        }
    }
    else{
        std::cout<< "Erro em <CONSTANTE>identificador não encontrado"<<std::endl;
        return larv;
    }

}
No * nome_funcao(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME_FUNCAO>");


    larv->filho=tipo_dado(fin,tk,tkn,linha,col);
    tk=getToken(fin,linha,col); //tirando pra pear antes
    if(tk.tipo==IDENTIFICADOR){
        larv->filho->prox=identificador(fin,tk,tkn,linha,col);
        tk=getToken(fin,linha,col);
        if(tk.tipo==APARENTE){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            larv->filho->prox->prox->prox=variaveis(fin,tk,tkn,linha,col);
            if(tk.tipo==FPARENTE){
                larv->filho->prox->prox->prox=insereLista(larv->filho->prox->prox->prox,tk);
                return larv;
            }
        }
    }
    return larv;
}
No* bloco(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* senao(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<SENAO> ");
    tkn=tk;
    tk=getToken(fin, linha,col);
    if(tk.tipo==SENAO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=bloco(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        tk=tkn;
        return larv;
    }
}
No* op_logico(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<OP_LOGICO> ");
    larv->filho=insereLista(larv->filho,tk);
    return larv;
}

No* exp_logica_2(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_LOGICA_2> ");
    if((tk.tipo==MAIOR) || (tk.tipo==MENOR) ||(tk.tipo==IGUAL) ||(tk.tipo==EXCLAMACAO) ){
        larv->filho=op_logico(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col); // test
        larv->filho->prox=exp_logica(fin,tk,tkn,linha,col);
        return larv;
    }
    else {
        return larv;
    }
}
No* op_matematico(std::ifstream & fin,Token tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<OP_MATEMATICO> ");
    larv->filho=insereLista(larv->filho,tk);
    return larv;
}

No* exp_matematica_2(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_MATEMATiCA_2> ");
    if((tk.tipo==MAIS) || (tk.tipo==MENOS) ||(tk.tipo==ASTERISCO) ||(tk.tipo==BARRA) ){
        larv->filho=op_matematico(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col); // test
        larv->filho->prox=exp_matematica(fin,tk,tkn,linha,col);
        return larv;
    }else{
        return larv;
    }
}



No* exp_matematica(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_MATEMATICA> ");
     if((tk.tipo==MAIS) || (tk.tipo==MENOS) ||(tk.tipo==ASTERISCO) ||(tk.tipo==BARRA) ){
        larv->filho=op_matematico(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col);
        larv->filho->prox=nome_numero(fin,tk,tkn,linha,col);
        larv->filho->prox->prox=exp_matematica(fin,tk,tkn,linha,col);
        return larv;
    }
    else
        return larv;
}

No* exp_logica(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_LOGICA> ");
    larv->filho=nome_numero(fin,tk,tkn,linha,col);
    larv->filho->prox= exp_matematica(fin,tk,tkn,linha,col);
    larv->filho->prox->prox = exp_logica_2(fin,tk,tkn,linha,col);
    return larv;
}


No* lista_param(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<LISTA_PARAM>");
        if(tk.tipo==VIRGULA){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=parametro(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        return larv;
    }
}

No* nome_numero(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);

No* parametro(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<PARAMETRO>");

    larv->filho=nome_numero(fin,tk,tkn,linha,col);
    larv->filho->prox=lista_param(fin,tk,tkn,linha,col);
    return larv;

}

No* parametros(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<PARAMETROS>");
    tk=getToken(fin, linha,col);
    if(tk.tipo==APARENTE){
        larv->filho=insereLista(larv->filho,tk);
        larv->filho->prox=parametro(fin,tk,tkn,linha,col);
        if(tk.tipo==FPARENTE){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            return larv;
        }
        else{
            std::cout<<" erro <PARAMETROS>  faltou )"<< std::endl;
     return larv;
        }
    }
    else{
        std::cout<<" erro <PARAMETROS>  faltou ("<< std::endl;
        return larv;
    }
}
No* valor_2(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VALOR_2>");
    tk=getToken(fin, linha,col);

    if(tk.tipo==APARENTE){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=parametro(fin,tk,tkn,linha,col);
        if(tk.tipo==FPARENTE){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            return larv;
        }
        else{
            std::cout<<"erro em valor_2, FALTOU fechar colchetes  )"<<std::endl;
            return larv;

        }
    }
    else {
        larv->filho=indice(fin,tk,tkn,linha,col);

        larv->filho->prox=exp_matematica(fin,tk,tkn,linha,col);
        return larv;
    }
}

No* valor(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VALOR>");
    tk=getToken(fin, linha,col);
    if(tk.tipo==IDENTIFICADOR){
        larv->filho=identificador(fin,tk,tkn,linha,col);
        larv->filho->prox=valor_2(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        larv->filho=numero(fin,tk,tkn,linha,col);
        larv->filho->prox=exp_matematica(fin,tk,tkn,linha,col);
        return larv;
    }
}

No* nome(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* nome_numero(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME_NUMERO> ");

    if(tk.tipo==NUMERICO){

        larv->filho=numero(fin,tk,tkn,linha,col);
        return larv;
    }
    else
        if(tk.tipo==IDENTIFICADOR){
            larv->filho=nome(fin,tk,tkn,linha,col);
            return larv;
        }
        else{
            return larv;
    }
}

No* indice(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<INDICE> ");
    if(tk.tipo==ACOLCH){

        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col); // tem q dar uma olhada nesse
        larv->filho->prox=nome_numero(fin,tk,tkn,linha,col);
        if(tk.tipo==FCOLCH){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            return larv;
        }

    }
    else{
        return larv;
    }
}

No* nome(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME> ");
    larv->filho=identificador(fin,tk,tkn,linha,col);
    tk=getToken(fin, linha,col);// ultimo altera
    larv->filho->prox=indice(fin,tk,tkn,linha,col);
    return larv;
}

No* comando(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No* comandos(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<COMANDOS> ");

    tk=getToken(fin, linha,col);
    if((tk.tipo == IDENTIFICADOR) || (tk.tipo == ENQUANTO) || (tk.tipo == SE ) || (tk.tipo ==ESCREVER) || (tk.tipo ==LER)){
        larv->filho=comando(fin,tk,tkn,linha,col);
        std::cout<<" -- "<<tk.info<<std::endl;
        if (tk.tipo==PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            larv->filho->prox->prox=comandos(fin,tk,tkn,linha,col);
            return larv;

        }else{
            std::cout<< "erro em <COMANDOS>, falta ;" <<std::endl;
            return larv;
        }
    }
    if(tk.tipo==FIM){
        std::cout<<" ----------- "<<tk.info << " " <<tk.linha<<std::endl;
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        return larv;
    }
    else{
        return larv;
    }
}


No* comando(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<COMANDO>");
    if(tk.tipo==ENQUANTO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=exp_logica(fin,tk,tkn,linha,col);
        larv->filho->prox->prox=bloco(fin,tk,tkn,linha,col); //só ativar depois q funcinar as expressoes
        return larv;
    }
    else
    if(tk.tipo==SE){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=exp_logica(fin,tk,tkn,linha,col);

        if(tk.tipo==ENTAO){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox->prox=bloco(fin,tk,tkn,linha,col);
            larv->filho->prox->prox->prox->prox=senao(fin,tk,tkn,linha,col);
            return larv;
        }else{
            std::cout<<" erro <COMANDO> faltou then"<<std::endl;
        }
    }
    else
    if(tk.tipo==ESCREVER){
        larv->filho=insereLista(larv->filho,tk);
        larv->filho->prox=const_valor(fin,tk,tkn,linha,col);
        tk=getToken(fin, linha,col);
        return larv;
    }
    else
    if(tk.tipo==LER){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=nome(fin,tk,tkn,linha,col);
        return larv;
    }
    else if(tk.tipo==IDENTIFICADOR){
        larv->filho=nome(fin,tk,tkn,linha,col);
        if(tk.tipo==ATRIBUIR){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            std::cout<<" o token é 1 "<<tk.info <<" "<<tk.linha<<std::endl;
            larv->filho->prox->prox=valor(fin,tk,tkn,linha,col);
            std::cout<<" o token é 2 "<<tk.info <<" "<<tk.linha<<std::endl;
            return larv;
        }
        larv->filho->prox=indice(fin,tk,tkn,linha,col);
        return larv;
    }
}
No * bloco(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<BLOCO>");
    if(tk.tipo==INICIO){
        larv->filho=insereLista(larv->filho,tk);
        larv->filho->prox=comandos(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        larv->filho=comando(fin,tk,tkn,linha,col);
        if(tk.tipo==PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            return larv;
        }
        else{
            std::cout<<" <BLOCO> ; não encontrado"<< std::endl;
        }
        return larv;
    }
}

No * def_var(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col);
No * bloco_funcao(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<BLOCO_FUNCAO>");
    tk=getToken(fin, linha,col);
    if(tk.tipo==VARIAVEL){
        larv->filho=def_var(fin,tk,tkn,linha,col);
        larv->filho->prox=bloco(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        larv->filho=bloco(fin,tk,tkn,linha,col);
        return larv;
    }
       return larv;
}
No * funcoes(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<FUNCOES>");
    if(tk.tipo==INTEIRO || tk.tipo==REAL || tk.tipo==VETOR || tk.tipo==IDENTIFICADOR ){
        larv->filho=funcao(fin,tk,tkn,linha,col);
        larv->filho->prox=funcoes(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        return larv;
    }

    return larv;
}
No * funcao(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos

    strcpy(larv->token.info,"<FUNCAO>");
    larv->filho=nome_funcao(fin,tk,tkn,linha,col);

//    Simbolo smb(larv->filho->filho->prox->filho->token.info);
//    smb.sedtTipo(larv->filho->filho->filho->token.info);
//    smb.setParametro(larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info);
//    for ( int i =0;i< smbs.size();i++){
//        if(smbs.at(i).getNome().compare(smb.getNome())==0){
//           smbs.at(i).sedtTipo(larv->filho->filho->filho->token.info);
//           smbs.at(i).setParametro(larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info);
//        }
//    }

//    std::cout<< "teste----- tipo função --" << larv->filho->filho->filho->token.info << std::endl;
//    std::cout<< "teste ---- nome função "<<larv->filho->filho->prox->filho->token.info<< std::endl;
//    std::cout<< "teste ---- param função "<<larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info<< std::endl;

    larv->filho->prox=bloco_funcao(fin,tk,tkn,linha,col);


    return larv;
}
No * def_func(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos

    if(tk.tipo == FUNCAO ){
        strcpy(larv->token.info,"<DEF_FUNC>");
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=funcao(fin,tk,tkn,linha,col);
        larv->filho->prox->prox=funcoes(fin,tk,tkn,linha,col);
        return larv;
    }
    else{
        std::cout<< "erro na definição de funçao, falta functioin" <<std::endl;
        return larv;
    }

}

No * def_tipo(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos

    if(tk.tipo == TIPO ){
        strcpy(larv->token.info,"<DEF_TIPO>");
        larv->filho=insereLista(larv->filho,tk);

        tk=getToken(fin, linha,col);
        if(tk.tipo==IDENTIFICADOR){
            larv->filho->prox=tipo(fin,tk,tkn,linha,col);
            tk=getToken(fin, linha,col);
            if(tk.tipo == PVIRGULA){

                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                larv->filho->prox->prox->prox=tipos(fin,tk,tkn,linha,col);
                return larv;
            }
            else{
                std::cout<< "erro em def_tipo, falta ;" <<std::endl;
                            return larv;
            }
            return larv;
        }else{
            std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }
    }
    else{
        std::cout<< "erro na definição de tipo, falta tipo" <<std::endl;
        return larv;
    }

}

No * def_var(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos

    if(tk.tipo == VARIAVEL ){
        strcpy(larv->token.info,"<DEF_VAR>");
        larv->filho=insereLista(larv->filho,tk);

        tk=getToken(fin, linha,col);
        if(tk.tipo==IDENTIFICADOR){
            larv->filho->prox=variavel(fin,tk,tkn,linha,col);
            tk=getToken(fin, linha,col);
            if(tk.tipo == PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                larv->filho->prox->prox->prox=variaveis(fin,tk,tkn,linha,col);
                return larv;
            }
            else{
                std::cout<< "erro em def_var, falta ;" <<std::endl;
            }
            return larv;
        }else{
            std::cout<< "identificador não encontrado"<<std::endl;
            return NULL;
        }
    }
    else{
        std::cout<< " " <<std::endl;
        return larv;
    }

}

No * def_const(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos

    if(tk.tipo == CONSTANTE ){

        strcpy(larv->token.info,"<DEF_CONST>");
        larv->filho=insereLista(larv->filho,tk);

        tk=getToken(fin, linha,col);
        if(tk.tipo==IDENTIFICADOR){
            larv->filho->prox=constante(fin,tk,tkn,linha,col);
            if(tk.tipo == PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                larv->filho->prox->prox->prox=constantes(fin,tk,tkn,linha,col);

                return larv;
            }
            else{
                std::cout<< "erro em def_const, falta ;" <<std::endl;
                return larv;
            }
        }
        else{
            std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }
    }

    else{
        std::cout<< "erro na definição de constante, falta const" <<std::endl;
        return larv;
    }

}

No * declaracoes(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){  // inicializa as funções

    No *larv =(No*)malloc(sizeof(No));
    strcpy(larv->token.info, "<DECLARACOES>");
    if(tk.tipo==CONSTANTE) {
        larv->filho=def_const(fin,tk,tkn,linha,col);
        if(tk.tipo==TIPO){
            larv->filho->prox=def_tipo(fin,tk,tkn,linha,col);
            if(tk.tipo==VARIAVEL){
                larv->filho->prox->prox=def_var(fin,tk,tkn,linha,col);
                if(tk.tipo==FUNCAO){
                    larv->filho->prox->prox->prox=def_func(fin,tk,tkn,linha,col);
                    return larv;
                }
            }
        }
        if(tk.tipo==VARIAVEL){
            larv->filho->prox=def_var(fin,tk,tkn,linha,col);
            if(tk.tipo==FUNCAO){
                larv->filho->prox->prox=def_func(fin,tk,tkn,linha,col);
                return larv;
            }
            return larv;
        }
        if(tk.tipo==FUNCAO){
            larv->filho->prox=def_func(fin,tk,tkn,linha,col);
            return larv;
        }
    }
    // agora começanco com tipo
    if(tk.tipo==TIPO){
        larv->filho=def_tipo(fin,tk,tkn,linha,col);
        if(tk.tipo==VARIAVEL){
            larv->filho->prox=def_var(fin,tk,tkn,linha,col);
            if(tk.tipo==FUNCAO){
                larv->filho->prox->prox=def_func(fin,tk,tkn,linha,col);
                return larv;
            }
        }
        if(tk.tipo==FUNCAO){
            larv->filho->prox=def_func(fin,tk,tkn,linha,col);
            return larv;
        }
    }
    // começando com variavel
    if(tk.tipo==VARIAVEL){
        larv->filho=def_var(fin,tk,tkn,linha,col);
        if(tk.tipo==FUNCAO){
            larv->filho->prox=def_func(fin,tk,tkn,linha,col);
            return larv;
        }
        else
            return larv;
    }
    return larv;
}

No* corpo(std::ifstream & fin,Token &tk,Token tkn, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CORPO>");
    tk=getToken(fin, linha,col);
    if(tk.tipo == TIPO || tk.tipo == CONSTANTE || tk.tipo == VARIAVEL || tk.tipo == FUNCAO ){

        larv->filho=declaracoes(fin,tk,tkn,linha,col); // estou akiii
        larv->filho->prox=bloco(fin,tk,tkn,linha,col);
        return larv;
    }
    else {
        larv->filho=bloco(fin,tk,tkn,linha,col);
        return larv;
    }
}
No* identificador(std::ifstream &fin,Token tk,Token tkn, int *linha,int *col){
    No *larv=(No*)malloc(sizeof(No));
    if(tk.tipo==IDENTIFICADOR){
        strcpy(larv->token.info,"<IDENTIFICADOR>");
        if(!procuraSimbolo(smbs,tk.info)) smbs.push_back(Simbolo(tk.info)); // colocando na "talela" de simbolos
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
    arv->num=0;
    tk=getToken(fin, linha,col);
    if(tk.tipo==INICIADOR){
        arv->filho=insereLista(arv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo==IDENTIFICADOR){
            arv->filho->prox=identificador(fin,tk,tkn,linha,col);
            tk=getToken(fin, linha,col);
            if(tk.tipo==PVIRGULA){
                arv->filho->prox->prox=insereLista(arv->filho->prox->prox,tk);
                arv->filho->prox->prox->prox=corpo(fin,tk,tkn,linha,col);
                return arv;
            }else{
                std::cout<< "; não encontrado"<<std::endl;
                return NULL;
            }
        }
        else{
                std::cout<< "identificador não encontrado"<<std::endl;
                return NULL;
        }
    }else{
        std::cout<< "iniciador não encontrado"<<std::endl;
        return NULL;
    }
}


int main(int argc, char **argv) {
        std::ifstream fin("file.lug", std::fstream::in);
//    std::ifstream fin("file2.lug", std::fstream::in);
//    std::ifstream fin("file3.lug", std::fstream::in);
    int linha= 1;
    int coluna=1;

    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setRenderHints(QPainter::SmoothPixmapTransform);
    Arvore* a = new Arvore();
    a->init(&scene, &view);

//    Simbolo smb = Simbolo("test");
//    Simbolo smb2 = Simbolo("test2");
//    smbs.push_back(smb);
//    smb.setNome("tetetete");
//    smbs.push_back(smb);

//    cout<< smbs.at(0).getNome()<<endl;
//    cout<< smbs.at(1).getNome()<<endl;
//    smbs.at(0).print();
//    smbs.at(1).print();
//    cout<< procuraSimbolo(smbs,"test");


    Token tk,tkn;
    tkn.linha=-1;
    tkn.col=-1;
    tkn.tipo=-1;
    No *arv=NULL;

//    while (fin.good()) {
//        tk=getToken(fin, &linha,&coluna);
//        std::cout << tk.info << " " << tk.linha << " " << tk.col << " "<< tk.tipo <<std::endl;
//    }

    arv=sintatico(fin,tk,tkn, &linha,&coluna);
    a->setRaiz(arv);

    std::cout<< " " <<std::endl;
    std::cout << " total de nos  " <<contarNos(a->getRaiz()) << std::endl;
    setarNumNos(a->getRaiz());

//    listarSimbolos(smbs);
    a->show();





//    Simbolo sm("ha");
//    if(!sm.getParametro().compare(""))
//        std::cout<<"sou sortudoo"<< std::endl;
    return app.exec();
}
