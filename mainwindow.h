#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "grafo.h"

#include <QPainter>
#include <QPaintEvent>

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

public slots:
    void mostrarGrafo ( Grafo * );

private slots:
    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;
    Grafo *grafo, *tmp;

protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
