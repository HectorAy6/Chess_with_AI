#include "Pieza.hh"
#include "Tablero.hh"

Pieza::Pieza(bool blanca){
    color = blanca;
}

Pieza::Pieza(Pieza *p2){
    color = p2->color;
}

Pieza::Pieza(){
    color = true;
}

char Pieza::print_pieza(){
    if(color==BLANCA) std::cout<<"\033[7m";
    else std::cout<<"\033[34m";
    return print();
}