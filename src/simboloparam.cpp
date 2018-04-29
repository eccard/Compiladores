#include "simboloparam.h"

SimboloParam::SimboloParam(char nome[21],char scopo[21],char classe[21],char tipo[21],int posicao)
    :Simbolo(nome,scopo,classe,tipo){
    this->posicao=posicao;
}
SimboloParam::SimboloParam(char nome[21],char scopo[21],char classe[21])
    :Simbolo(nome,scopo,classe){
}
SimboloParam::SimboloParam(char nome[21],char scopo[21],char classe[21],int posicao)
    :Simbolo(nome,scopo,classe){
    this->posicao=posicao;
}

int SimboloParam::getPosicao(){
    return this->posicao;
}
void SimboloParam::setPosicao(int posicao){
    this->posicao=posicao;
}
void SimboloParam::print(){
    std::cout<<this->getNome()<< " " << this->getScopo() << " "<<this->getClasse() <<" " << this->getTipo()<<" "<<this->getPosicao()<< std::endl;
}

