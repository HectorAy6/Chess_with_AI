#include "Pieza.hh"

Pieza::Pieza(bool blanca){
    pieza_blanca = blanca;
}

Pieza::Pieza(Pieza *p2){
    pieza_blanca = p2->pieza_blanca;
}

Pieza::Pieza(){
    pieza_blanca = true;
}

char Pieza::print_pieza(){
    if(pieza_blanca) std::cout<<"\033[7m";
    else std::cout<<"\033[34m";
    return print();
}