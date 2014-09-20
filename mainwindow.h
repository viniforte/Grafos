#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graph.h"
#include "Dfs.h"
#include "Bfs.h"
#include "OrdenacaoTopologica.h"
#include "Prim.h"
#include "Dijkstra.h"
#include "kruskal.h"

#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void mostrar ( Graph *);

public:
    explicit MainWindow(QWidget *parent = 0);
     void mostrarLista(QList<Vertex *> lista);
     void getPath (QString metodo);
    ~MainWindow();

public slots:
    void mostrarGrafo ( Graph * );


private slots:
    void on_actionLoad_triggered();

    void on_start_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Graph *graph, *tmp;
    QThread *alg;
    OrdenacaoTopologica * ord;
    int idmostrar;
    int metodo;
    void createAlgoritm ( int i );


protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
