#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "grafo.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    //this->p
    this->ui->toolBar->addWidget( this->ui->labelInicial );
    this->ui->toolBar->addWidget( this->ui->cbOrigem );
    this->ui->toolBar->addWidget( this->ui->labelFinal  );
    this->ui->toolBar->addWidget( this->ui->cbFinal );
    this->ui->toolBar->addWidget(this->ui->start);
    this->ui->statusBar->addWidget( this->ui->caminho );
    this->ui->statusBar->addWidget( this->ui->MostrarCaminhoButton );

    QMainWindow::paintEvent(new QPaintEvent(this->geometry()));
    this->grafo=this->tmp=NULL;
    connect( this, SIGNAL (mostrar(Grafo * )), this, SLOT(mostrarGrafo(Grafo*)) );
}

void MainWindow::paintEvent(QPaintEvent *) {
    if (this->tmp==NULL) return;

    QPainter painter(this);
    painter.setPen(Qt::SolidLine);

    Vertice **vertice = tmp->getVertice();
    Vertice *v, *v1, *v2;
    Aresta *a;
    int n = tmp->getVerticeCount();

    // Pintar primeiramente as arestas
    painter.setPen( Qt::black );
    painter.setPen( Qt::SolidLine );

    for (int i=0; i<n; i++) {
        a=vertice[i]->getAresta();
        while (a!=NULL) {
            v1 = vertice[a->getIdV1()];
            v2 = vertice[a->getIdV2()];
            painter.drawLine( QPoint (v1->getX(), v1->getY()), QPoint (v2->getX(), v2->getY()) );
            a = a->getNext();
        }
    }
    for (int i=0; i<n; i++) {
        v=vertice[i];
        painter.setBrush ( v->getCor() );
        painter.setPen( (v->getCor()==Qt::white)? Qt::black : Qt::white );
        painter.drawEllipse( v->getX()-20,  v->getY()-20, 40, 40 );
        QRect r1 ( v->getX()-4,  v->getY()-8, v->getX()+4,  v->getY()+8 );
        painter.drawText( r1, v->getNome() );
    }
}

void MainWindow::mostrarGrafo ( Grafo *g ) {
    this->tmp=g;
    update();
}

void MainWindow::on_actionLoad_triggered() {
    QDir::setCurrent("../files");
    qDebug() << QDir::currentPath();
    QString filename =  QFileDialog::getOpenFileName( this, tr("Open Document"),
                                                     QDir::currentPath(),
                                                     tr("Document files (*.txt);All files (*.*)"), 0,
                                                     QFileDialog::DontUseNativeDialog );
    if( !filename.isNull() ) {
        qDebug() << filename;

        QFile file( filename );
        if(!file.open(QIODevice::ReadOnly)) {
            qDebug() << "error " << file.errorString();
            QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
            return;
        }
        QTextStream in(&file);
        QString line;
        QStringList sl;

        if (grafo!=NULL) delete grafo;
        line = in.readLine();     // nï¿½mero de vï¿½rtices
        grafo = new Grafo ( line.toInt(), this );

        ui->cbOrigem->clear();
        ui->cbFinal->clear();
        bool loadvertice = true;
        while(!in.atEnd() && loadvertice) {
            line = in.readLine();
            if (line.length()>0 && line.at(0)!='(') {
                //line = 1,100,100 ==> nome vï¿½rtice, coordenada x, coordenada y
                sl = line.split(",");
                if (sl.count()==3) {
                    grafo->add( sl[0], sl[1].toInt(), sl[2].toInt() );
                    ui->cbOrigem->addItem( sl[0] );
                    ui->cbFinal->addItem( sl[0] );
                } else {
                    QMessageBox::critical(this,"Carregar vï¿½rtices", "Erro na estrutura do arquivo - nï¿½s [node, coord. x, coord. y]!");
                    return;
                }
            } else
                loadvertice = false;
        }
        if (!in.atEnd()) {
            do {
                // line = (1,2,5)
                line = line.mid(1, line.length() -2 );

                //line = 1,2,5
                //qDebug() << line;

                sl = line.split(",");
                if (sl.count()==3)
                    grafo->addAresta(sl[0], sl[1], sl[2].toInt() );
                else {
                    QMessageBox::critical(this,"Carregar arestas", "Erro na estrutura do arquivo - nï¿½s [node, coord. x, coord. y]!");
                    return;
                }

                line = in.readLine();
            } while(!in.atEnd());
        }

        qDebug() << "Carregado com sucesso!";
        file.close();

        emit mostrar ( grafo );
    }
}

MainWindow::~MainWindow() {
    if (grafo!=NULL)
        delete grafo;
    delete ui;
}

void MainWindow::mostrarLista(QList<Vertice *> lista){
    qDebug() << "mostrarLista";
    QString str = "";
    this->ui->caminho->append("Ordem Topologica");
    foreach (Vertice * vertice, lista){
        str += vertice->getNome();
        if (!lista.endsWith(vertice)) str += " - ";
    }
    this->ui->caminho->append(str);
}

void MainWindow::getPath(QString metodo){
    Vertice * ver = this->grafo->getVertice()[ui->cbFinal->currentIndex()];
    QString msg = "";
    int cont = 0;
    while (ver->getPai() != NULL){
        msg = ver->getNome() + msg;
        msg = " -> " + msg;
        ver = ver->getPai();
        cont++;
    }
    msg = this->grafo->getVertice()[ui->cbOrigem->currentIndex()]->getNome() + msg;
    qDebug() << msg;
    this->ui->caminho->setText(metodo + "\n" + msg);
}

void MainWindow::on_start_clicked(){
    switch ( this->ui->cdMetodo->currentIndex()) {
        case 0:
            qDebug() << "DFS";
            dfs = new Dfs();
            dfs->setParameters(grafo, ui->cbOrigem->currentIndex(), ui->cbFinal->currentIndex());
            dfs->start();
            connect(dfs, SIGNAL(sinal()), SLOT(slot()));
            break;
        case 1:
            qDebug() << "BFS";
            bfs = new Bfs();
            bfs->setParameters(grafo, ui->cbOrigem->currentIndex(), ui->cbFinal->currentIndex());
            bfs->start();
            connect(bfs, SIGNAL(sinal()), SLOT(slot()));
            break;
        case 2:
            qDebug() << "Ordenação Topologica";
            ord = new OrdenacaoTopologica();
            ord->setParameters(grafo, ui->cbOrigem->currentIndex(), ui->cbFinal->currentIndex());
            ord->start();
            connect(ord, SIGNAL(sinal()), SLOT(slot()));
            break;
        case 3:
            qDebug() << "Dijkstra";
            break;
        case 4:
            qDebug() << "Prim";
            break;
        case 5:
            qDebug() << "Kruskal";
            break;
        case 6:
            qDebug() << "Ford-Fulkerson";
            break;
        default:
            break;
    }
}

void MainWindow::on_MostrarCaminhoButton_clicked()
{
    switch ( this->ui->cdMetodo->currentIndex()) {
        case 0:
            qDebug() << "DFS";
            this->getPath("DFS");
            break;
        case 1:
            qDebug() << "BFS";
            break;
        case 2:
            qDebug() << "Ordenação Topologica";
            this->mostrarLista(ord->getList());
            break;
        case 3:
            qDebug() << "Dijkstra";
            break;
        case 4:
            qDebug() << "Prim";
            break;
        case 5:
            qDebug() << "Kruskal";
            break;
        case 6:
            qDebug() << "Ford-Fulkerson";
            break;
        default:
            break;
    }
}

void MainWindow::slot() {
    update();
    QThread::sleep(1);
}
