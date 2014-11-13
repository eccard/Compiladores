#ifndef SIMBOLOCONST_H
#define SIMBOLOCONST_H

#include "simbolo.h"
class SimboloConst : public Simbolo
{
    double valor;

    double getValor();
    void setValor(double valor);
    void print();

public:
    SimboloConst(char nome[21],char scopo[21],char classe[21],char tipo[21],double valor);
    ~SimboloConst();
};

#endif // SIMBOLOCONST_H
