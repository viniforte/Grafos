#ifndef BFS_H
#define BFS_H


#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "Grafo.h"

#define INFINITO 1000000

class Bfs : public QThread {
    Q_OBJECT

public:
    Bfs ( Grafo *grafo, int verticeOrigem, QObject *parent=0 );

    ~Bfs () ;

protected:
    void run();

signals:
    void update ( Grafo * );

private:
    Grafo *grafo;
    int verticeInicial;
    void metodoBFS ();

};

#endif // BFS_H
