#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

//#include<QApplication>
#include<QApplication>
#include "Arvore.h"
#include "constants.h"
#include "simbolo.h"
#include "simboloconst.h"
#include "simbolofuncao.h"
#include "simboloparam.h"
#include "simbolotipo.h"
#include <list>
#include <iterator>

No* identificador(std::ifstream & fin,Token tk, int *linha,int *col);
No* exp_logica(std::ifstream & fin,Token &tk, int *linha,int *col);
No* op_matematico(std::ifstream & fin,Token tk, int *linha,int *col);
No* exp_matematica(std::ifstream & fin,Token &tk, int *linha,int *col);
No* parametro(std::ifstream & fin,Token &tk, int *linha,int *col);
No* nome_numero(std::ifstream & fin,Token &tk, int *linha,int *col);
No * funcao(std::ifstream & fin,Token &tk, int *linha,int *col);
No* indice(std::ifstream & fin,Token &tk, int *linha,int *col);
No * def_var(std::ifstream & fin,Token &tk, int *linha,int *col);
No* constante(std::ifstream & fin,Token &tk, int *linha,int *col);
No* comando(std::ifstream & fin,Token &tk, int *linha,int *col);

int QNTNOGLOB=0;
std::list<Simbolo*> smbs;
std::list<Simbolo*> smbs_var;

char escopo[21]="global";
char escopo_anterior[21]="global";
char classe[21]="var";
char desc[130];
char iden[21]; // uso em constante

