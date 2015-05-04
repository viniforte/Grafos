#include "interface.h"
#include "ui_interface.h"

#include <QRect>
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

Interface::Interface(QWidget *parent) :
    QMainWindow(parent),
    interface(new Ui::Interface) {

    interface->setupUi(this);

    //this->ui->toolBar->addWidget( this->ui->labelInicial );
    //this->ui->toolBar->addWidget( this->ui->cbOrigem );
    //this->ui->toolBar->addWidget(this->ui->metodos);
    //this->ui->toolBar->addWidget(this->ui->start);
    //this->ui->statusBar->addWidget( this->ui->labelFinal  );
    //this->ui->statusBar->addWidget( this->ui->cbFinal );
    //this->ui->statusBar->addWidget( this->ui->textEdit );
    //this->ui->statusBar->addWidget( this->ui->pushButton );


    //QMainWindow::paintEvent(new QPaintEvent(this->geometry()));
    QRect geo;
    geo.setRect(800,700,100,300);
    QMainWindow::paintEvent(new QPaintEvent(geo));
    qDebug() << "Geometry";
    qDebug() << this->geometry();
    qDebug() << geo;
    this->grafo=new Grafo(0, this);
    this->tmp=NULL;

    connect( this, SIGNAL (mostrar( Grafo* )), this, SLOT ( mostrarGrafo(Grafo* ) ) );


    this->algoritmo = NULL;

    idmostrar=0;
}

void Interface::mostrarLista(QList<Vertice *> lista){
    qDebug() << "mostrarLista";
    QString str = "";
    this->interface->textEdit->append("Ordem Topologica");
    foreach (Vertice * vertice, lista){
        str = vertice->getNome() + str;
        if (!lista.endsWith(vertice)) str = " - " + str;
    }
    this->interface->textEdit->append(str);
}

void Interface::getCaminho(QString metodo){
    Vertice * vertice = this->grafo->getVertice()[interface->cbFinal->currentIndex()];
    QString msg = "";
    int cont = 0;
    while (vertice->getPai() != NULL){
        msg = vertice->getNome() + msg;
        msg = " -> " + msg;
        vertice = vertice->getPai();
        cont++;
    }
    msg = this->grafo->getVertice()[interface->cbOrigem->currentIndex()]->getNome() + msg;
    qDebug() << msg;
    this->interface->textEdit->setText(metodo + "\n" + msg);
}

void Interface::executarAlgoritmo ( int i ) {
    qDebug() << "EXECUNTANDO ALGORITMO";
    if (algoritmo) delete algoritmo;
        qDebug() << "switch";
    switch (i) {     
        case BFS : this->algoritmo = new Bfs ( grafo, interface->cbOrigem->currentIndex(), this );  break;
        case DFS : this->algoritmo = new Dfs ( grafo, interface->cbOrigem->currentIndex(), this ); break;
    }
    if (i != ORDENACAO){
        connect( algoritmo,  SIGNAL ( update(Grafo*)), this, SLOT ( mostrarGrafo(Grafo* ) ) );
        algoritmo->start();
    }
}

void Interface::paintEvent(QPaintEvent *) {
    grafo->pintar();
    if (!this->tmp) return;
    tmp->pintar();
}

void Interface::mostrarGrafo ( Grafo *grafo ) {
    this->tmp = grafo;
    update ();
}

void Interface::on_actionLoad_triggered() {
    QDir::setCurrent("../files");
    qDebug() << QDir::currentPath();
    QString nomeArquivo =  QFileDialog::getOpenFileName( this, tr("Open Document"), QDir::currentPath(), tr("Document files (*.txt);All files (*.*)"), 0, QFileDialog::DontUseNativeDialog );
    if( !nomeArquivo.isNull() ) {
        //qDebug() << filename.toAscii();
        QString s = grafo->carregarDoArquivo(nomeArquivo);
        interface->cbOrigem->addItems( s.split(";"));
        interface->cbFinal->addItems( s.split( ";") );
        emit mostrar ( grafo );
    }
}

void Interface::on_start_clicked() {
    if (this->grafo!=NULL) {
        executarAlgoritmo( this->interface->metodos->currentIndex() );
       }
}

void Interface::on_pushButton_clicked() {
    switch (interface->metodos->currentIndex()) {
        case DFS : getCaminho("DFS");break;
        case BFS : getCaminho("BFS");break;
    }
}

Interface::~Interface() {
    if (grafo) delete grafo;
    if (algoritmo) delete algoritmo;
    delete interface;
}
