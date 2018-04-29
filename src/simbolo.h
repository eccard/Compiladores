#ifndef SIMBOLO_H
#define SIMBOLO_H
#include <iostream>
#include <string>
#include<list>
//#include "Arvore.h"

class Simbolo
{
public:
    Simbolo();
    Simbolo(char nome[21],char scopo[21]);
//    Simbolo(char nome[21],char scopo[21],char tipo[21]);
    Simbolo(char nome[21],char scopo[21],char classe[21]);
    Simbolo(char nome[21],char scopo[21],char classe[21],char tipo[21]);

    char nome[21];
    char scopo[21];
    char classe[21];
    char tipo[21];

    char* getNome();
    char* getTipo();
    char* getScopo();
    virtual void print(); // virtual LB, late biding(faz a amarração em tempo de compilação)
private:

   void setClasse(char classe[21]);

public:
    void setNome(char nome[21]);
    void setTipo(char tipo[21]);
    void setEscopo(char escopo[21]);
    char* getClasse();

};

//int existeNomeEmEscopo(std::string escopo);
char *tipoParamFuncao(std::list<Simbolo*> &simbs,char nome_func[21],int posicao);
int qntParamsFuncao(std::list<Simbolo*> &simbs,char nome[21] );
char* tipoNomeEmEscopo(std::list<Simbolo*> &simbs,char scopo[21],char nome[21] );
char* classeNomeEmEscopo(std::list<Simbolo*> &simbs,char scopo[21],char nome[21] );
int existeNomeEmEscopo(std::list<Simbolo*> &simbs,char scopo[21],char nome[21] );
int procuraSimbolo(std::list<Simbolo*> &simbs,char nome[21]);
//int possuifuncao(std::vector<Simbolo> &simbs,std::string nome);
void listarSimbolos(std::list<Simbolo*> &simbs);
void setTipoArraySimbolo(std::list<Simbolo*> &simbs_var,char tipo[21]);
#endif // SIMBOLO_H
