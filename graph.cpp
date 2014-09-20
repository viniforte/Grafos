#include "graph.h"

#include <QFile>

Graph::Graph ( int n, QMainWindow *main, QWidget *parent ) : QWidget (parent)  {
    this->main    = main;
    this->edges   = NULL;
    this->vertex  = NULL;
    this->max     = n;
    this->count   = 0;

    resize(n);
}

void Graph::paint () {

    QPainter painter(main);

    // Pintar primeiramente as arestas
    for (Edge *e=edges; e; e=e->getNext() ) {
        e->paint( getVertexAt(e->getId())->getPoint(),
                 getVertexAt(e->getIdAdj())->getPoint(),
                 painter );
    }

    for (int i=0; i<count; i++) {
        getVertexAt(i)->paint(painter);
    }
}

void Graph::resize ( int n ) {
    dispose();
    this->max    = n;
    this->count  = 0;
    this->vertex = new Vertex*[max];
    for (int i=0; i<max; i++) {
        vertex[i] = NULL;
    }
}

int Graph::getVertexIndex ( QString name ) {
    for (int i=0; i<count; i++)
        if ((vertex[i]!=NULL) && (vertex[i]->getName()==name.toUpper()))
            return i;
    return -1;
}

Vertex* Graph::getVertexAt ( int index ) {
    return (index<count)? vertex[index] : NULL;
}

void Graph::addVertex ( QString name, QPoint p ) {
    if (count<max) {
        qDebug() << "Adicionando vértice " << name;
        vertex[count] = new Vertex(count, name.toUpper(), p );
        count++;
    } else
        qDebug() << "Número de vértices maior que o informado!";
}

bool Graph::addEdge ( QString source, QString target, int w, QColor color ) {
    int s = getVertexIndex(source.toUpper());
    int t = getVertexIndex(target.toUpper());
    if ((s==-1) || (t==-1)) {
        qDebug() << "Vértice de [origem|destino] não encontrado: " << source << ", " << target;
        return false;
    }
    Edge::append( &edges, s, t, w, color );
    vertex[s]->append( t, w, color );
    return true;
}

QString Graph::getPath( QString name ) {
    QString s = "";
    Vertex *v = vertex [ getVertexIndex( name ) ];
    while (v!=NULL) {
        s += v->getName()+ ",";
        v = v->getFather();
    }
    return s;
}

Edge *Graph::getEdges() {
    return this->edges;
}

Vertex **Graph::getVertex ()    {
    return this->vertex;
}

int Graph::getVertexCount()  {
    return this->count;
}

QString Graph::loadFromFile ( QString fileName ) {
    QString v="", c="";

    QFile file( fileName );
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "error " << file.errorString();
        QMessageBox::critical(this, "Lendo arquivo", "Erro na leitura do arquivo selecionado");
        return "";
    }
    QTextStream in(&file);

    QString line;
    QStringList sl;

    int n = in.readLine().toInt();
    resize(n);
    while(!in.atEnd() && n) {
        line = in.readLine();
        //line = 1,100,100 ==> nome vértice, coordenada x, coordenada y
        sl = line.split(",");
        if (sl.count()==3) {
            addVertex ( sl[0], QPoint(sl[1].toInt(), sl[2].toInt()));
            v  += c + sl[0];  c   = ";";
        } else {
            QMessageBox::critical(this,"Carregar vértices", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
        n--;
    }
    while(!in.atEnd() && !line.isEmpty()) {
        line = in.readLine();   // line = (1,2,5)
        line = line.mid(1, line.length() -2 );  // line = 1,2,5
        sl = line.split(",");
        if (sl.count()==3)
            addEdge(sl[0], sl[1], sl[2].toInt() );
        else {
            QMessageBox::critical(this,"Carregar arestas", "Erro na estrutura do arquivo - nós [node, coord. x, coord. y]!");
            return "";
        }
    }

    qDebug() << "Carregado com sucesso!";
    file.close();

    return v;
}

void Graph::dispose () {
    for (int i=0; i<count; i++)
        delete vertex[i];
    if (vertex)
        delete [] vertex;
}

Graph::~Graph ( ) {
    qDebug() << "Eliminando o Graph";
    dispose();
}
