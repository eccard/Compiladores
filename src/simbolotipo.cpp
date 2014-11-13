#include "simbolotipo.h"
#include <string.h>

SimboloTipo::SimboloTipo(char nome[21],char scopo[21],char classe[21],char tipo[21],int tam,char tipo_tipo[21])
:Simbolo(nome,scopo,classe,tipo){
    this->tam=tam;
    strncpy(this->tipo_tipo,tipo_tipo,21);
}
SimboloTipo::~SimboloTipo(){
    delete[] this->nome;
    delete[] this->scopo;
    delete[] this->classe;
    delete[] this->tipo;
}

int SimboloTipo::getTam(){
    return this->tam;
}

char* SimboloTipo::getTipo_tipo(){
    return this->tipo_tipo;
}

void SimboloTipo::setTam(int tam){
    this->tam=tam;
}
void SimboloTipo::setTipo_tipo(char tipo_tipo[21]){
    strncpy(this->tipo_tipo,tipo_tipo,21);
}
void SimboloTipo::print(){
    std::cout<<this->getNome()<< " " << this->getScopo() << " "<<this->getClasse() <<" " << this->getTipo()<<" "<<this->getTam()<<" "<<this->getTipo_tipo()<< std::endl;
}

