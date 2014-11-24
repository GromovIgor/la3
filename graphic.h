#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QtGui>
#include <QWidget>
#include <math.h>
#include <QVector>
#include <QDebug>
#include "worldmap.h"

class Graphic : public QWidget
{
public:
    Graphic(QWidget *wgt, int x, int y, int z, int edge);
    QVector<int> dot;
    int edges;
    int B;
    int X;
    int state;
    bool persp;
private:
    qreal Xpos;
    qreal Ypos;
    QWidget *wgt;
    QPainter painter;
    void paintEvent(QPaintEvent *pe);
    void Init();
    WorldMap map;
};

#endif // GRAPHIC_H
