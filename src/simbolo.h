#ifndef SIMBOLO_H
#define SIMBOLO_H
#include <iostream>
#include <string>
#include<vector>
#include "Arvore.h"

class Simbolo
{
public:
    Simbolo(std::string nome);
    std::string nome;
    std::string tipo;
    std::string parametro;



    std::string getNome();
    std::string getTipo();
    std::string getParametro();
    void setNome(std::string nome);
    void sedtTipo(std::string tipo);
    void setParametro(std::string param);

    void print();
    void listarParametro();
private:

};

int procuraSimbolo(std::vector<Simbolo> &simbs,std::string nome);
int possuifuncao(std::vector<Simbolo> &simbs,std::string nome);
void listarSimbolos(std::vector<Simbolo> &simbs);

#endif // SIMBOLO_H
