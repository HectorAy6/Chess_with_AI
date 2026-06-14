#include <QWidget>
#include "Header/Tablero.hh"

class MyQWidget:public QWidget{
    Q_OBJECT

    public:
        MyQWidget(QWidget *parent);
    
    private:
        Tablero t;
    
    public slots:
        //void recivir_Pos(int x, int y);

};