int checkTipoToken(char token[21]){
    int x=0;
    int cont=0;
    int i=0;

    if(strcmp(token,"program")==0){ return cte::INICIADOR; }
    if(strcmp(token,"var")==0){ return cte::VARIAVEL; }
    if(strcmp(token,"function")==0){return cte::FUNCAO;}
    if(strcmp(token,"type")==0){return cte::TIPO;}
    if(strcmp(token,"begin")==0){return cte::INICIO;}
    if(strcmp(token,"end")==0){return cte::FIM;}
    if(strcmp(token,"write")==0){return cte::ESCREVER;}
    if(strcmp(token,"read")==0){return cte::LER;}
    if(strcmp(token,"while")==0){return cte::ENQUANTO;}
    if(strcmp(token,"if")==0){return cte::SE;}
    if(strcmp(token,"then")==0){return cte::ENTAO;}
    if(strcmp(token,"integer")==0){return cte::INTEIRO;}
    if(strcmp(token,"real")==0){return cte::REAL;}
    if(strcmp(token,"array")==0){return cte::VETOR;}
    if(strcmp(token,"else")==0){return cte::SENAO;}
    if(strcmp(token,"of")==0){return cte::DE;}
    if(strcmp(token,":=")==0){return cte::ATRIBUIR;}
    if(strcmp(token,"const")==0){return cte::CONSTANTE;}

    if(strcmp(token,";")==0){return cte::PVIRGULA;}
    if(strcmp(token,":")==0){return cte::DOISPONTOS;}
    if(strcmp(token,",")==0){return cte::VIRGULA;}
    if(strcmp(token,"=")==0){return cte::IGUAL;}
    if(strcmp(token,"(")==0){return cte::APARENTE;}
    if(strcmp(token,")")==0){return cte::FPARENTE;}
    if(strcmp(token,"[")==0){return cte::ACOLCH;}
    if(strcmp(token,"]")==0){return cte::FCOLCH;}

    if(strcmp(token,">")==0){return cte::MAIOR;}
    if(strcmp(token,"<")==0){return cte::MENOR;}
    if(strcmp(token,"!")==0){return cte::EXCLAMACAO;}


    if(strcmp(token,"+")==0){return cte::MAIS;}
    if(strcmp(token,"-")==0){return cte::MENOS;}
    if(strcmp(token,"*")==0){return cte::ASTERISCO;}
    if(strcmp(token,"/")==0){return cte::BARRA;}


    x=strlen(token);


    for(i=0; i < x ; i++){
        switch(token[i]){
        case '@':
            return cte::ERRO;
            break;
        case '#':
            return cte::ERRO;
            break;
        case '$':
            return cte::ERRO;
            break;
        case '%':
            return cte::ERRO;
            break;
        case '&':
            return cte::ERRO;
            break;
        case '`':
            return cte::ERRO;
            break;
        case '|':
            return cte::ERRO;
            break;
        case '~':
            return cte::ERRO;
            break;
        case '^':
            return cte::ERRO;
            break;

        }
    }

    for(i=0; i < x ; i++){

        if(((token[i] >= '0') && (token[i] <= '9') )|| (token[i] == '.')){
            cont++;
        }
    }
    if(cont==x){
        return cte::NUMERICO;
    }

    if(token[0] >= '0' && token[0] <= '9' ){
        return cte::ERRO;
    }

    // caso o algotmo chegue até esse ponto quer dizer que
    // token é um identificador
    return cte::IDENTIFICADOR;
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
    if(ch==' ') ch= fin.get();

    if ( ch=='=' || ch=='<' || ch=='<' || ch=='>' ||
         ch=='(' || ch=='[' || ch==']' || ch=='!' ||
         ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
         ch==',' || ch=='#' || ch=='$' || ch=='%' ||
         ch=='`' || ch=='|' || ch=='~' || ch=='^'){
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



//falta tratar erro
No * const_valor(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONST_VALOR>");

    if(tk.tipo==cte::IDENTIFICADOR){  // o que ele diz de sequencia alfanumerica
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        return larv;
    }
    else{
        larv->filho=nome_numero(fin,tk,linha,col);
        larv->filho->prox=exp_matematica(fin,tk,linha,col);
        return larv;

    }

    return larv;
}


void erro(char tag[20], char info[10],char desc[130],bool tipo){ //tipo 0 -> erro sintatico | 1 semantico
    if(tipo==0)
        std::cout<< "erro em "<<tag<<", falta "<<info<<std::endl;
    if(tipo==1)
          std::cout<<info<<"  erro semantico "<<desc<<std::endl;
}

No* constantes(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONSTANTES> ");

    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=constante(fin,tk,linha,col);
        if (tk.tipo==cte::PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=constantes(fin,tk,linha,col);

            return larv;

        }else{
            erro(";",larv->token.info,"",0);
            return larv;
        }

    }
    else{
        return larv;
    }
}

No* constante(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CONSTANTE>");
    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=identificador(fin,tk,linha,col);
        strncpy(iden,tk.info,21); //semantico...
        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IGUAL){
            larv->filho->prox= insereLista(larv->filho->prox,tk);


            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=const_valor(fin,tk,linha,col);
            // aki que vou jogar essa constante na tabela de simbolos
            if(!existeNomeEmEscopo(smbs,escopo,iden)){
                smbs.push_back(new SimboloConst(iden,escopo,"const","int",1));
            }else{
                strcpy(desc,escopo);
                strcat(desc," variavel redeclarado  - ");
                strcat(desc,iden);
                erro("",larv->token.info,desc ,1);
            }
            return larv;
        }
        else{
            erro("=",larv->token.info,"",0);
            //std::cout<< "erro em <CONSTANTE>, falta =" <<std::endl;
            return larv;
        }
    }
    else{
        erro("IDENTIFICADOR",larv->token.info,"",0);
        //std::cout<< "Erro em <CONSTANTE>identificador não encontrado"<<std::endl;
        return larv;
    }

}
No* numero(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NUMERO>");
    if(tk.tipo==cte::NUMERICO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col); //acabei de comentar ... ver isso
        return larv;
    }
    else{
        erro("numero",larv->token.info,"",0);
        //std::cout<< " número não encontrado" << std::endl;
        return NULL;
    }

}

No* tipo_dado(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPO_DADO>");

    if(tk.tipo==cte::REAL || tk.tipo==cte::INTEIRO ){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        return larv;
    }
    if(tk.tipo ==cte:: VETOR){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo ==cte:: ACOLCH){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col); // acabei de colocar pra tirar o problema de numero
            larv->filho->prox->prox=numero(fin,tk,linha,col);
            if(tk.tipo ==cte:: FCOLCH){
                larv->filho->prox->prox->prox=insereLista(larv->filho->prox->prox->prox,tk);
                tk=getToken(fin, linha,col);
                if(tk.tipo ==cte:: DE){
                larv->filho->prox->prox->prox->prox=insereLista(larv->filho->prox->prox->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox->prox->prox=tipo_dado(fin,tk,linha,col);
                return larv;
                }

            }

        }
    }else{
         if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho=identificador(fin,tk,linha,col);
            tk=getToken(fin, linha,col);
            return larv;
        }else{
            erro("o tipo especificado",larv->token.info,"",0);
            //std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }

    }

}

