#ifndef SIMBOLOTIPO_H
#define SIMBOLOTIPO_H

#include "simbolo.h"

class SimboloTipo : public Simbolo
{
    void print();
public:
    SimboloTipo(char nome[21],char scopo[21],char classe[21],char tipo[21],int tam,char tipo_tipo[21]);
    ~SimboloTipo();
    int getTam();
    char* getTipo_tipo();

    void setTam(int tam);
    void setTipo_tipo(char tipo_tipo[21]);

private:
    int tam;
    char tipo_tipo[21];

};

#endif // SIMBOLOTIPO_H
