#ifndef ARESTA_H
#define ARESTA_H

#include <QDebug>

class Aresta : public QObject {
    Q_OBJECT

public:
    Aresta ( int id1, int id2, int w ) {
        this->id1  = id1; // origem
        this->id2  = id2; // destino
        this->w    = w;
        this->next = NULL;
        this->fluxo = w;
    }

   /* void Append ( int id1, int id2, int w ) {
        if (this->next==NULL) {
            qDebug() << "Incluindo aresta (" << id1 <<","<< id2 <<"," << w << ")";
            this->next = new Aresta ( id1, id2, w);
        } else
            this->next->Append( id1, id2, w);
    }*/

    static void append ( Aresta **aresta, int id1, int id2, int w ) {
        if (*aresta==NULL)
            *aresta = new Aresta ( id1, id2, w);
        else
            append( &(*aresta)->next, id1, id2, w );
    }

    int getW ()  { return this->w;   }
    int getIdV1() { return this->id1; }
    int getIdV2() { return this->id2; }
    int getFluxo() { return this->fluxo; }

    void setFluxo( int fluxo ) { this->fluxo = fluxo; }

    Aresta *getNext() { return this->next;         }


    ~Aresta() {
        qDebug() << "Excluindo aresta (" << id1 <<","<<id2<<"," << w << ")";
        if (this->next!=NULL)
            delete this->next;
    }

protected:
  //  Aresta *next;

private:
    Aresta *next;
    int id1;
    int id2;
    int w;
    int fluxo;

};

#endif // ARESTA_H