No* lista_id(std::ifstream & fin,Token &tk, int *linha,int *col,int funcao,int &qnt_parms){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<LISTA_ID>");

    if(tk.tipo==cte::VIRGULA){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho->prox=identificador(fin,tk,linha,col);
//semantico
//        if(!existeNomeEmEscopo(smbs,escopo,tk.info) && !existeNomeEmEscopo(smbs_var,escopo,tk.info))
//            smbs_var.push_back(new Simbolo(tk.info,escopo,"var"));

        if(funcao==0){
            if(!existeNomeEmEscopo(smbs,escopo,tk.info) && !existeNomeEmEscopo(smbs_var,escopo,tk.info))
                smbs_var.push_back(new Simbolo(tk.info,escopo,"var"));
            else{
                strcpy(desc,escopo);
                strcat(desc," variavel redeclarado  - ");
                strcat(desc,iden);
                erro("",larv->token.info,desc ,1);

            }
        }
        else// funcao ==1 -> significa que é um Param, é chamado por nome_função
            if(!existeNomeEmEscopo(smbs,escopo,tk.info) && !existeNomeEmEscopo(smbs_var,escopo,tk.info)){
                smbs_var.push_back(new SimboloParam(tk.info,escopo,"param",qnt_parms));
                qnt_parms=qnt_parms+1;
            }
            else{
                strcpy(desc,escopo);
                strcat(desc," parametro redeclarado  - ");
                strcat(desc,iden);
                erro("",larv->token.info,desc ,1);

            }




        // fim semantico
        tk=getToken(fin, linha,col);
        larv->filho->prox->prox=lista_id(fin,tk,linha,col,funcao,qnt_parms);
        return larv;
        }else{
            erro(",",larv->token.info,"",0);
            //std::cout<< "identificador não encontrado em lista_id"<<std::endl;
            return NULL;
        }

    }
    else return larv;
}
No * variavel(std::ifstream & fin,Token &tk, int *linha,int *col,int funcao,int &qnt_parms);
No * variaveis(std::ifstream & fin,Token &tk, int *linha,int *col,int funcao,int &qnt_parms){// 1 se vem de funcao
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VARIAVEIS> ");
//    int qnt_parms=0;
    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=variavel(fin,tk,linha,col,funcao,qnt_parms);
        if (tk.tipo==cte::PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=variaveis(fin,tk,linha,col,funcao,qnt_parms);
            return larv;

        }else{
            erro(";",larv->token.info,"",0);
            //std::cout<< "erro na variaveis, falta ;" <<std::endl;
            return larv;
        }

    }else{
        return larv;
    }
}

No* variavel(std::ifstream & fin,Token &tk, int *linha,int *col,int funcao,int &qnt_parms){ //1 se é param, vem de funcao
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VARIAVEL>");

    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=identificador(fin,tk,linha,col);
        strncpy(iden,tk.info,21);
        if(funcao==0){
            if(!existeNomeEmEscopo(smbs,escopo,tk.info) && !existeNomeEmEscopo(smbs_var,escopo,tk.info))
                smbs_var.push_back(new Simbolo(tk.info,escopo,"var"));
            else{
                strcpy(desc,escopo);
                strcat(desc," variavel redeclarado  - ");
                strcat(desc,iden);
                erro("",larv->token.info,desc ,1);

            }
        }
        else// funcao ==1 -> significa que é um Param, é chamado por nome_função
            if(!existeNomeEmEscopo(smbs,escopo,tk.info) && !existeNomeEmEscopo(smbs_var,escopo,tk.info)){
                smbs_var.push_back(new SimboloParam(tk.info,escopo,"param",qnt_parms));
                qnt_parms=qnt_parms+1;
            }
            else{
                strcpy(desc,escopo);
                strcat(desc," variavel redeclarado  - ");
                strcat(desc,iden);
                erro("",larv->token.info,desc ,1);

            }

        tk=getToken(fin, linha,col);
        larv->filho->prox = lista_id(fin,tk,linha,col,funcao,qnt_parms);

        if(tk.tipo==cte::DOISPONTOS){
            larv->filho->prox->prox= insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);

            setTipoArraySimbolo(smbs_var,tk.info);// colocar o tipo em smbs_var ...
            smbs.merge(smbs_var);
            smbs_var.clear();

            larv->filho->prox->prox->prox=tipo_dado(fin,tk,linha,col);
            return larv;
        }else{
            erro(":",larv->token.info,"",0);
            //std::cout<<"erro em variavel, : não encontrado.   encontrado "<<tk.info<<" "<<tk.linha<<std::endl;
        }

    }else{
        erro("IDENTIFICADOR",larv->token.info,"",0);
        //std::cout<< "identificador não encontrado"<<std::endl;
        return NULL;
    }
}
No* tipo(std::ifstream & fin,Token &tk, int *linha,int *col);
No * tipos(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPOS> ");

    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=tipo(fin,tk,linha,col);
        if (tk.tipo==cte::PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=tipos(fin,tk,linha,col);

            return larv;

        }else{
            erro(";",larv->token.info,"",0);
            //std::cout<< "erro na variaveis, falta ;" <<std::endl;
            return larv;
        }

    }else{
        return larv;
    }
}
No* tipo(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<TIPO>");
    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=identificador(fin,tk,linha,col);
         tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IGUAL){
            larv->filho->prox= insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=tipo_dado(fin,tk,linha,col);

            return larv;
        }
        else{
            erro("=",larv->token.info,"",0);
            //std::cout<< "erro em <TIPO>, falta =" <<std::endl;
            return larv;
        }
    }
    else{
        erro("IDENTIFICADOR",larv->token.info,"",0);
        //std::cout<< "Erro em <CONSTANTE>identificador não encontrado"<<std::endl;
        return larv;
    }

}

