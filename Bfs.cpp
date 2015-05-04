#include "Bfs.h"

Bfs::Bfs( Grafo *grafo, int verticeInicial, QObject *parent) : QThread(parent) {
    this->grafo = grafo;
    this->verticeInicial = verticeInicial;
}

Bfs::~Bfs () {
    delete grafo;
}

void Bfs::run () {
    metodoBFS();
}

void Bfs:: metodoBFS() {
    qDebug() << "Metodo BFS";
    QList<Vertice *> lista;
    Vertice *verticeAtual, *vertice;
    Aresta *aresta;
    Vertice **ListaVertices = grafo->getVertice();
    int quantidade = grafo->getQuantidadeVertice();
    int i;
    for ( i = 0; i < quantidade; i++ ) {
        ListaVertices[i]->setPai(NULL);
        ListaVertices[i]->setCor(Qt::white);
        ListaVertices[i]->setPeso(INFINITO);
    }
    ListaVertices[this->verticeInicial]->setPeso(0);
    ListaVertices[this->verticeInicial]->setCor(Qt::gray);
    emit update(grafo);
    sleep(1);

    lista.append(ListaVertices[this->verticeInicial]);
    while (!lista.empty()) {
        vertice = lista.takeFirst();
        for ( aresta = vertice->getArestas(); aresta; aresta = aresta->getProximo() ) {
            verticeAtual = ListaVertices[aresta->getIndiceAdj()];
            if ( verticeAtual->getCor() == Qt::white ) {
                verticeAtual->setCor(Qt::gray);

                emit update(grafo);
                sleep(1);

                verticeAtual->setPai(vertice);
                verticeAtual->setPeso(vertice->getPeso() + 1 );
                lista.append(verticeAtual);
            }
        }
        vertice->setCor(Qt::black);
        emit update(grafo);
        sleep(1);
        qDebug() << "Emitiu sinal";
    }
}


