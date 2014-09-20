#include "edge.h"

Edge::Edge ( int id, int idAdj, int w, QColor color, QObject *parent ) : QObject(parent) {
    this->id    = id;    // source of edges
    this->idAdj = idAdj; // adjacent of edges
    this->w     = w;

    this->next  = NULL;
    this->color = color;
}

void Edge::setColor ( QColor value ) {
    this->color = value;
}

void Edge::paint(QPoint p1, QPoint p2, QPainter &painter ) {
    painter.setPen( color );
    painter.drawLine ( p1, p2 );

    int x = (p1.x()+p2.x())/2;
    int y = (p1.y()+p2.y())/2;
    QRect rect ( x-4,  y, x,  y );
    painter.drawText ( rect, QString::number(w) );
}

int Edge::getW ()  {
    return this->w;
}

int Edge::getId() {
    return this->id;
}
int Edge::getIdAdj() {
    return this->idAdj;
}

QColor Edge::getColor ( ) {
    return this->color;
}

Edge *Edge::getNext() {
    return this->next;
}

void Edge::append ( Edge **e, int id, int idAdj, int w, QColor color ) {
    if (*e==NULL)
        *e = new Edge ( id, idAdj, w, color );
    else
        append( &(*e)->next, id, idAdj, w, color );
}

Edge* Edge::removeLeast ( Edge **e, Edge *m ) {
    if (*e) {
        if (!m) m=*e;

        if ((*e)->getW()<m->getW())
            m = removeLeast( &(*e)->next,*e);
        else
            m = removeLeast( &(*e)->next,m);

        if (m==*e) {
            *e = m->getNext();
            m->next = NULL;
        }
    }
    return m;
}

Edge* Edge::clone ( Edge *e ) {
    if (e) {
        Edge *h = new Edge(e->getId(), e->getIdAdj(),e->getW(), e->getColor() );
        h->next = clone(e->next);
        return h;
    }
    return NULL;
}

Edge::~Edge() {
    qDebug() << "Excluindo aresta (" << id <<","<<idAdj<<"," << w << ")";
    if (this->next!=NULL)
        delete this->next;
}

