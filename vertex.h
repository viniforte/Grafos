#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include <QPainter>

#include "edge.h"

class Vertex : public QObject {
    Q_OBJECT

public:
    Vertex ( int, QString, QPoint, QObject *parent=0 );
     ~Vertex();

    QString getSET ();
    int     getId  ();
    QString getName ();
    QColor  getColor();
    Edge    *getEdges ();
    Vertex  *getFather();
    int     getD ();
    int     getTi ();
    int     getTo ();
    QPoint  getPoint ();
    //int     getY ();

    void setSET ( QString );
    void append ( int, int, QColor color );
    void setFather ( Vertex * );
    void setD ( int );
    void setTi ( int  );
    void setTo ( int  );
    void setColor ( QColor  ) ;

    Vertex *clone ();
    void paint ( QPainter & );

protected:
    QString name;
    int id;         // Index do vértice no vetor
    int d;          // tempo de entrada | distância | peso
    int t;          // tempo de saida
    Vertex *father; // pai do vértice
    QColor  color;  // cor do vértice

    QString set;

    Edge   *edges;

    QPoint p;
    int x;  // coordenada para desenho
    int y;  // coordenada para desenho
};

#endif // VERTEX_H