int contarParamFuncao(No* larv){
    if(larv==NULL) return 0;
    if(!strcmp(larv->token.info,"<IDENTIFICADOR>")){
        std::cout<<escopo <<"--- "<<larv->filho->token.info<<std::endl;
//        contarParamFuncao(larv->filho) + contarParamFuncao(larv->prox);
        return 1 + contarParamFuncao(larv->filho) + contarParamFuncao(larv->prox);
    }
    else
        return contarParamFuncao(larv->filho) + contarParamFuncao(larv->prox);
}

No * nome_funcao(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME_FUNCAO>");
    larv->filho=tipo_dado(fin,tk,linha,col);
    int qnt_params=0;
    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho->prox=identificador(fin,tk,linha,col);
        // jogar esse identificador na tabela principal
        strcpy(escopo,tk.info);// atualizando o escopo para a função

        if(!existeNomeEmEscopo(smbs,escopo,tk.info)){
            SimboloFuncao *sf = new SimboloFuncao(tk.info,"GLOBAL","FUNCAO");
        //
        strncpy(iden,tk.info,21); // salvando o identificador no temporario
        tk=getToken(fin,linha,col);
        if(tk.tipo==cte::APARENTE){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
//            strcpy(escopo_anterior,escopo);// salvando escopo anterior
//            strcpy(escopo,iden);           // setar flag para parametro

            tk=getToken(fin,linha,col);
            larv->filho->prox->prox->prox=variaveis(fin,tk,linha,col,1,qnt_params);// passando 1, significa q essa variavel será paramentro,
                                                                        // vindo de nome_funcao
                                                                        // inicialmente a qnt_parms é 0
//            int total_de_params = contarParamFuncao(larv->filho->prox->prox->prox);
//            std::cout<<"total de parametos "<< total_de_params<<std::endl;
            std::cout<<"$$$$$ "<<qnt_params<<std::endl;
//            sf->setQnt_Params(contarParamFuncao(larv->filho->prox->prox->prox));
            sf->setQnt_Params(qnt_params);
            smbs.push_back(sf);
            if(tk.tipo==cte::FPARENTE){
                larv->filho->prox->prox->prox=insereLista(larv->filho->prox->prox->prox,tk);
//                strcpy(escopo,escopo_anterior);// voltando o escopo anterior
                tk=getToken(fin,linha,col);
                return larv;
            }
            else{
                erro(")",larv->token.info,"",0);
                return larv;
            }
        }
        else{
            erro("(",larv->token.info,"",0);
            return larv;

        }
    }// semantico
        else{
            //erro ja existe identificador em escopo
            strcpy(desc,"identificador já em uso  - ");
            strcat(desc,iden);
            erro("",larv->token.info,desc ,1);
        }
    }
    return larv;
}
No* bloco(std::ifstream & fin,Token &tk, int *linha,int *col);
No* senao(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<SENAO> ");
    tk=getToken(fin, linha,col);
    if(tk.tipo==cte::SENAO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=bloco(fin,tk,linha,col);
        return larv;
    }
    else{
        return larv;
    }
}
No* op_logico(std::ifstream & fin,Token tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<OP_LOGICO> ");
    larv->filho=insereLista(larv->filho,tk);
    return larv;
}

