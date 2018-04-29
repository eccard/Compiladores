#ifndef SIMBOLOPARAM_H
#define SIMBOLOPARAM_H

#include "simbolo.h"
class SimboloParam : public Simbolo {
  int posicao;

  void setPosicao(int posicao);
  void print();

public:
  int getPosicao();
  SimboloParam(char nome[21], char scopo[21], char classe[21], char tipo[21],
               int posicao);
  SimboloParam(char nome[21], char scopo[21], char classe[21]);
  SimboloParam(char nome[21], char scopo[21], char classe[21], int posicaos);
};

#endif // SIMBOLOPARAM_H
