#include "simbolo.h"
#include <vector>
#include <string.h>
Simbolo::Simbolo(){}

Simbolo::Simbolo(char nome[21],char scopo[21],char tipo[21]){
    strncpy(this->nome,nome,21);
    strncpy(this->scopo,scopo,21);
    strncpy(this->tipo,tipo,21);
}
Simbolo::Simbolo(char nome[21],char scopo[21]){
    strncpy(this->nome,nome,21);
    strncpy(this->scopo,scopo,21);

}
Simbolo::~Simbolo(){
//    std::cout<<"limpou"<<std::endl;
    delete[] this->nome;
    delete[] this->scopo;
    delete[] this->tipo;
}

char* Simbolo::getNome(){
    return this->nome;
}
char* Simbolo::getTipo(){
    return this->tipo;
}

void Simbolo::setNome(char nome[21]){
    strncpy(this->nome,nome,21);
}

void Simbolo::setTipo(char tipo[21]){
    strncpy(this->tipo,tipo,21);
}
void Simbolo::setEscopo(char escopo[21]){
    strncpy(this->scopo,escopo,21);
}

void Simbolo::print(){
    std::cout<<this->getNome()<< " " << this->getScopo() << " " << this->getTipo()<< std::endl;
}

int procuraSimbolo(std::vector<Simbolo*> &simbs,char nome[21]){
    Simbolo *sm;
    for(unsigned int i=0; i < simbs.size(); i++){
        sm=simbs.at(i);
        if(!strcmp(sm->getNome(),nome))
            return 1;
    }

    return 0;
}
char* Simbolo::getScopo(){
    return this->scopo;
}

void listarSimbolos(std::vector<Simbolo*> &simbs){
    std::cout<<"variaveis declaradas"<<std::endl;
    for(unsigned int i=0; i < simbs.size(); i++){
        simbs.at(i)->print();
    }
}

int existeNomeEmEscopo(std::vector<Simbolo*> &simbs,char scopo[21],char nome[21] ){
    for(unsigned int i=0; i < simbs.size(); i++){
        if(!strcmp(simbs.at(i)->getNome(),nome)) // retorna 0 se é igual
            if(!strcmp(simbs.at(i)->getScopo(),scopo))
                return 1;
    }
    return 0;
}
void setTipoArraySimbolo(std::vector<Simbolo*> &simbs_var,char tipo[21]){
    for(unsigned int i=0; i < simbs_var.size(); i++){
        simbs_var.at(i)->setTipo(tipo);
    }
}
