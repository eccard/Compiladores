#include "simbolofuncao.h"
#include <string.h>
SimboloFuncao::SimboloFuncao(char nome[21], char scopo[21], char classe[21],
                             char tipo[21], int qnt_params)
    : Simbolo(nome, scopo, classe, tipo) {
  this->qnt_params = qnt_params;
}
SimboloFuncao::SimboloFuncao(char nome[21], char scopo[21], char classe[21])
    : Simbolo(nome, scopo, classe) {}

int SimboloFuncao::getQnt_Params() { return this->qnt_params; }

void SimboloFuncao::setQnt_Params(int qnt_params) {
  this->qnt_params = qnt_params;
}

void SimboloFuncao::print() {
  std::cout << this->getNome() << " " << this->getScopo() << " "
            << this->getClasse() << " " << this->getTipo() << " "
            << this->getQnt_Params() << std::endl;
}
