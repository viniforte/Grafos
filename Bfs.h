#ifndef BFS_H
#define BFS_H


#include <QThread>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMainWindow>

#include "graph.h"
#define INFINITO 1000000
class Bfs : public QThread {
    Q_OBJECT

public:
    Bfs ( Graph *g,int vert, QObject *parent=0 );

    ~Bfs () ;

protected:
    void run();

signals:
    void update ( Graph * );

private:
    Graph *g;
    int verticeInicial;
    void metodoBFS ();

};

#endif // BFS_H
