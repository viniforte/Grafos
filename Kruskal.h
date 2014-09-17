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
        Aresta * r= new Aresta(lista[0]->getIdV1(),lista[0]->getIdV2(),lista[0]->getW(),Qt::yellow);

        for (int i = 1; i < lista.size(); i++){
            Aresta::append(&r,lista[i]->getIdV1(),lista[i]->getIdV2(),lista[i]->getW(),Qt::yellow);
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

    void procuraAresta(Aresta * a){
        Vertice *v = g->getVertice()[a->getIdV1()];
        qDebug() << v->getNome();
        Aresta * h = v->getAresta();
        qDebug() << "origem: " << h->getIdV1();
        qDebug() << "destino: " << a->getIdV2();
        while (h!= NULL && h->getIdV2() != a->getIdV2()){
            h = h->getNext();
        }

        if (h != NULL && h->getIdV2() == a->getIdV2()) {
            qDebug() << "destino h: " << h->getIdV2() << " origem h: " << h->getIdV1();
            h->setColor(Qt::red);
            emit sinal();
        }
    }
    void kruskal() {
        Aresta *a = ordenar(g->getAresta());
        imprimiLista(a);
        Vertice *v1, *v2;
        vKruskal = new Vertice *[g->getVerticeCount()];
        for(int i=0; i < g->getVerticeCount(); i++){
            vKruskal[i] = new Vertice(i, g->getVertice()[i]->getNome(),
                                      g->getVertice()[i]->getX(),
                                      g->getVertice()[i]->getY());
            vKruskal[i]->setLista(QString::number(g->getVertice()[i]->getId()));
            qDebug() << vKruskal[i]->getLista();
        }

        int n_a = 0;
        while((n_a-1 < g->getVerticeCount()) && (a != NULL)){
            v1 = vKruskal[a->getIdV1()];
            v2 = vKruskal[a->getIdV2()];
            if (!Find (v1,v2)){
                v1->add(a->getIdV1(), a->getIdV2(), a->getW());
                v2->add(a->getIdV2(), a->getIdV1(), a->getW());
                v1->getAresta()->setColor(Qt::red);
                v2->getAresta()->setColor(Qt::red);
                join(v1,v2); //usa split se usar string, lista...
                n_a++;
                procuraAresta(a);
            }
            a = a->getNext();
        }
    }
    void join (Vertice * v1, Vertice *v2){
        qDebug() << "Lista 1: " << v1->getLista();
        qDebug() << "Lista 2: " << v2->getLista();
        QString c = v1->getLista() + ";"+ v2->getLista();
        qDebug() << "lista c: " << c;
        QStringList s = c.split(";");
        foreach (QString str, s){
            qDebug() << "Str: " << str;
            vKruskal[str.toInt()]->setLista(c);
        }
    }

    bool Find (Vertice *v1, Vertice *v2){
        if (find (QString::number(v1->getId()), v2->getLista()) && find(QString::number(v2->getId()), v1->getLista()))
            return true;
        return false;
    }

    bool find ( QString nome, QString lista) {
        QStringList s = lista.split(";");
        return s.contains(nome);
    }

};

#endif // KRUSKAL_H
