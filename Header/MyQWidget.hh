#ifndef MYQWIDGET_HH
#define MYQWIDGET_HH

#include <QWidget>
#include <QMessageBox>
#include "Header/Tablero.hh"

class MyQWidget:public QWidget{
    Q_OBJECT

    public:
        MyQWidget(QWidget *parent);
        void pintar_tablero();
        void pintar_coronacion(Pos p);
    
    private:
        Tablero t;
        bool partida_acabada=false;
    public slots:
        void recivir_Pos(char f, int c);
        void restart();
    signals:
        void enviar_color(char f, int c, QColor col);
        void enviar_imatge(char f, int c, QPixmap &i);

};
#endif