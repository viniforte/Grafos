#ifndef BFS_H
#define BFS_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"



class Bfs : public QThread
{
    Q_OBJECT
    public:
        void setParameters(Grafo * g, int initial, int final) {
            this->grafo = g;
            this->VerticeInitial = initial;
            this->VerticeFinal = final;
        }

        void run() {
            metodoBFS();
        }
    private:
        int tempo;
        int VerticeInitial;
        int VerticeFinal;
        Grafo *grafo;
    signals:
        void sinal();

    public:
        void metodoBFS() {
            //Lista lista = new Lista();
            qDebug() << "chegou metodoBFS";
            QList<Vertice *> lista;
            Vertice *verticeAtual, *vertice;
            Aresta *aresta;
            Vertice **V = grafo->getVertice();
            int n = grafo->getVerticeCount();
            int i;
            for ( i = 1; i < n; i++ ) {
                qDebug() << "Inicializando vertices";
                V[i]->setParent(NULL);
                V[i]->setCor(Qt::white);
                V[i]->setDistancia(INFINITO);
            }
            V[0]->setParent(NULL);
            V[0]->setDistancia(0);
            V[0]->setCor(Qt::gray);
            qDebug() << "Vai emitir sinal";
            emit sinal();
            sleep(2);
            qDebug() << "Emitiu sinal";

            //lista->appendVertice(vertice[0]);
            lista.append(V[0]);
            //while (!lista->isEmpty() ) {
            while (!lista.empty()) {
                //vertice->lista->removeInicio();
                vertice = lista.takeFirst();
                for ( aresta = vertice->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                    verticeAtual = V[aresta->getIdV2()];
                    if ( verticeAtual->getCor() == Qt::white ) {
                        verticeAtual->setCor(Qt::gray);
                        emit sinal();
                        sleep(2);
                        verticeAtual->setPai(vertice);
                        verticeAtual->setDistancia(vertice->getDistancia() + 1 );
                        lista.append(verticeAtual);
                    }
                }
                vertice->setCor(Qt::black);
                emit sinal();
                sleep(2);
                qDebug() << "Emitiu sinal";
            }
        }



};

#endif // BFS_H
