#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grafo.h"
#include "Dfs.h"
#include "Bfs.h"
#include "OrdenacaoTopologica.h"
#include "Prim.h"
#include "Dijkstra.h"
#include "FordFulkerson.h"
#include "Kruskal.h"

#include <QPainter>
#include <QPaintEvent>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

signals:
    void mostrar ( Grafo * );

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mostrarLista(QList <Vertice *>);
    void getPath(QString);

public slots:
    void mostrarGrafo ( Grafo * );
    void slot();

private slots:
    void on_actionLoad_triggered();
    void on_start_clicked();
    void on_MostrarCaminhoButton_clicked();

private:
    Ui::MainWindow *ui;
    Grafo *grafo, *tmp;
    Dfs *dfs;
    Bfs *bfs;
    OrdenacaoTopologica *ord;
    Prim *prim;
    Dijkstra *dijkstra;
    FordFulkerson *ford;
    Kruskal *kruskal;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
