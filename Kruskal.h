#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QThread>
#include "grafo.h"
#include "vertice.h"

class Kruskal : public QThread
{
    Q_OBJECT
public:
    void setParameters(Grafo * g, int initial, int final) {
        this->g = g;
        this->initial = initial;
        this->final = final;
    }

    void run() {
        kruskal();
    }

private:
    int tempo;
    int initial;
    QString final;
    Grafo *g;
    Vertice **vKruskal;

signals:
    void sinal();
public:

    QList <Aresta *> ArestaToList (Aresta * a){
        Aresta * h = a;
        QList <Aresta *> lista;
        while (h != NULL){
            lista.append(h);
            h = h->getNext();
        }
        return lista;
    }

    Aresta* ordenar (Aresta * a) {
        QList <Aresta *> lista = ArestaToList (a);
        for (int i = 0; i < lista.size(); i++){
            for (int j = i+1; j < lista.size(); j++)
            if (lista[i]->getW() > lista[j]->getW())
                lista.swap(i,j);
        }
        Aresta * r= new Aresta(lista[0]->getIdV1(),lista[0]->getIdV2(),lista[0]->getW());

        for (int i = 1; i < lista.size(); i++){
            Aresta::append(&r,lista[i]->getIdV1(),lista[i]->getIdV2(),lista[i]->getW());
        }
        return r;
    }

    void imprimiLista(Aresta * a){
        Aresta * h = a;

        while (h != NULL){
            qDebug() << h->getW();
            h = h->getNext();
        }
    }

    void kruskal() {
        Aresta *a = ordenar(g->getAresta());
        Vertice *v1, *v2;
        vKruskal = new Vertice *[g->getVerticeCount()];
        for(int i=0; i < g->getVerticeCount(); i++){
            vKruskal[i] = new Vertice(i, g->getVertice()[i]->getNome(),
                                      g->getVertice()[i]->getX(),
                                      g->getVertice()[i]->getY());
        }

        int n_a = 0;
        while((n_a-1 < g->getVerticeCount()) && (a != NULL)){
            v1 = vKruskal[a->getIdV1()];
            v2 = vKruskal[a->getIdV2()];
            if (!Find (v1,v2)){
                qDebug() <<"achou";
                /*v1->add(a->getIdV1(), a->getIdV2(), a->getW());
                v2->add(a->getIdV2(), a->getIdV1(), a->getW());
                join(v1,v2); //usa split se usar string, lista...
                n_a++;*/
            } else qDebug()<<"não achou";
            a = a->getNext();
        }
    }

    Vertice* find (Vertice * v){
        if (v != v->getPai()){
            v->setPai(find(v->getPai()));
        }
        return v->getPai();
    }

    bool Find ( Vertice *v1, Vertice *v2) {
        Vertice * p1 = find (v1);
        Vertice * p2 = find (v2);
        if (p1 != p2) return true;
        else return false;
    }

};

#endif // KRUSKAL_H
