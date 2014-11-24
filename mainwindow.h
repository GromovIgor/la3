#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include "graphic.h"
#include <QDebug>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    Graphic *view;
public:
    MainWindow();
private slots:
    void setXvar(int i);
    void setYvar(int i);
    void setZvar(int i);
    void setnumber(int i);
    void setRender(int state);
    void setX(int state);
    void setAngleB(int state);
    void setPerspective(int state);
};

#endif // MAINWINDOW_H
