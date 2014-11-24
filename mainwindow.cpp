/*самое главное окно, реализованы функции, связывающие переключатели и поля слева с основным
виджетом отрисовки конуса. При любом изменении значения поля - перерисовка конуса*/
#include "mainwindow.h"
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>

//конструктор всего окна и связывание переключателей с виждетом рисования конуса
MainWindow::MainWindow()
{
    setFixedSize(1000,800);

    view              = new Graphic(this,30,40,70,12);
    QGroupBox *gbox   = new QGroupBox(this);
    QLabel *lbl       = new QLabel(gbox);
    QCheckBox *chbox  = new QCheckBox(gbox);

    view->setGeometry(175,0,this->width()-175,this->height());

    gbox->setTitle(tr("Point of view"));
    gbox->setGeometry(10,10,145,100);
    lbl->setText(tr("Observation point"));
    lbl->setGeometry(30,10,100,40);
    QSpinBox *xVar = new QSpinBox(gbox);
    QSpinBox *yVar = new QSpinBox(gbox);
    QSpinBox *zVar = new QSpinBox(gbox);
    xVar->setRange(-500,500);
    yVar->setRange(-500,500);
    zVar->setRange(-500,500);
    xVar->setValue(30);
    yVar->setValue(40);
    zVar->setValue(70);
    xVar->setGeometry(5,45,45,20);
    yVar->setGeometry(50,45,45,20);
    zVar->setGeometry(95,45,45,20);
    connect(xVar,SIGNAL(valueChanged(int)),this,SLOT(setXvar(int)));
    connect(yVar,SIGNAL(valueChanged(int)),this,SLOT(setYvar(int)));
    connect(zVar,SIGNAL(valueChanged(int)),this,SLOT(setZvar(int)));
    chbox->setText(tr("Perspective"));
    chbox->setGeometry(5,65,100,40);
    connect(chbox,SIGNAL(stateChanged(int)),this,SLOT(setPerspective(int)));

    gbox = new QGroupBox(this);
    gbox->setGeometry(10,120,145,195);
    gbox->setTitle(tr("Parameters of Conus"));

    lbl = new QLabel(gbox);
    lbl->setText(tr("Number grane"));
    lbl->setGeometry(5,10,100,40);
    QSpinBox *spbox = new QSpinBox(gbox);
    spbox->setValue(12);
    spbox->setRange(3,24);
    spbox->setGeometry(5,45,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setnumber(int)));

    lbl = new QLabel(gbox);
    lbl->setText(tr("Side size"));
    lbl->setGeometry(5,55,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setRange(5,40);
    spbox->setValue(15);
    spbox->setGeometry(5,90,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setX(int)));

    lbl = new QLabel(gbox);
    lbl->setText(tr("AngleB"));
    lbl->setGeometry(5,100,100,40);
    spbox = new QSpinBox(gbox);
    spbox->setRange(15,80);
    spbox->setValue(65);
    spbox->setGeometry(5,135,35,20);
    connect(spbox,SIGNAL(valueChanged(int)),this,SLOT(setAngleB(int)));

    chbox = new QCheckBox(gbox);
    chbox->setText(tr("Antialising"));
    chbox->setChecked(true);
    chbox->setGeometry(5,155,100,40);
    connect(chbox,SIGNAL(stateChanged(int)),this,SLOT(setRender(int)));
}

void MainWindow::setXvar(int i)
{
    view->dot[0] = i;
    view->repaint();
}

void MainWindow::setYvar(int i)
{
    view->dot[1] = i;
    view->repaint();
}

void MainWindow::setZvar(int i)
{
    view->dot[2] = i;
    view->repaint();
}

void MainWindow::setnumber(int i)
{
   view->edges = i;
   view->repaint();
}

void MainWindow::setRender(int state)
{
    view->state = state;
    view->repaint();
}

void MainWindow::setAngleB(int state)
{
    view->B = state;
    view->repaint();
}

void MainWindow::setX(int state)
{
    view->X = state;
    view->repaint();
}

void MainWindow::setPerspective(int state)
{
    view->persp = state;
    view->repaint();
}
