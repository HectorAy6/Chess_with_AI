#include "Tablero.hh"

Tablero::Tablero(){

    for (auto& fila : tablero_piezas) {
        fila.resize(size_tablero); // Crea los unique_ptr apuntando a nullptr por defecto
    }

    reset();
    
}

void Tablero::print(){
    std::cout << "  A B C D E F G H" << std::endl;
    for(int i=0; i<size_tablero; i++){
        std::cout << 8-i;
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]==nullptr){
                std::cout << " .";
            }else{
                std::cout << " " << tablero_piezas[i][j]->print_pieza() << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl << std::endl;
}

bool Tablero::movimiento(bool equipo){

    Pos pos_original, nueva_pos;
    bool acceptable = false;
    std::set<Pos> Movimientos_pos;
    
    while (!acceptable)
    {
        std::cout << "Elige pieza para mover:";
        
        demanarPos(pos_original.x, pos_original.y);

        if(pos_aceptable(pos_original.x, pos_original.y)){
            if(tablero_piezas[pos_original.x][pos_original.y]==nullptr) std::cout << "La posicion no esta ocupada" << std::endl;
            else if(tablero_piezas[pos_original.x][pos_original.y]->equipo()!=equipo) std::cout << "La posicion esta ocupada por pieza rival" << std::endl;
            else {
                tablero_piezas[pos_original.x][pos_original.y]->obtener_movimientos_posibles(Movimientos_pos, pos_original, this);
                if(Movimientos_pos.size()==0) std::cout << "La pieza no tiene movimientos validos" << std::endl;
                else acceptable = true;
            }
        }else std::cout << "La posicion no existeix" << std::endl;
        
    }
    
    acceptable = false;

    while (!acceptable)
    {
        std::cout << "Elige posicio a donde mover:";
        
        demanarPos(nueva_pos.x, nueva_pos.y);
        if(Movimientos_pos.find(nueva_pos)==Movimientos_pos.end()) std::cout << "La pieza no sepuede mover ahi" << std::endl;
        else acceptable = true;
        
    }

    std::shared_ptr<Pieza> p = tablero_piezas[pos_original.x][pos_original.y];
    tablero_piezas[pos_original.x][pos_original.y] = nullptr;
    bool rei_matado = false;
    if(tablero_piezas[nueva_pos.x][nueva_pos.y]!=nullptr and tablero_piezas[nueva_pos.x][nueva_pos.y]->tipo_de_pieza()==REI)  rei_matado = true;
    tablero_piezas[nueva_pos.x][nueva_pos.y] = p;
    return rei_matado;

}

void Tablero::jugar_partida(){
    bool acabado = false;
    bool equipo = BLANCA;
    
    print();

    while(!acabado){
        acabado = movimiento(equipo);
        print();

        equipo= !equipo;
    }
    if(equipo==BLANCA) std::cout << "GANADOR NEGRO";
    else std::cout << "GANADOR BLANCO";

    std::cout << std::endl;
}

void Tablero::reset(){

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            tablero_piezas[i][j]=nullptr;
        }
    }
    //Piezas blancas
    tablero_piezas[7][1] = std::make_shared<Caballo>(BLANCA);
    tablero_piezas[7][6] = std::make_shared<Caballo>(BLANCA);
    tablero_piezas[7][4] = std::make_shared<Rei>(BLANCA);
    tablero_piezas[7][3] = std::make_shared<Dama>(BLANCA);
    tablero_piezas[7][0] = std::make_shared<Torre>(BLANCA);
    tablero_piezas[7][7] = std::make_shared<Torre>(BLANCA);
    tablero_piezas[7][2] = std::make_shared<Alfil>(BLANCA);
    tablero_piezas[7][5] = std::make_shared<Alfil>(BLANCA);
    for(int i = 0; i<size_tablero; i++){
        tablero_piezas[6][i] = std::make_shared<Peon>(BLANCA, this);
    }

    //Piezas Negras
    tablero_piezas[0][1] = std::make_shared<Caballo>(NEGRA);
    tablero_piezas[0][6] = std::make_shared<Caballo>(NEGRA);
    tablero_piezas[0][4] = std::make_shared<Rei>(NEGRA);
    tablero_piezas[0][3] = std::make_shared<Dama>(NEGRA);
    tablero_piezas[0][0] = std::make_shared<Torre>(NEGRA);
    tablero_piezas[0][7] = std::make_shared<Torre>(NEGRA);
    tablero_piezas[0][2] = std::make_shared<Alfil>(NEGRA);
    tablero_piezas[0][5] = std::make_shared<Alfil>(NEGRA);
    for(int i = 0; i<size_tablero; i++){
        tablero_piezas[1][i] = std::make_shared<Peon>(NEGRA, this);
    }
}

void Tablero::demanarPos(int &fila, int &columna){

    char columna_letra;

    while (!(std::cin >> columna_letra >> fila)) {
        std::cout << "Entrada invalida. Introduce una letra y un numero: " << std::endl;
        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }

    if(columna_letra>'H') columna = columna_letra- 'a';
    else columna = columna_letra-'A';

    fila = 8-fila;
}