No* exp_logica_2(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_LOGICA_2> ");
    if((tk.tipo==cte::MAIOR) || (tk.tipo==cte::MENOR) ||(tk.tipo==cte::IGUAL) ||(tk.tipo==cte::EXCLAMACAO) ){
        larv->filho=op_logico(fin,tk,linha,col);
        tk=getToken(fin, linha,col); // test
        larv->filho->prox=exp_logica(fin,tk,linha,col);
        return larv;
    }
    else {
        return larv;
    }
}
No* op_matematico(std::ifstream & fin,Token tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<OP_MATEMATICO> ");
    larv->filho=insereLista(larv->filho,tk);
    return larv;
}

No* exp_matematica_2(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_MATEMATiCA_2> ");
    if((tk.tipo==cte::MAIS) || (tk.tipo==cte::MENOS) ||(tk.tipo==cte::ASTERISCO) ||(tk.tipo==cte::BARRA) ){
        larv->filho=op_matematico(fin,tk,linha,col);
        tk=getToken(fin, linha,col); // test
        larv->filho->prox=exp_matematica(fin,tk,linha,col);
        return larv;
    }else{
        return larv;
    }
}



No* exp_matematica(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_MATEMATICA> ");
     if((tk.tipo==cte::MAIS) || (tk.tipo==cte::MENOS) ||(tk.tipo==cte::ASTERISCO) ||(tk.tipo==cte::BARRA) ){
        larv->filho=op_matematico(fin,tk,linha,col);
        tk=getToken(fin, linha,col);
        larv->filho->prox=nome_numero(fin,tk,linha,col);
        larv->filho->prox->prox=exp_matematica(fin,tk,linha,col);
        return larv;
    }
    else
        return larv;
}

No* exp_logica(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<EXP_LOGICA> ");
    larv->filho=nome_numero(fin,tk,linha,col);
    larv->filho->prox= exp_matematica(fin,tk,linha,col);
    larv->filho->prox->prox = exp_logica_2(fin,tk,linha,col);
    return larv;
}


No* lista_param(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<LISTA_PARAM>");
        if(tk.tipo==cte::VIRGULA){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=parametro(fin,tk,linha,col);
        return larv;
    }
    else{
        return larv;
    }
}

No* nome_numero(std::ifstream & fin,Token &tk, int *linha,int *col);

No* parametro(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<PARAMETRO>");

    larv->filho=nome_numero(fin,tk,linha,col);
    larv->filho->prox=lista_param(fin,tk,linha,col);
    return larv;

}

No* parametros(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<PARAMETROS>");
    tk=getToken(fin, linha,col);
    if(tk.tipo==cte::APARENTE){
        larv->filho=insereLista(larv->filho,tk);
        larv->filho->prox=parametro(fin,tk,linha,col);
        if(tk.tipo==cte::FPARENTE){
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
No* valor_2(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VALOR_2>");

    if(tk.tipo==cte::APARENTE){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=parametro(fin,tk,linha,col);
        if(tk.tipo==cte::FPARENTE){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            return larv;
        }
        else{
            //std::cout<<"erro em valor_2, FALTOU fechar colchetes  )"<<std::endl;
            erro(")",larv->token.info,"",0);
            return larv;

        }
    }
    else {
        larv->filho=indice(fin,tk,linha,col);
        larv->filho->prox=exp_matematica(fin,tk,linha,col);
        return larv;
    }
}

No* valor(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<VALOR>");
    if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=identificador(fin,tk,linha,col);
        tk=getToken(fin, linha,col);
        larv->filho->prox=valor_2(fin,tk,linha,col);
        return larv;
    }
    else{
        larv->filho=numero(fin,tk,linha,col);
        larv->filho->prox=exp_matematica(fin,tk,linha,col);
        return larv;
    }
}

No* nome(std::ifstream & fin,Token &tk, int *linha,int *col);
No* nome_numero(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME_NUMERO> ");

    if(tk.tipo==cte::NUMERICO){
        larv->filho=numero(fin,tk,linha,col);
        return larv;
    }
    else
        if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho=nome(fin,tk,linha,col);
            return larv;
        }
        else{
            return larv;
    }
}

No*
indice(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<INDICE> ");
    if(tk.tipo==cte::ACOLCH){

        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col); // tem q dar uma olhada nesse
        larv->filho->prox=nome_numero(fin,tk,linha,col);
        if(tk.tipo==cte::FCOLCH){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            return larv;
        }else{
            erro("]",larv->token.info,"",0);
            return larv;
        }

    }
    else{
        return larv;
    }
}

