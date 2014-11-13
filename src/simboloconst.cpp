#include "simboloconst.h"

SimboloConst::SimboloConst(char nome[21],char scopo[21],char classe[21],char tipo[21],double valor)
    :Simbolo(nome,scopo,classe,tipo){
    this->valor=valor;
}

void SimboloConst::setValor(double valor){
    this->valor=valor;
}
double SimboloConst::getValor(){
    return this->valor;
}

void SimboloConst::print(){
    std::cout<<this->getNome()<< " " << this->getScopo() << " " <<this->getClasse() <<" "<< this->getTipo()<<" "<<this->getValor() <<std::endl;
}

SimboloConst::~SimboloConst(){
    delete[] this->nome;
    delete[] this->scopo;
    delete[] this->tipo;
}
