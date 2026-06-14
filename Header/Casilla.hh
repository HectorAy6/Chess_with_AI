#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>

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

    private:
        char fi;
        int co;

        void mouseReleaseEvent (QMouseEvent *e);

    signals:
        void click(char f, int c);
};