No* nome(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<NOME> ");
    larv->filho=identificador(fin,tk,linha,col);
    tk=getToken(fin, linha,col);// ultimo altera
    larv->filho->prox=indice(fin,tk,linha,col);
    return larv;
}


No* comandos(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<COMANDOS> ");

    if((tk.tipo ==cte:: IDENTIFICADOR) || (tk.tipo ==cte:: ENQUANTO) || (tk.tipo ==cte:: SE ) || (tk.tipo ==cte::ESCREVER) || (tk.tipo ==cte::LER)){
        larv->filho=comando(fin,tk,linha,col);
        if (tk.tipo==cte::PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=comandos(fin,tk,linha,col);
            return larv;

        }else{
            std::cout<< "erro em <COMANDOS>, falta ;"<<tk.linha <<std::endl;
            erro(";",larv->token.info,"",0);
            return larv;
        }
    }
    if(tk.tipo==cte::FIM){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        return larv;
    }
    else{
        return larv;
    }
}


No* comando(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<COMANDO>");

    if(tk.tipo==cte::ENQUANTO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=exp_logica(fin,tk,linha,col);
        larv->filho->prox->prox=bloco(fin,tk,linha,col); //só ativar depois q funcinar as expressoes
        return larv;
    }
    else
    if(tk.tipo==cte::SE){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=exp_logica(fin,tk,linha,col);

        if(tk.tipo==cte::ENTAO){
            larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox->prox=bloco(fin,tk,linha,col);
            larv->filho->prox->prox->prox->prox=senao(fin,tk,linha,col);
            return larv;
        }else{
            //std::cout<<" erro <COMANDO> faltou then"<<std::endl;
            erro("then",larv->token.info,"",0);
            return larv;
        }
    }
    else
    if(tk.tipo==cte::ESCREVER){
        larv->filho=insereLista(larv->filho,tk);
        larv->filho->prox=const_valor(fin,tk,linha,col);
        tk=getToken(fin, linha,col);
        return larv;
    }
    else
    if(tk.tipo==cte::LER){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=nome(fin,tk,linha,col);
        return larv;
    }
    else if(tk.tipo==cte::IDENTIFICADOR){
        larv->filho=nome(fin,tk,linha,col);
        if(tk.tipo==cte::ATRIBUIR){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            tk=getToken(fin, linha,col);
            larv->filho->prox->prox=valor(fin,tk,linha,col);
            return larv;
        }
        else{
            std::cout<< " faltou comando de atribuir em COMANDO - "<< std::endl;
        return larv;
        }
    }
}
No * bloco(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<BLOCO>");
    if(tk.tipo==cte::INICIO){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=comandos(fin,tk,linha,col);
        return larv;
    }
    else{
        larv->filho=comando(fin,tk,linha,col);
        if(tk.tipo==cte::PVIRGULA){
            larv->filho->prox=insereLista(larv->filho->prox,tk);
            return larv;
        }
        else{
            //std::cout<<" <BLOCO> ; não encontrado "<<tk.linha<< std::endl;
            erro(";",larv->token.info,"",0);
            return larv;
        }
    }
}


