#ifndef GRAPF_H
#define GRAPF_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QColor>
#include <QMessageBox>
#include <QMainWindow>

#include <QPainter>

#include "vertex.h"

#define INF  100000

class Graph : public QWidget {
    Q_OBJECT

public:
    Graph ( int n, QMainWindow *m, QWidget *parent=0 );


    void addVertex ( QString, QPoint );
    bool addEdge ( QString, QString, int, QColor color=Qt::black );

    Edge    *getEdges();
    Vertex  **getVertex () ;
    Vertex  *getVertexAt ( int );
    int     getVertexCount();
    int     getVertexIndex ( QString  );
    QString getPath ( QString );
    QString loadFromFile ( QString );

    void paint ();

    void resize ( int );
    void dispose ();
    ~Graph ( ) ;

signals:
    void update ( Graph * );

private:
    QMainWindow *main;
    Vertex      **vertex;
    Edge        *edges;

    int max;
    int count; 
};



#endif // GRAPF_H
