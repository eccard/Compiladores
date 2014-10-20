#include "simbolo.h"
#include <vector>
#include <string.h>

Simbolo::Simbolo(std::string nome){
    this->nome=nome;
}

std::string Simbolo::getNome(){
    return this->nome;
}
std::string Simbolo::getTipo(){
    return this->tipo;
}

std::string Simbolo::getParametro(){
    return this->parametro;
}

void Simbolo::setNome(std::string nome){
    this->nome=nome;
}

void Simbolo::sedtTipo(std::string tipo){
    this->tipo=tipo;
}

void Simbolo::setParametro(std::string param){
    this->parametro=param;
}
void Simbolo::print(){
    std::cout<<this->getNome()<< " " << this->getParametro() << std::endl;
}

int procuraSimbolo(std::vector<Simbolo> &simbs,std::string nome){
    Simbolo sm("te");
    for( int i=0; i < simbs.size(); i++){
        sm=simbs.at(i);
        if(sm.getNome().compare(nome)==0) return 1;
    }

    return 0;
}
int possuifuncao(std::vector<Simbolo> &simbs,std::string nome){
//    Simbolo sm("");
    for( int i=0; i < simbs.size(); i++){
        //        sm=simbs.at(i);
        if(simbs.at(i).getNome().compare(nome)==0){
            if(simbs.at(i).getParametro().compare(""))
            return 1;
        }
    }
    return 0;
}
void Simbolo::listarParametro(){
    std::cout<<this->getParametro() <<std::endl;
}

void listarSimbolos(std::vector<Simbolo> &simbs){
    std::cout<<"variaveis declaradas"<<std::endl;
    for( int i=0; i < simbs.size(); i++){
        simbs.at(i).print();
    }
}