No * bloco_funcao(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<BLOCO_FUNCAO>");

    if(tk.tipo==cte::VARIAVEL){
        larv->filho=def_var(fin,tk,linha,col);
        larv->filho->prox=bloco(fin,tk,linha,col);
        return larv;
    }
    else{
        larv->filho=bloco(fin,tk,linha,col);
        return larv;
    }
       return larv;
}
No * funcoes(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<FUNCOES>");
    if(tk.tipo==cte::INTEIRO || tk.tipo==cte::REAL || tk.tipo==cte::VETOR || tk.tipo==cte::IDENTIFICADOR ){
        larv->filho=funcao(fin,tk,linha,col);
        larv->filho->prox=funcoes(fin,tk,linha,col);
        return larv;
    }
    else{
        return larv;
    }

    return larv;
}
No * funcao(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<FUNCAO>");

    larv->filho=nome_funcao(fin,tk,linha,col);

//    Simbolo smb(larv->filho->filho->prox->filho->token.info);
//    smb.sedtTipo(larv->filho->filho->filho->token.info);
//    smb.setParametro(larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info);
//    for ( int i =0;i< smbs.size();i++){
//        if(smbs.at(i).getNome().compare(smb.getNome())==cte::0){
//           smbs.at(i).sedtTipo(larv->filho->filho->filho->token.info);
//           smbs.at(i).setParametro(larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info);
//        }
//    }

//    std::cout<< "teste----- tipo função --" << larv->filho->filho->filho->token.info << std::endl;
//    std::cout<< "teste ---- nome função "<<larv->filho->filho->prox->filho->token.info<< std::endl;
//    std::cout<< "teste ---- param função "<<larv->filho->filho->prox->prox->prox->filho->filho->prox->prox->filho->token.info<< std::endl;

    larv->filho->prox=bloco_funcao(fin,tk,linha,col);
    strcpy(escopo,"global");


    return larv;
}
No * def_func(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<DEF_FUNC>");

    if(tk.tipo ==cte:: FUNCAO ){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        larv->filho->prox=funcao(fin,tk,linha,col);
        larv->filho->prox->prox=funcoes(fin,tk,linha,col);
        return larv;
    }
    else{
        return larv;
    }

}

No * def_tipo(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<DEF_TIPO>");

    if(tk.tipo ==cte:: TIPO ){
        larv->filho=insereLista(larv->filho,tk);

        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho->prox=tipo(fin,tk,linha,col);
//            tk=getToken(fin, linha,col);
            if(tk.tipo ==cte:: PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox=tipos(fin,tk,linha,col);
                return larv;
            }
            else{
                erro(";",larv->token.info,"",0);
                //std::cout<< "erro em def_tipo, falta ;" <<std::endl;
                return larv;
            }
            return larv;
        }else{
            erro("IDENTIFICADOR",larv->token.info,"",0);
            //std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }
    }
    else{
        return larv;
    }

}

No * def_var(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<DEF_VAR>");

   int qnt_params=0;
    if(tk.tipo ==cte:: VARIAVEL ){
        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho->prox=variavel(fin,tk,linha,col,0,qnt_params);// passando 0, pq 0 significa que variavel não vem de uma declaração de função
            if(tk.tipo ==cte:: PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox=variaveis(fin,tk,linha,col,0,qnt_params);// passando 0, pq 0 significa que variavel não vem de uma declaração de função
                                                                            //
                return larv;
            }
            else{
                erro(";",larv->token.info,"",0);
                //std::cout<< "erro em def_var, falta ;" <<std::endl;
                return larv;
            }
//            return larv;
        }else{
            erro("IDENTIFICADOR",larv->token.info,"",0);
            //std::cout<< "identificador não encontrado"<<std::endl;
            return NULL;
        }
    }
    else{
        return larv;
    }

}

No * def_const(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<DEF_CONST>");

    if(tk.tipo ==cte:: CONSTANTE ){

        larv->filho=insereLista(larv->filho,tk);

        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho->prox=constante(fin,tk,linha,col);
            if(tk.tipo ==cte:: PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox=constantes(fin,tk,linha,col);

                return larv;
            }
            else{
                erro(";",larv->token.info,"",0);
                //std::cout<< "erro em def_const, falta ;" <<std::endl;
                return larv;
            }
        }
        else{
            erro("IDENTIFICADOR",larv->token.info,"",0);
            //std::cout<< "identificador não encontrado"<<std::endl;
            return larv;
        }
    }

    else{
        return larv;
    }

}

