#ifndef VERTICE_H
#define VERTICE_H

#include <QObject>
#include <QDebug>
#include <QColor>

#include "Aresta.h"

class Vertice : public QObject {
    Q_OBJECT

public:
    Vertice ( int id, QString nome, int x, int y ) {
        this->id     = id;
        this->nome   = nome;
        this->x      = x;
        this->y      = y;

        this->tempoEntrada    = 0;
        this->tempoSaida     = 0;
        this->distancia      = 0;
        this->n_a    = 0;
        this->cor    = Qt::white;
        this->aresta = NULL;

    }

    void add ( int id1, int id2, int w ) { Aresta::append( &aresta, id1, id2, w ); }
    Aresta *getAresta ()                 { return this->aresta; }
    QString getNome ()                   { return this->nome; }
    int     getX ()                      { return this->x;    }
    int     getY ()                      { return this->y;    }
    QColor  getCor ()                    { return this->cor;  }
    int getDistancia()                   { return this->distancia; }

    void setPai(Vertice *pai) { this->pai = pai; }
    Vertice* getPai (){return this->pai;}
    void setCor(QColor cor)  { this->cor = cor; }
    void setTempoEntrada( int  tempoEntrada ) { this->tempoEntrada = tempoEntrada; }
    void setTempoSaida( int  tempoSaida ) { this->tempoSaida = tempoSaida; }
    void setDistancia( int distancia ) { this->distancia = distancia; }

    ~Vertice() {
        qDebug() << "Excluindo vertice " << nome;
        if (this->aresta!=NULL)
            delete this->aresta;
    };

protected:
    int id; // Index do vértice no vetor
    QString nome;
    int tempoEntrada; // tempo de entrada
    int tempoSaida; // tempo de saida
    int distancia;  // distância
    int n_a; // número de arestas
    QColor cor; // cor do vértice
    Aresta *aresta;
    Vertice *pai;

    int x;
    int y;

};

#endif // VERTICE_H
