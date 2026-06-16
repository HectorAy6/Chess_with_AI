#ifndef MYQWIDGET_HH
#define MYQWIDGET_HH

#include <QWidget>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

#include "Header/Tablero.hh"


class MyQWidget:public QWidget{
    Q_OBJECT

    public:
        MyQWidget(QWidget *parent);
        void pintar_tablero();
        void pintar_coronacion(Pos p);
    
    private:
        Tablero t;
        bool partida_acabada=false, coronando, turno_stockfish, stockfish_activado;
        std::vector<std::string> movimientos;

        std::string mov(Pos orig, Pos nueva);
        QProcess *stockfish;

        void mandar_comando_stock();

    public slots:
        void recivir_Pos(char f, int c, bool stock);
        void restart();
        void leer_datos_stockfish();
        void activar_persona();
        void activar_stockfish();

    signals:
        void enviar_color(char f, int c, QColor col);
        void enviar_imatge(char f, int c, QPixmap &i);

};
#endif