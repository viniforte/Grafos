#include "Bfs.h"

Bfs::Bfs( Graph *g, int vert, QObject *parent) : QThread(parent) {
    this->g = g;
    this->verticeInicial = vert;
}

Bfs::~Bfs () {
    delete g;
}

void Bfs::run () {
    metodoBFS();
}

void Bfs:: metodoBFS() {
    QList<Vertex *> lista;
    Vertex *verticeAtual, *vertice;
    Edge *aresta;
    Vertex **V = g->getVertex();
    int n = g->getVertexCount();
    int i;
    for ( i = 0; i < n; i++ ) {
        V[i]->setFather(NULL);
        V[i]->setColor(Qt::white);
        V[i]->setD(INFINITO);
    }
    V[this->verticeInicial]->setD(0);
    V[this->verticeInicial]->setColor(Qt::gray);
    emit update(g);
    sleep(1);

    lista.append(V[this->verticeInicial]);
    while (!lista.empty()) {
        vertice = lista.takeFirst();
        for ( aresta = vertice->getEdges(); aresta; aresta = aresta->getNext() ) {
            verticeAtual = V[aresta->getIdAdj()];
            if ( verticeAtual->getColor() == Qt::white ) {
                verticeAtual->setColor(Qt::gray);
                emit update(g);
                sleep(1);
                verticeAtual->setFather(vertice);
                verticeAtual->setD(vertice->getD() + 1 );
                lista.append(verticeAtual);
            }
        }
        vertice->setColor(Qt::black);
        emit update(g);
        sleep(1);
        qDebug() << "Emitiu sinal";
    }
}


