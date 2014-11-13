#ifndef SIMBOLOFUNCAO_H
#define SIMBOLOFUNCAO_H
#include "simbolo.h"
class SimboloFuncao: public Simbolo
{
    int qnt_params;

    int getQnt_Params();
    void setQnt_Params(int qnt_params);
    void print();
public:
    SimboloFuncao(char nome[21],char scopo[21],char classe[21],char tipo[21],int qnt_params);
    ~SimboloFuncao();
};

#endif // SIMBOLOFUNCAO_H
