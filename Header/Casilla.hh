#ifndef CASILLA_HH
#define CASILLA_HH

#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include "Header/MyQWidget.hh"

class Casilla: public QLabel{
    Q_OBJECT
    Q_PROPERTY(char fila READ readFila WRITE setFila DESIGNABLE true)
    Q_PROPERTY(int columna READ readColumna WRITE setColumna DESIGNABLE true)

    public:
        Casilla(QWidget *parent );
        char readFila(){ return fi;}
        int readColumna(){return co;}

        void setFila(char c){fi = c;}
        void setColumna(int c) {co = c;}
        void setControl(MyQWidget *w){
            connect(this, &Casilla::click, w, &MyQWidget::recivir_Pos);
            connect(w, &MyQWidget::enviar_color, this, &Casilla::color_fondo);
            connect(w, &MyQWidget::enviar_imatge, this, &Casilla::imagen_pieza);
        }

    private:
        char fi;
        int co;

        void mouseReleaseEvent (QMouseEvent *e);

    signals:
        void click(char f, int c);

    public slots:
        void color_fondo(char f, int c ,QColor col);
        void imagen_pieza(char f, int c ,QPixmap &i);

};

#endif