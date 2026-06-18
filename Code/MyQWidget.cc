#include "../Header/MyQWidget.hh"

MyQWidget::MyQWidget(QWidget *parent):QWidget(parent){
    restart();
    // Dentro de tu clase:
    stockfish = new QProcess(this);
    stockfish->start("./Stockfish/stockfish");
    // Leer la respuesta de forma asíncrona (sin bloquear la interfaz)
    connect(stockfish, &QProcess::readyReadStandardOutput, this, &MyQWidget::leer_datos_stockfish);
}

void MyQWidget::recivir_Pos(char f, int c, bool stock){
    if(stockfish_activado and turno_stockfish and !stock) return;
    if(partida_acabada) return;
    int res = t.enviar_pos(f, c);
    if(res == POS_NO_VALIDA) return;
    if(res == TABLAS or res == JAQUE_MATE_B or res == JAQUE_MATE_N or res == RENDIRSE){
        partida_acabada = true;
        pintar_tablero();
        t.actualizar_posiciones();
        Pos p1 = t.get_pieza_sel(), p2 = t.get_pieza_nueva();
        movimientos.push_back(mov(p1,p2));
        if(!creando) movimientos_antes_retroceso.clear();
        if(res == JAQUE_MATE_B){
            QMessageBox::information(this, "Fin de la partida", "Jaque mate. Ganan las blancas.");
        } else if(res == TABLAS){
            QMessageBox::information(this, "Fin de la partida", "Tablas.");
        } else if(res == RENDIRSE){
            QMessageBox::information(this, "Fin de la partida", "Se ha rendido. Ganan las .");
        }if(res == JAQUE_MATE_N){
            QMessageBox::information(this, "Fin de la partida", "Jaque mate. Ganan las negras.");
        }
        return;
    }
    if(res == SIGUIENTE_RONDA){
        t.cambio_equipo();
        t.actualizar_posiciones();
        Pos p1 = t.get_pieza_sel(), p2 = t.get_pieza_nueva();
        movimientos.push_back(mov(p1,p2));
        if(!creando) movimientos_antes_retroceso.clear();
        if(coronando){
            movimientos[movimientos.size()-1].push_back(t.print_pieza(p2.x, p2.y));
        }
        coronando = false;
        turno_stockfish = !turno_stockfish;
        if(turno_stockfish and stockfish_activado) mandar_comando_stock();
    }
    if(res==CORONACION){
        Pos p;
        coronando = true;
        if(f>'H') p.y = f- 'a';
        else p.y = f-'A';

        p.x = 8-c;
        pintar_coronacion(p);
    }else {
        pintar_tablero();
    }

}

void MyQWidget::pintar_tablero(){
    std::set<Pos> movimientos_pos, antigua_pos; 
    t.get_movimientos_pos(movimientos_pos);
    Pos pieza_sel = t.get_pieza_sel();
    t.get_antiguasPos(antigua_pos);
    bool hay_pieza_sel = t.get_hay_pieza_sel();

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            QColor col;
            if(i%2==j%2) {
                col = QColor(91, 57, 13);
            }else{
                col = QColor(238, 212, 114);
            }
            if(antigua_pos.find(Pos(i,j))!=antigua_pos.end()){
                col = QColor(0,255,0);
            }
            if(movimientos_pos.find(Pos(i,j))!=movimientos_pos.end()){
                col = QColor(255,0,0);
            }else if(Pos(i,j)==pieza_sel and hay_pieza_sel){
                col = QColor(0,0,255);
            }
            emit enviar_color(char('a'+j), 8-i, col);
            emit enviar_imatge(char('a'+j), 8-i, t.get_image(i,j));
        }
    }
}

void MyQWidget::pintar_coronacion(Pos p){
    std::set<Pos> movimientos_pos, antigua_pos; 
    t.get_movimientos_pos(movimientos_pos);
    Pos pieza_sel = t.get_pieza_sel();
    t.get_antiguasPos(antigua_pos);

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            QColor col;
            if(i%2==j%2) {
                col = QColor(91, 57, 13);
            }else{
                col = QColor(238, 212, 114);
            }
            if(antigua_pos.find(Pos(i,j))!=antigua_pos.end()){
                col = QColor(0,255,0);
            }
            if(j==p.y and abs(i-p.x)<4){
                col = QColor(255,255,255);
                QPixmap ima(":");
                bool e = t.get_equipo();
                if(abs(i-p.x)==0){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Dama_B.png");
                    else ima = QPixmap(":Images/Images/Dama_N.png");
                }
                else if(abs(i-p.x)==1){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Torre_B.png");
                    else ima = QPixmap(":Images/Images/Torre_N.png");
                }else if(abs(i-p.x)==2){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Caballo_B.png");
                    else ima = QPixmap(":Images/Images/Caballo_N.png");
                }else if(abs(i-p.x)==3){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Alfil_B.png");
                    else ima = QPixmap(":Images/Images/Alfil_N.png");
                }
                emit enviar_imatge(char('a'+j), 8-i, ima);
            }else if (Pos(i,j)!=pieza_sel){
                emit enviar_imatge(char('a'+j), 8-i, t.get_image(i,j));
            }else {
                emit enviar_imatge(char('a'+j), 8-i, t.get_image(-1,j));
            }
            emit enviar_color(char('a'+j), 8-i, col);
            
        }
    }
}

