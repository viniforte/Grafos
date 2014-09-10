#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include <QThread>
#include <QList>
#include "grafo.h"
#include "vertice.h"



class FordFulkerson : public QThread
{
    Q_OBJECT
    public:
        void setParameters(Grafo * g, int initial, int final) {
            this->grafo = g;
            this->VerticeInitial = initial;
            this->VerticeFinal = final;
        }

        void run() {
            metodoFordFulkerson();
        }
    private:
        int tempo;
        int VerticeInitial;
        int VerticeFinal;
        Grafo *grafo;
        QList<Vertice *> lista;
    signals:
        void sinalFordFulkerson();

    public:

        void metodoFordFulkerson () {
            qDebug() << "Ford Fulkerson";
            Vertice **V = grafo->getVertice();
            Aresta *aresta;

            if ( VerticeInitial == VerticeFinal ) {
                qDebug() << "Erro: inicio e fim iguais";
                return;
            }

            QList<Vertice *> ListaAresta;
            bool existeCaminho;
            int cf;

            // Zera todas os fluxos
            for (int i=0; i< grafo->getVerticeCount();i++){
                for ( aresta =  V[i]->getAresta(); aresta != NULL; aresta = aresta->getNext() ) {
                    aresta->setFluxo(0);
                    qDebug() << aresta->getIdV1() << "fLUXO" << aresta->getFluxo();
                }
            }
        }

/*
            existeCaminho = buscaCaminhoAumento (VerticeInitial, VerticeFinal, &ListaAresta);

            while (existeCaminho) {
                // Obtém o residual mais restritivo
                cf = CF ( &ListaAresta );

                // Atualiza os fluxos com o residual encontrado
                for ( int i=0; i<caminho.count(); i++ )
                    caminho.at(i)->fluxo += cf;

                // Apresenta o caminho encontrado
                //textEdit->append( mostrarCaminho ( &caminho ) );

                // Apaga o caminho para buscar novo
                caminho.clear();

                // Busca novo caminho
                existeCaminho = buscaCaminhoAumento (ini, fim, &caminho);
            }
        }/*
            bool buscaCaminhoAumento ( No *atual, No *fim, QVector<Aresta*> *caminho ) {
                if (atual->visitando) return false;

                if (atual->nome==fim->nome) return true;

                atual->visitando = true;

                QVector<Aresta*> arestasOrd;

                Aresta *aresta;
                bool achou = false;
                int  i=0, j;

                // Ordena as arestas pelo maior valor residual
                for ( aresta=atual->adjs->get(i); aresta!=NULL; aresta=atual->adjs->get(++i) ) {
                    if (aresta->r()>0) {
                        for ( j=0; (j<arestasOrd.count()) && (arestasOrd.at(j)->r() > aresta->r()); j++);
                        arestasOrd.insert(j, aresta);
                    }
                }
                // Para cada aresta ordenada, tenta encontrar o caminho
                for ( i = 0; i<arestasOrd.count() && !achou; i++ ) {
                    aresta = arestasOrd.at(i);
                    No *noadj = getNoAdj(atual, aresta);
                    achou = buscaCaminhoAumento( noadj, fim, caminho );
                    if ( achou ) {
                        caminho->insert(0, aresta );
                    }
                }

                atual->visitando = false;
                return achou;
            }

            int CF ( QVector<Aresta*> *caminho ) {
                int cf = INFINITO;
                for (int i=0; i<caminho->count();i++) {
                    if (caminho->at(i)->r()<cf)
                        cf = caminho->at(i)->r();
                }
                return cf;
            }

            QString mostrarCaminho ( QVector<Aresta*> *caminho ) {
                QString s="", sn;
                for (int i=0; i<caminho->count(); i++) {
                    sn.setNum(caminho->at(i)->r());
                    s = s+ "("+caminho->at(i)->no1 + "," + caminho->at(i)->no2 +
                            + ",r="+sn+")";
                }
                return s;
            }*/


};

#endif // FORDFULKERSON_H
