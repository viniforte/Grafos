#ifndef DFS_H
#define DFS_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"


class Dfs : public QThread
{
    Q_OBJECT
    public:
        void setParameters(Grafo * g, int initial, int final) {
            this->grafo = g;
            this->VerticeInitial = initial;
            this->VerticeFinal = final;
        }

        void run() {
            metodoDFS();
        }
    private:
        int tempo;
        int VerticeInitial;
        int VerticeFinal;
        Grafo *grafo;
    signals:
        void sinal();

    public:
        void metodoDFS() {
            Vertice **V = grafo->getVertice();
            int n = grafo->getVerticeCount();
            for(int i = 0; i < n; i++) {
                V[i]->setPai(NULL);
                V[i]->setTempoEntrada(INFINITO);
                V[i]->setTempoSaida(INFINITO);
                V[i]->setCor(Qt::white);
            }
            tempo = 0;
            for(int i = VerticeInitial; i < n; i++) {
                if(V[i]->getCor() == Qt::white) {
                    visit(V[i]);
                }
            }
        }

        void visit(Vertice *v) {
            Aresta *a; Vertice *va;
            v->setCor(Qt::gray);
            emit sinal();
            sleep(2);
            v->setTempoEntrada(tempo++);
            for(a = v->getAresta(); a != NULL; a = a->getNext()) {
                va = grafo->getVertice()[a->getIdV2()];
                //qDebug() << v->getNome().toStdString() << ' ' << va->getNome().toStdString();
                if(va->getCor() == Qt::white) {
                    va->setPai(v);
                    visit(va);
                }
            }
            v->setTempoSaida(tempo++);
            v->setCor(Qt::black);
            emit sinal();
            sleep(2);
        }

};
#endif // DFS_H
