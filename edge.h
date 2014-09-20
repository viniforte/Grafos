#ifndef EDGE_H
#define EDGE_H

#include <QDebug>
#include <QPainter>
#include <QColor>

class Edge : public QObject {
    Q_OBJECT

public:
    Edge ( int , int, int, QColor, QObject *parent=0 );
    ~Edge();

    static Edge* clone ( Edge * );
    static void  append ( Edge **, int, int, int, QColor color );
    static Edge* removeLeast ( Edge **, Edge *m=0 );

    int    getW ();
    int    getId();
    int    getIdAdj();
    QColor getColor();
    Edge   *getNext();


    void setColor ( QColor );
    void paint( QPoint p1, QPoint p2, QPainter & );

private:    
    int    id;
    int    idAdj;
    int    w;
    QColor color;
    Edge   *next;
};

#endif // EDGE_H
