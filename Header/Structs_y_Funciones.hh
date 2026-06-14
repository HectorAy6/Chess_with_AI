#if !defined(STRUCTS_F_HH)
#define STRUCTS_F_HH

#include <iostream>

extern int  size_tablero;
#define BLANCA true
#define NEGRA false
#define PEON 0
#define TORRE 1
#define CABALLO 2
#define ALFIL 3
#define REI 4
#define DAMA 5

struct Pos {
    int x, y;

    Pos(const int p1,const  int p2){
        x=p1;
        y=p2;
    }
    
    Pos(const Pos &p2){
        x = p2.x;
        y = p2.y;
    }

    Pos():x(0),y(0){}

    bool operator<(const Pos &p) const{
        if(x==p.x) return y<p.y;
        return x<p.x;
    }

    bool operator>(const Pos &p)const {
        if(x==p.x) return y>p.y;
        return x>p.x;
    }

    bool operator==(const Pos &p)const {
        return y==p.y and x==p.x;
    }

    bool operator!=(const Pos &p)const {
        return y!=p.y or x!=p.x;
    }

    Pos operator+(const Pos &p)const {
        return Pos(x+p.x, y+p.y);
    }
    
    Pos operator-(const Pos &p)const {
        return Pos(x-p.x, y-p.y);
    }

    Pos operator=(const Pos &p){
        x=p.x;
        y=p.y;
        return p;
    }

};

std::ostream& operator<<(std::ostream& os, const Pos& p);
std::istream& operator>>(std::istream& os,  Pos& p);

bool pos_aceptable(int x, int y);

#endif // MACRO


