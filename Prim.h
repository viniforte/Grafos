#ifndef PRIM_H
#define PRIM_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"

class Prim : public QThread
{
    Q_OBJECT
    public:
        void setParameters(Grafo * g, int initial, int final) {
            this->grafo = g;
            this->VerticeInitial = initial;
            this->VerticeFinal = final;
        }

        void run() {
            metodoPrim(VerticeInitial);
        }
    private:
        int tempo;
        int VerticeInitial;
        int VerticeFinal;
        Grafo *grafo;
        QList<Vertice *> lista;
    signals:
        void sinalPrim();

    public:

        void metodoPrim( int indexVi ) {
            qDebug() << "chegou metodo PRIM";
            int n = grafo->getVerticeCount();
            Vertice **V = grafo->getVertice();
            Vertice *verticeAtual, *vertice;
            Aresta *aresta;

            for( int i = 0; i < n; i++ ) {
                V[i]->setDistancia(INFINITO);
                V[i]->setPai(NULL);
                V[i]->setCor(Qt::white);
                lista.append(V[i]);
            }
            qDebug() << "Saiu do for";
            V[indexVi]->setDistancia(0);
            while ( !lista.empty() ) {
                qDebug() << "ListaSize:" << lista.size();
                vertice = popMenor();
                qDebug() << "ListaSizeDepois:" << lista.size();
                vertice->setCor(Qt::gray);
                emit sinalPrim();
                sleep(2);
                for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ){
                    verticeAtual = V[aresta->getIdV2()];
                    if ( (verticeAtual->getCor() != Qt::black ) && (verticeAtual->getDistancia() > aresta->getW()) ) {
                        verticeAtual->setPai(vertice);
                        verticeAtual->setDistancia( aresta->getW() );
                    }
                }
                vertice->setCor(Qt::black);
                qDebug() << "Pintou Preto  ";
                emit sinalPrim();
                sleep(2);
            }
        }

        Vertice* popMenor(){
            int menor = 0;
            for (int i= 1; i < lista.size(); i++ ) {
                if ( lista.at(i)->getDistancia() < lista.at(menor)->getDistancia() ) {
                    menor = i;
                }
            }
            qDebug() << "Menor: " << lista.at(menor)->getNome() << "Com distancia: " << lista.at(menor)->getDistancia();
            return lista.takeAt(menor);
        }

};

#endif // PRIM_H
