#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#define DFS 0
#define BFS 1
#define ORDENACAO 2
#define PRIM 3
#define KRUSKAL 4
#define DIJKSTRA 5
#define FF 6

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->ui->toolBar->addWidget( this->ui->labelInicial );
    this->ui->toolBar->addWidget( this->ui->cbOrigem );
    this->ui->toolBar->addWidget(this->ui->metodos);
    this->ui->toolBar->addWidget(this->ui->start);
    this->ui->statusBar->addWidget( this->ui->labelFinal  );
    this->ui->statusBar->addWidget( this->ui->cbFinal );
    this->ui->statusBar->addWidget( this->ui->textEdit );
    this->ui->statusBar->addWidget( this->ui->pushButton );

    QMainWindow::paintEvent(new QPaintEvent(this->geometry()));

    this->graph=new Graph(0, this);
    this->tmp=NULL;

    connect( this, SIGNAL (mostrar( Graph* )), this, SLOT ( mostrarGrafo(Graph* ) ) );


    this->alg = NULL;

    idmostrar=0;
}

void MainWindow::mostrarLista(QList<Vertex *> lista){
    qDebug() << "mostrarLista";
    QString str = "";
    this->ui->textEdit->append("Ordem Topologica");
    foreach (Vertex * vertice, lista){
        str = vertice->getName() + str;
        if (!lista.endsWith(vertice)) str = " - " + str;
    }
    this->ui->textEdit->append(str);
}

void MainWindow::getPath(QString metodo){
    Vertex * ver = this->graph->getVertex()[ui->cbFinal->currentIndex()];
    QString msg = "";
    int cont = 0;
    while (ver->getFather() != NULL){
        msg = ver->getName() + msg;
        msg = " -> " + msg;
        ver = ver->getFather();
        cont++;
    }
    msg = this->graph->getVertex()[ui->cbOrigem->currentIndex()]->getName() + msg;
    qDebug() << msg;
    this->ui->textEdit->setText(metodo + "\n" + msg);
}

void MainWindow::createAlgoritm ( int i ) {
    if (alg) delete alg;
    switch (i) {
    case DFS : this->alg = new Dfs ( graph, ui->cbOrigem->currentIndex(), this ); break;
    case BFS : this->alg = new Bfs ( graph, ui->cbOrigem->currentIndex(), this );  break;
    case ORDENACAO : {

        this->ord = new OrdenacaoTopologica ( graph, ui->cbOrigem->currentIndex(), this );
        connect( ord,  SIGNAL ( update(Graph*)), this, SLOT ( mostrarGrafo(Graph* ) ) );
        this->ord->start();
        break;
    }
    case PRIM : this->alg = new Prim ( graph, ui->cbOrigem->currentIndex(),this, this ); break;
    case DIJKSTRA : this->alg = new Dijkstra ( graph, ui->cbOrigem->currentIndex(),this, this  ); break;
    case KRUSKAL : this->alg = new kruskal ( graph, this, this ); break;
    }
    if (i != ORDENACAO){
        connect( alg,  SIGNAL ( update(Graph*)), this, SLOT ( mostrarGrafo(Graph* ) ) );
        alg->start();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    graph->paint();
    if (!this->tmp) return;
    tmp->paint();
}

void MainWindow::mostrarGrafo ( Graph *g ) {
    this->tmp = g;
    update ();
}

void MainWindow::on_actionLoad_triggered() {
    QDir::setCurrent("../files");
    qDebug() << QDir::currentPath();
    QString filename =  QFileDialog::getOpenFileName( this, tr("Open Document"),
                                                      QDir::currentPath(),
                                                      tr("Document files (*.txt);All files (*.*)"), 0,
                                                      QFileDialog::DontUseNativeDialog );
    if( !filename.isNull() ) {
        //qDebug() << filename.toAscii();
        QString s = graph->loadFromFile(filename);
        ui->cbOrigem->addItems( s.split(";"));
        ui->cbFinal->addItems( s.split( ";") );
        emit mostrar ( graph );
    }
}

void MainWindow::on_start_clicked() {
    if (this->graph!=NULL) {
        createAlgoritm( this->ui->metodos->currentIndex() );
       }
}

void MainWindow::on_pushButton_clicked() {
    switch (ui->metodos->currentIndex()) {
        case DFS : getPath("DFS");break;
        case BFS : getPath("BFS");break;
        case ORDENACAO : mostrarLista(this->ord->getList());break;
    }
}

MainWindow::~MainWindow() {
    if (graph) delete graph;
    if (alg) delete alg;
    delete ui;
}
