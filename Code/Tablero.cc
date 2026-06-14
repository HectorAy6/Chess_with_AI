#include "../Header/Tablero.hh"

Tablero::Tablero(){

    for (auto& fila : tablero_piezas) {
        fila.resize(size_tablero); // Crea los unique_ptr apuntando a nullptr por defecto
    }

    reset();
    
}

void Tablero::print(){
    std::cout << "  A B C D E F G H" << std::endl;
    for(int i=0; i<size_tablero; i++){
        std::cout << size_tablero-i;
        for(int j=0; j<size_tablero; j++){
            if(!piezaSeleccionada){
                if(tablero_piezas[i][j]==nullptr){
                    std::cout << " .";
                }else{
                    std::cout << " " << tablero_piezas[i][j]->print_pieza() << "\033[0m";
                }
            }else{
                if(tablero_piezas[i][j]==nullptr){
                    if(Movimientos_pieza_seleccionada.find(Pos(i,j))==Movimientos_pieza_seleccionada.end()) std::cout << " .";
                    else std::cout << " *";
                }else{
                    if(Movimientos_pieza_seleccionada.find(Pos(i,j))==Movimientos_pieza_seleccionada.end()) std::cout << " " << tablero_piezas[i][j]->print_pieza() << "\033[0m";
                    else std::cout << " " << tablero_piezas[i][j]->print_pieza_seleccionada() << "\033[0m";
                } 
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl << std::endl;
}

int Tablero::movimiento(bool equipo){

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(ocupado_equipo(Pos(i,j), equipo)) tablero_piezas[i][j]->desactivar_doble_movimiento();
        }
    }

    while (!pedirComanda(equipo));

    if(!piezaSeleccionada) return RENDIRSE;

    if(tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y]!=nullptr) movimientos_sin_accion=0;
    else movimientos_sin_accion ++;

    if(posicion_pieza_actual==Rei_blanco) Rei_blanco = nueva_posicion_pieza;
    else if (posicion_pieza_actual==Rei_negro) Rei_negro = nueva_posicion_pieza;

    if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->tipo_de_pieza()==REI){
        Pos mov = nueva_posicion_pieza-posicion_pieza_actual;
        if(abs(mov.y)==2){
            if(mov.y<0){
                tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y+1] = tablero_piezas[posicion_pieza_actual.x][0];
                tablero_piezas[posicion_pieza_actual.x][0] = nullptr;
            }else{
                tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y-1] = tablero_piezas[posicion_pieza_actual.x][size_tablero-1];
                tablero_piezas[posicion_pieza_actual.x][size_tablero-1] = nullptr;
            }
        }
    }

    if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->tipo_de_pieza()==PEON){
        Pos mov = nueva_posicion_pieza-posicion_pieza_actual;
        movimientos_sin_accion = 0;
        if(abs(mov.y)!=0 and tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y]==nullptr){
            if(equipo==BLANCA)tablero_piezas[nueva_posicion_pieza.x+1][nueva_posicion_pieza.y]=nullptr;
            else tablero_piezas[nueva_posicion_pieza.x-1][nueva_posicion_pieza.y]=nullptr;
        }
        else if(nueva_posicion_pieza.x==0 and equipo == BLANCA){
            coronacion();
        }else if(nueva_posicion_pieza.x==size_tablero-1 and equipo == NEGRA){
            coronacion();
        }else if(abs(mov.x)==2) tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->activar_doble_movimiento();
    }

    tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->pieza_movida();

    
    tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y] = tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y];
    tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = nullptr;
    
    contador_posiciones[tablero_piezas]++;
    if(contador_posiciones[tablero_piezas]>=3) return TABLAS;
    if(movimientos_sin_accion==100) return TABLAS;
    if(demasiadas_pocas_piezas()) return TABLAS;
    calculo_Jaque(!equipo);
    if(tiene_movimientos(!equipo)) return SIGUIENTE_RONDA;
    if(hay_jaque(!equipo)) return JAQUE_MATE;
    return TABLAS;

}

void Tablero::jugar_partida(){
    int acabado = SIGUIENTE_RONDA;
    bool equipo = NEGRA;
    
    print();

    while(acabado==SIGUIENTE_RONDA){
        equipo= !equipo;
        acabado = movimiento(equipo);
        piezaSeleccionada = false;
        print();
    }
    if(acabado==TABLAS) std::cout << "TABLAS";
    else if(acabado==RENDIRSE && equipo==BLANCA) std::cout << "BLANCO SE RINDE, GANA NEGRO";
    else if(acabado==RENDIRSE && equipo==NEGRA) std::cout << "NEGRO SE RINDE, GANA BLANCO";
    else if(acabado==JAQUE_MATE && equipo==BLANCA) std::cout << "JAQUE MATE GANADOR BLANCO";
    else if(acabado==JAQUE_MATE && equipo==NEGRA) std::cout << "JAQUE MATE GANADOR NEGRO";

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
        
    Rei_blanco = Pos(7,4);
    Rei_negro = Pos(0,4);

    jaqueBlanco = false;
    jaqueNegro = false;

    movimientos_sin_accion = 0;
    contador_posiciones.clear();
}

