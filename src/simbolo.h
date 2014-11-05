#ifndef SIMBOLO_H
#define SIMBOLO_H
#include <iostream>
#include <string>
#include<vector>
//#include "Arvore.h"

class Simbolo
{
public:
    Simbolo();
    Simbolo(char nome[21],char scopo[21]);
    Simbolo(char nome[21],char scopo[21],char tipo[21]);
    char nome[21];
    char scopo[21];
    char tipo[21];

    char* getNome();
    char* getTipo();
    char* getScopo();
    void print();
    ~Simbolo();
private:
public:
    void setNome(char nome[21]);
    void setTipo(char tipo[21]);
    void setEscopo(char escopo[21]);


};

//int existeNomeEmEscopo(std::string escopo);
int existeNomeEmEscopo(std::vector<Simbolo*> &simbs,char scopo[21],char nome[21] );
int procuraSimbolo(std::vector<Simbolo*> &simbs,char nome[21]);
//int possuifuncao(std::vector<Simbolo> &simbs,std::string nome);
void listarSimbolos(std::vector<Simbolo*> &simbs);
void setTipoArraySimbolo(std::vector<Simbolo*> &simbs_var,char tipo[21]);
#endif // SIMBOLO_H