No * declaracoes(std::ifstream & fin,Token &tk, int *linha,int *col){  // inicializa as funções

    No *larv =(No*)malloc(sizeof(No));
    strcpy(larv->token.info, "<DECLARACOES>");

    larv->filho=def_const(fin,tk,linha,col);
    larv->filho->prox=def_tipo(fin,tk,linha,col);
    larv->filho->prox->prox=def_var(fin,tk,linha,col);
    larv->filho->prox->prox->prox=def_func(fin,tk,linha,col);
    return larv;
}
No* corpo(std::ifstream & fin,Token &tk, int *linha,int *col){
    No *larv =(No*)malloc(sizeof(No)); /// lista auxiliar para montar a lista de filhos
    strcpy(larv->token.info,"<CORPO>");

    if(tk.tipo ==cte:: TIPO || tk.tipo ==cte:: CONSTANTE || tk.tipo ==cte:: VARIAVEL || tk.tipo ==cte:: FUNCAO ){
        larv->filho=declaracoes(fin,tk,linha,col);
        larv->filho->prox=bloco(fin,tk,linha,col);
        return larv;
    }
    else {
        larv->filho=bloco(fin,tk,linha,col);
        return larv;
    }
}
No* identificador(std::ifstream &fin,Token tk, int *linha,int *col){
    No *larv=(No*)malloc(sizeof(No));
    if(tk.tipo==cte::IDENTIFICADOR){
        strcpy(larv->token.info,"<IDENTIFICADOR>");
//        if(!procuraSimbolo(smbs,tk.info)) smbs.push_back(Simbolo(tk.info)); // colocando na "talela" de simbolos
        larv->filho=insereLista(larv->filho,tk);
        return larv;
    }else{
        //std::cout <<"identificador não encontrado" <<std::endl;
        return NULL;
    }
}


No* sintatico(std::ifstream & fin,Token tk, int *linha,int *col){
    No * larv= NULL;
    strcpy(tk.info,"<PROGRAMA>");
    larv=insereLista(larv,tk); //cabeça da regra
    larv->num=0;

    tk=getToken(fin, linha,col);
    if(tk.tipo==cte::INICIADOR){

        larv->filho=insereLista(larv->filho,tk);
        tk=getToken(fin, linha,col);
        if(tk.tipo==cte::IDENTIFICADOR){
            larv->filho->prox=identificador(fin,tk,linha,col);
//            std::cout<<"teste"<<std::endl;
            tk=getToken(fin, linha,col);
            if(tk.tipo==cte::PVIRGULA){
                larv->filho->prox->prox=insereLista(larv->filho->prox->prox,tk);
                tk=getToken(fin, linha,col);
                larv->filho->prox->prox->prox=corpo(fin,tk,linha,col);
                return larv;
            }else{
                //std::cout<< "; não encontrado"<<std::endl;
                erro(";",larv->token.info,"",0);
                return NULL;
            }
        }
        else{
                erro("IDENTIFICADOR",larv->token.info,"",0);
                //std::cout<< "identificador não encontrado"<<std::endl;
                return NULL;
        }
    }else{
        erro("INICIADOR",larv->token.info,"",0);
        //std::cout<< "iniciador não encontrado"<<std::endl;
        return NULL;
    }
}


int main(int argc, char **argv) {
    std::ifstream fin("file.lug", std::fstream::in);
//    std::ifstream fin("file2.lug", std::fstream::in);
//    std::ifstream fin("file3.lug", std::fstream::in);
//    std::ifstream fin("file3.lug", std::fstream::in);
    int linha= 1;
    int coluna=1;

    QApplication app(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setRenderHints(QPainter::SmoothPixmapTransform);
    Arvore* a = new Arvore();
    a->init(&scene, &view);



    Token tk;
    No *arv=NULL;

//    while (fin.good()) {
//        tk=getToken(fin, &linha,&coluna);
//        std::cout << tk.info << " " << tk.linha << " " << tk.col << " "<< tk.tipo <<std::endl;
//    }

    arv=sintatico(fin,tk, &linha,&coluna);
    a->setRaiz(arv);
    std::cout << " total de nos  " <<contarNos(a->getRaiz()) << std::endl;
    setarNumNos(a->getRaiz());
    a->show();

//    smbs.push_back(new Simbolo("test",escopo,"var","int"));
//    smbs.push_back(new Simbolo("tam",escopo,"var","int"));
//    smbs.push_back(new SimboloTipo("vetor",escopo,"tipo","array",15,"integer"));
//    smbs.push_back(new SimboloFuncao("fatorial",escopo,"funcao","int",3));
//    smbs.push_back(new SimboloConst("cont",escopo,"const","int",3233));
//    smbs.push_back(new SimboloParam("tam2",escopo,"param","int",1));
//    if(!existeNomeEmEscopo(smbs,escopo,"testrrr"))
//        smbs.push_back(new Simbolo("testrrrr",escopo,"const"));
//    std::list<Simbolo*>::iterator i;
//    i=smbs.begin();
//    std::advance(i,3);
//    smbs.push_back(*i);
    listarSimbolos(smbs);


    std::cout<<"-Fim-"<< std::endl;
    return app.exec();
}
//funcao bloco depois do PV, ultimo erro