bool Tablero::pedirComanda(bool equipo){

    char comando;

    std::cout << "Introducir comando:" << std::endl;
    while (!(std::cin >> comando) || comandos_validos.find(comando)==comandos_validos.end()) {
        std::cout << "Entrada invalida. Introduce una letra para indicar que hacer: " << std::endl;
        std::cout << " 's/S' : seleccionar pieza " << std::endl;
        std::cout << " 'm/M' : mover seleccionada pieza " << std::endl;
        std::cout << " 'd/D' : quitar seleccion pieza " << std::endl;
        std::cout << " 'e/E' : acabar partida " << std::endl;
        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }

    if(comando=='S' || comando == 's'){
        pedirPos(posicion_pieza_actual);
        piezaSeleccionada = false;
        if(pos_aceptable(posicion_pieza_actual.x, posicion_pieza_actual.y)){
            if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]==nullptr) std::cout << "La posicion no esta ocupada" << std::endl;
            else if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo()!=equipo) std::cout << "La posicion esta ocupada por pieza rival" << std::endl;
            else {
                tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->obtener_movimientos_posibles(Movimientos_pieza_seleccionada, posicion_pieza_actual, this);
                if(Movimientos_pieza_seleccionada.size()==0) std::cout << "La pieza no tiene movimientos validos" << std::endl;
                else {
                    std::cout << "Pieza seleccionada con exito" << std::endl;
                    piezaSeleccionada = true;
                    print();
                }
            }
        }else std::cout << "La posicion no existe" << std::endl;
    }else if(comando=='m' || comando == 'M'){
        if(!piezaSeleccionada) {
            std::cout << "No hay ninguna pieza seleccionada" << std::endl;
            return false;
        }
        pedirPos(nueva_posicion_pieza);
        if(Movimientos_pieza_seleccionada.find(nueva_posicion_pieza)==Movimientos_pieza_seleccionada.end()) std::cout << "La pieza no sepuede mover ahi" << std::endl;
        else return true;
    }else if(comando=='d'||comando=='D'){
        piezaSeleccionada = false;
    }else if(comando=='e'|| comando == 'E'){
        piezaSeleccionada = false;
        return true;
    }
    return false;

    
}

void Tablero::pedirPos(Pos &p){
    char columna_letra;
    while (!(std::cin >> columna_letra >> p.x) ) {
        std::cout << "Entrada invalida. Introduce una letra y un numero para indicar posicion pieza" << std::endl;        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }
    if(columna_letra>'H') p.y = columna_letra- 'a';
    else p.y = columna_letra-'A';

    p.x = 8-p.x;
}

void Tablero::calculo_jaque(bool &Jaque,const bool equipo, const Pos rei){
    std::set<Pos> aux;
    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]!=nullptr and tablero_piezas[i][j]->equipo()!=equipo){
                tablero_piezas[i][j]->obtener_casillas_amenaza(aux,Pos(i,j), this);
                Jaque = aux.find(rei)!=aux.end();
                if(Jaque) return;
            }
        }
    }

    Jaque = false;
}

bool Tablero::hay_jaque_eliminar_pieza(Pos p){
    bool equipo = tablero_piezas[p.x][p.y]->equipo();
    bool result  = false;
    std::shared_ptr<Pieza> aux = tablero_piezas[p.x][p.y];
    tablero_piezas[p.x][p.y] = nullptr;
    calculo_Jaque(equipo);
    if(hay_jaque(equipo)){
        result = true;
    }
    tablero_piezas[p.x][p.y] = aux;
    calculo_Jaque(equipo);
    return result;
}

bool Tablero::hay_jaque_mover_pieza(Pos original, Pos nueva){
    bool equipo = tablero_piezas[original.x][original.y]->equipo();
    bool result  = false;
    if(original==Rei_blanco) Rei_blanco = nueva;
    else if(original == Rei_negro) Rei_negro = nueva;
    std::shared_ptr<Pieza> aux = tablero_piezas[nueva.x][nueva.y];
    tablero_piezas[nueva.x][nueva.y] = tablero_piezas[original.x][original.y];
    tablero_piezas[original.x][original.y] = nullptr;
    
    calculo_Jaque(equipo);
    if(hay_jaque(equipo)){
        result = true;
    }
    tablero_piezas[original.x][original.y] = tablero_piezas[nueva.x][nueva.y];
    tablero_piezas[nueva.x][nueva.y] = aux;

    if(nueva==Rei_blanco) Rei_blanco = original;
    else if(nueva == Rei_negro) Rei_negro = original;
    calculo_Jaque(equipo);
    return result;
}

