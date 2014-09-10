TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mainwindow.cpp \
    grafo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    fila.h \
    grafo.h \
    vertice.h \
    mainwindow.h \
    Aresta.h \
    Dfs.h \
    Bfs.h \
    OrdenacaoTopologica.h \
    Dijkstra.h \
    Prim.h \
    FordFulkerson.h

FORMS += \
    mainwindow.ui