void MyQWidget::restart(){
    t.reset();
    partida_acabada = false;
    pintar_tablero();
    movimientos.clear();
    coronando = false;
    turno_stockfish = false;
    stockfish_activado = false;
    emit reset();
    creando = false;
}

std::string MyQWidget::mov(Pos orig, Pos nueva){
    char res[100];
    sprintf(res, "%c%d%c%d", orig.y+'a', 8-orig.x,  nueva.y+'a', 8-nueva.x);
    return res;
}

void MyQWidget::leer_datos_stockfish(){
    char buf[1024];
    std::string s, clave("bestmove"), movimiento_stock;
    while(stockfish->readLine(buf, sizeof(buf))>0){
        s = std::string(buf);
        if(s.find(clave)!=std::string::npos){
            movimiento_stock = s.substr(9,5);
            recivir_Pos(movimiento_stock[0], movimiento_stock[1]-'0', true);
            recivir_Pos(movimiento_stock[2], movimiento_stock[3]-'0', true);
            if(movimiento_stock[4]!=' '){
                int mov = movimiento_stock[3]-movimiento_stock[1];
                if(movimiento_stock[4]=='q')recivir_Pos(movimiento_stock[2], movimiento_stock[3]-'0', true);
                else if (movimiento_stock[4]=='r' ) recivir_Pos(movimiento_stock[2], movimiento_stock[3]-'0'-mov, true);
                else if (movimiento_stock[4]=='n' ) recivir_Pos(movimiento_stock[2], movimiento_stock[3]-'0'-2*mov, true);
                else if (movimiento_stock[4]=='b' ) recivir_Pos(movimiento_stock[2], movimiento_stock[3]-'0'-3*mov, true);
            }
            
        }

    }

   
    
}

void MyQWidget::mandar_comando_stock(){
    std::string posicion("position startpos moves");
    for(auto s:movimientos) {
        posicion.push_back(' ');
        posicion.append(s);
    }
    posicion.push_back('\n');
    stockfish->write(posicion.c_str());
    stockfish->write("go movetime 200\n");
}

void MyQWidget::activar_persona(){
    stockfish_activado = false;
}

void MyQWidget::activar_stockfish(){
    stockfish_activado = true;
    turno_stockfish = false;
}

void MyQWidget::retroceder_jugada(){
    if(movimientos.empty()) return;
    movimientos_antes_retroceso.push_back(movimientos.back());
    movimientos.pop_back();
    if(!movimientos.empty() and stockfish_activado){
        movimientos_antes_retroceso.push_back(movimientos.back());
        movimientos.pop_back();
    };
    bool sa = stockfish_activado;
    std::vector<std::string> aux = movimientos;
    restart();
    creando = true;
    for(auto s:aux) {
        recivir_Pos(s[0], s[1]-'0', false);
        recivir_Pos(s[2], s[3]-'0', false);
        if(s.size()>4){
            int mov = s[3]-s[1];
            if(s[4]=='q')recivir_Pos(s[2], s[3]-'0', false);
            else if (s[4]=='r' ) recivir_Pos(s[2], s[3]-'0'-mov, false);
            else if (s[4]=='n' ) recivir_Pos(s[2], s[3]-'0'-2*mov, false);
            else if (s[4]=='b' ) recivir_Pos(s[2], s[3]-'0'-3*mov, false);
        }
    }
    creando = false;
    stockfish_activado = sa;
    if(sa) emit enviar_stockfish();

}

void MyQWidget::adelantar_jugada(){
    if(movimientos_antes_retroceso.empty()) return;
    std::string s = movimientos_antes_retroceso.back();
    creando = true;
    recivir_Pos(s[0], s[1]-'0', true);
    recivir_Pos(s[2], s[3]-'0', true);
    if(s.size()>4){
        int mov = s[3]-s[1];
        if(s[4]=='q')recivir_Pos(s[2], s[3]-'0', true);
        else if (s[4]=='r' ) recivir_Pos(s[2], s[3]-'0'-mov, true);
        else if (s[4]=='n' ) recivir_Pos(s[2], s[3]-'0'-2*mov, true);
        else if (s[4]=='b' ) recivir_Pos(s[2], s[3]-'0'-3*mov, true);
    }
    movimientos_antes_retroceso.pop_back();
    if(stockfish_activado){
        s = movimientos_antes_retroceso.back();
        recivir_Pos(s[0], s[1]-'0', true);
        recivir_Pos(s[2], s[3]-'0', true);
        if(s.size()>4){
            int mov = s[3]-s[1];
            if(s[4]=='q')recivir_Pos(s[2], s[3]-'0', true);
            else if (s[4]=='r' ) recivir_Pos(s[2], s[3]-'0'-mov, true);
            else if (s[4]=='n' ) recivir_Pos(s[2], s[3]-'0'-2*mov, true);
            else if (s[4]=='b' ) recivir_Pos(s[2], s[3]-'0'-3*mov, true);
        }
        movimientos_antes_retroceso.pop_back();
    }

    creando = false;
}