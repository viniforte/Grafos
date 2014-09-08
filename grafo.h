#ifndef GRAFO_H
#define GRAFO_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QColor>

#include "vertice.h"

#define INFINITO 100000

class Grafo : public QObject {
    Q_OBJECT

public:
    Grafo ( int n, QObject *parent ) : QObject(parent)  {
        aresta      = NULL;
        this->max   = n;
        this->size  = 0;
        vertice     = new Vertice*[max];
        for (int i=0; i<max; i++)
            vertice[i] = NULL;

    }

    void add ( QString nome, int x, int y ) {
        if (size<max) {
            qDebug() << "Adicionando vertice " << nome;
            vertice[size] = new Vertice(size, nome.toUpper(), x, y);
            size++;
        } else
            qDebug() << "Número de vertices maior que o informado!";
    }

    bool addAresta ( QString source, QString target, int w ) {
        int s = getVerticeIndex(source);
        int t = getVerticeIndex(target);
        if ((s==-1) || (t==-1)) {
            qDebug() << "Vertice de [origem|destino] não encontrado: " << source << ", " << target;
            return false;
        }
        Aresta::append( &aresta, s, t, w );
        vertice[s]->add( s, t, w);
        return true;
    }

    Vertice **getVertice ()    { return this->vertice; }
    int     getVerticeCount()  { return this->size; }

    ~Grafo ( ) {
        qDebug() << "Eliminando o grafo";
        for (int i=0; i<size; i++)
            delete vertice[i];
        delete [] vertice;
    }

    //depth first search
    void dfs () {

        int n = this->getVerticeCount();
        for ( int i = 0; i < n; i++ ) {
            this->vertice[i]->setParent(NULL);
            this->vertice[i]->setTempoEntrada(INFINITO);
            this->vertice[i]->setTempoSaida(INFINITO);
            this->vertice[i]->setCor(Qt::white);
        }

        //MOSTRAR

        this->tempo = 0;
        for ( int i = 0; i < n; i++ ){
            if (this->vertice[i]->getCor() == Qt::white ) {
                Visit(this->vertice[i]);
            }
        }
    }

    void Visit ( Vertice *vertice ) {
        vertice->setCor(Qt::yellow);
        Vertice *VA;
        vertice->setTempoEntrada(this->tempo++);
        Aresta *aresta = vertice->getAresta();
        for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
            VA = this->vertice[aresta->getIdV2()];
            if ( VA->getCor() == Qt::white ) {
                VA->setParent(vertice);
                Visit(VA);
            }
        }
        vertice->setTempoSaida(this->tempo++);
        vertice->setCor(Qt::red);
    }

    //TOPOLOGICA
    /*void dfsOrdenacaoTopologica ( Lista **lista ) {
        *lista = new Lista();
        for ( int i = 0; i < n; i++ ) {
            this->vertice[i]->setParent(NULL);
            this->vertice[i]->setTempoEntrada(INFINITO);
            this->vertice[i]->setTempoSaida(INFINITO);
            this->vertice[i]->setCor(Qt::white);
        }

        //MOSTRAR

        this->tempo = 0;
        for ( int i = 0; i < n; i++ ){
            if (this->vertice[i]->getCor() == Qt::white ) {
                Visit(this->vertice[i], *lista );
            }
        }
    }

    void VisitOrdenacaoTopologica ( Vertice *vertice, Lista *lista ) {
        vertice->setCor(Qt::yellow);
        Vertice *VA;
        vertice->setTempoEntrada(this->tempo++);
        Aresta *aresta = vertice->getAresta();
        for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
            VA = vertice[aresta->getIdV2()];
            if ( VA->getCor() == Qt::white ) {
                VA->setParent(vertice);
                VisitOrdenacaoTopologica(VA, lista);
            }
        }
        vertice->setTempoSaida(this->tempo++);
        vertice->setCor(Qt::red);
        //MOSTRAR
    }*/

    /*void bfs(){
        Lista lista = new Lista();
        Vertice *verticeAtual;
        Aresta *arestta;
        int i;
        for ( i = 1; i <size; i++ ) {
            vertice[i]->setParent(NULL);
            vertice[i]->setCor(Qt::white);
            vertice[i]->setDistancia(INFINITO);
        }
        vertice[0]->setParent(NULL);
        vertice[0]->setDistancia(0);
        vertice[0]->setCor(Qt::gray);
        lista->appendVertice(vertice[0]);
        while (!lista->isEmpty() ) {
            vertice->lista->removeInicio();
            for ( aresta = vertice[i]->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                verticeAtual = aresta->getIdV2();
                if ( verticeAtual->getCor() == Qt::white ) {
                    verticeAtual->setCor(Qt::red);
                    verticeAtual->setParent(vertice);
                    //verticeAtual->setDistancia(vertice->get );
                    //lista->appendVertice(
                }
            }
            vertice[i]->setCor(Qt::black);
        }
        //delete lista;
    }*/

    /*void Dijkstra ( int Vi ) {
        Vertice *v,*verticeAtual;
        Aresta *aresta;
        Lista *lista = new Lista();
        for ( int i = 0; i < size; i++ ){
            vertice[i]->setCor(Qt::white);
            vertice[i]->setParent(NULL);
            vertice[i]->setDistancia(INFINITO);
        }
        vertice[Vi]->setCor(Qt::yellow);
        vertice[Vi]->setDistancia(0);
        lista->append(vertice[Vi]);
        while ( !lista->isEmpty() ) {
            v = lista->removeMenorVertice();
            v->setCor(Qt::red);
            for ( aresta = v->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                verticeAtual = vertice[aresta->getIdV2()];
                if ( v->getDistancia() + aresta->getW() < verticeAtual->getDistancia() ) {
                    verticeAtual->setDistancia( v->getDistancia() + aresta->getW() );
                    verticeAtual->setParent(v);
                }
                if ( verticeAtual->getCor() ==  Qt::white ) {
                    verticeAtual->setCor(Qt::yellow);
                    lista->append(verticeAtual);
                }
            }
        }
        delete lista;
    }

    void Prim ( int indexVi ) {
        Vertice *v, *verticeAtual;
        Aresta * aresta;
        Lista *lista = new Lista();
        for ( int i = 0; i < n_aresta; i++ ) {
            vertice[i]->setDistancia(INFINITO);
            vertice[i]->setCor(Qt::white);
            vertice[i]->setParent(NULL);
            lista->append(vertice[i]);
        }
        vertice[indexVi]->setDistancia(0);
        while ( !lista->isEmpty() ) {
            v = lista->removeMenorVertice();
            v->setCor(Qt::yellow);
            for ( aresta = v->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                verticeAtual = vertice[aresta->getIdV2()];
                if ( (verticeAtual->getCor() != Qt::red) && (verticeAtual->getDistancia() > aresta->getW()) ) {
                    verticeAtual->setParent(v);
                    verticeAtual->setDistancia(aresta->getW());
                }
            }
            v->setCor(Qt::red);
        }
        delete lista;
    }*/


protected:
    Vertice **vertice;
    Aresta *aresta;
    int max;
    int size;
    int tempo;

    int getVerticeIndex ( QString nome ) {
        for (int i=0; i<size; i++)
            if ((vertice[i]!=NULL) && (vertice[i]->getNome()==nome.toUpper()))
                return i;
        return -1;
    }


};



#endif // GRAFO_H
