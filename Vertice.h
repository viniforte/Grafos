#ifndef VERTICE_H
#define VERTICE_H

#include <QObject>
#include <QDebug>
#include <QColor>
#include <QPainter>

#include "Aresta.h"

class Vertice : public QObject {
    Q_OBJECT

public:
    Vertice ( int, QString, QPoint, QObject *parent=0 );
     ~Vertice();

    QString getSET ();
    int     getIndiceVertice  ();
    QString getNome ();
    QColor  getCor();
    Aresta   *getArestas ();
    Vertice  *getPai();
    int     getPeso ();
    int     getTempoEntrada ();
    int     getTempoSaida ();
    QPoint  getPonto ();
    //int     getY ();

    void setSET ( QString );
    void acrescentar ( int, int, QColor color );
    void setPai ( Vertice * );
    void setPeso ( int );
    void setTempoEntrada ( int  );
    void setTempoSaida ( int  );
    void setCor ( QColor  ) ;

    Vertice *clonar ();
    void pintar ( QPainter & );

protected:
    QString nome;
    int indiceVertice;         // Index do v�rtice no vetor
    int peso;          // tempo de entrada | dist�ncia | peso
    int tempoEntrada; // tempo de entrada
    int tempoSaida;          // tempo de saida
    Vertice *pai; // pai do v�rtice
    QColor  cor;  // cor do v�rtice

    QString set;

    Aresta   *arestas;

    QPoint ponto;
    int cordenadaX;  // coordenada para desenho
    int cordenadaY;  // coordenada para desenho
};

#endif // VERTICE_H