bool Tablero::tiene_movimientos(bool equipo){
    std::set<Pos> result;
    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]!=nullptr and tablero_piezas[i][j]->equipo()==equipo){
                tablero_piezas[i][j]->obtener_movimientos_posibles(result,Pos(i,j), this);
                if(result.size()>0) return true;
            }
        }
    }
    return false;
}

bool Tablero::enroque_derecha(Pos rei){
    Pos aux = rei+ Pos(0, 1), fin = Pos(rei.x, size_tablero-1);
    while(aux!=fin){
        if(tablero_piezas[aux.x][aux.y]!=nullptr) return false;
        aux = aux + Pos(0, 1);
    }
    if(tablero_piezas[aux.x][aux.y]==nullptr) return false;
    if(tablero_piezas[aux.x][aux.y]->equipo() != tablero_piezas[rei.x][rei.y]->equipo()) return false;
    if(tablero_piezas[aux.x][aux.y]->tipo_de_pieza()!=TORRE) return false;
    if(tablero_piezas[aux.x][aux.y]->se_ha_movido()) return false;
    if(hay_jaque_eliminar_pieza(rei)) return false;
    if(hay_jaque_mover_pieza(rei, Pos(rei.x, rei.y+1))) return false;
    if(hay_jaque_mover_pieza(rei, Pos(rei.x, rei.y+2))) return false;

    return true;

}

bool Tablero::enroque_izquierda(Pos rei){
    Pos aux = rei + Pos(0, -1);
    while(aux!=Pos(rei.x, 0)){
        if(tablero_piezas[aux.x][aux.y]!=nullptr) return false;
        aux = aux + Pos(0, -1);
    }
    if(tablero_piezas[aux.x][aux.y]==nullptr) return false;
    if(tablero_piezas[aux.x][aux.y]->equipo() != tablero_piezas[rei.x][rei.y]->equipo()) return false;
    if(tablero_piezas[aux.x][aux.y]->tipo_de_pieza()!=TORRE) return false;
    if(tablero_piezas[aux.x][aux.y]->se_ha_movido()) return false;
    if(hay_jaque_eliminar_pieza(rei)) return false;
    if(hay_jaque_mover_pieza(rei, Pos(rei.x, rei.y-1))) return false;
    if(hay_jaque_mover_pieza(rei, Pos(rei.x, rei.y-2))) return false;

    return true;

}

void Tablero::coronacion(){
    std::cout << "Introduce a la nueva pieza que quieras coronar:" << std::endl;
    char c;
    while(!(std::cin>>c) or piezas_validas.find(c)==piezas_validas.end()){
        std::cout << "Pieza mal seleccionada, para elegir ponga:" << std::endl;
        std::cout << "D/d: Dama" << std::endl;
        std::cout << "C/c Caballo:" << std::endl;
        std::cout << "A/a Alfil:" << std::endl;
        std::cout << "T/t Torre:" << std::endl;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }
    if(c=='d' or c=='D') tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = std::make_shared<Dama>(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo());
    else if(c=='t' or c=='T') tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = std::make_shared<Torre>(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo());
    else if(c=='c' or c=='C') tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = std::make_shared<Caballo>(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo());
    else if(c=='a' or c=='A') tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = std::make_shared<Alfil>(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo());

}

bool Tablero::posiblePeonPasado(Pos p, bool equipo){
    if(tablero_piezas[p.x][p.y]==nullptr) return false;
    if(tablero_piezas[p.x][p.y]->equipo()==equipo) return false;
    if(tablero_piezas[p.x][p.y]->tipo_de_pieza()!=PEON) return false;
    if(!tablero_piezas[p.x][p.y]->tiene_doble_movimiento()) return false;
    return true;
}

bool Tablero::demasiadas_pocas_piezas(){
    std::pair<int, Pos>piezas_blancas(REI, Pos()), piezas_negras(REI,Pos());
    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]!=nullptr and tablero_piezas[i][j]->tipo_de_pieza()!=REI){
                int pieza = tablero_piezas[i][j]->tipo_de_pieza();
                if(pieza==DAMA or pieza==TORRE or pieza==PEON) return false;

                if(tablero_piezas[i][j]->equipo()==BLANCA) {
                    if(piezas_blancas.first!=REI) return false;
                    piezas_blancas = std::pair<int,Pos>(pieza, Pos(i,j));
                }
                else if(tablero_piezas[i][j]->equipo()==NEGRA){ 
                    if(piezas_negras.first!=REI) return false;
                    piezas_negras = std::pair<int,Pos>(pieza, Pos(i,j));
                }
            }
        }   
    }
    if(piezas_blancas.first==REI || piezas_negras.first==REI) return true;
    if(piezas_blancas.first==CABALLO || piezas_negras.first==CABALLO) return false;
    if((piezas_blancas.second.x+ piezas_blancas.second.y)%2==(piezas_negras.second.x+ piezas_negras.second.y)%2) return true;
    return false;
}