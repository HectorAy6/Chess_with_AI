#include "../Header/Structs_y_Funciones.hh"

int  size_tablero = 8;

std::ostream& operator<<(std::ostream& os, const Pos& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

std::istream& operator>>(std::istream& os, Pos& p) {
    os >> p.x >> p.y;
    return os;
}

bool pos_aceptable(int x, int y){
    return x>-1 and x<size_tablero and y>-1 and y<size_tablero;
}