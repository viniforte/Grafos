#include "vertex.h"


Vertex::Vertex ( int id, QString name, QPoint p, QObject *parent ) : QObject(parent) {
    this->id     = id;
    this->name   = name;
    this->p      = p;

    this->t      = 0;
    this->d      = 0;
    this->color  = Qt::white;
    this->father = NULL;
    this->edges  = NULL;
    this->set    = QString::number(id);
}

QString Vertex::getSET () {
    return this->set;
}

int Vertex::getId() {
    return this->id;
}

QString Vertex::getName() {
    return this->name;
}

QColor Vertex::getColor() {
    return this->color;
}

Edge *Vertex::getEdges() {
    return this->edges;
}

Vertex *Vertex::getFather() {
    return this->father;
}

int Vertex::getD () {
    return this->d;
}

int Vertex::getTi () {
    return this->d;
}

int Vertex::getTo () {
    return this->t;
}

QPoint Vertex::getPoint () {
    return this->p;
}

void Vertex::setSET ( QString newSet ) {
    this->set = newSet;
}

void Vertex::append( int idAdj, int w, QColor color )  {
    Edge::append( &edges, id, idAdj, w, color );
}

void Vertex::setFather( Vertex *value ) {
    this->father = value;
}

void Vertex::setD ( int value) {
    this->d   = value;
}

void Vertex::setTi ( int value ) {
    this->d  = value;
}

void Vertex::setTo  ( int value ) {
    this->t  = value;
}

void Vertex::setColor ( QColor value ) {
    this->color = value;
}

Vertex *Vertex::clone () {
    return new Vertex (id, name, p, this->parent() );
}

void Vertex::paint ( QPainter &painter ) {
    painter.setBrush ( color );
    painter.setPen( (color==Qt::white)? Qt::black : Qt::white );
    painter.drawEllipse( p.x()-20,  p.y()-20, 40, 40 );

    QRect rect ( p.x()-4,  p.y()-8, p.x()+4,  p.y()+8 );
    painter.drawText( rect, name );


    // colocar peso?
    // setar o pai?
}

Vertex::~Vertex() {
    qDebug() << "Excluindo vertice " << name;
    if (this->edges!=NULL)
        delete this->edges;
}

