#include "graphic.h"

Graphic::Graphic(QWidget *wgt, int x, int y, int z, int edge) : QWidget(wgt)
{
    dot << x << y << z << 1;        //установка координат точки обзора
    edges = edge;                   //установка кол-ва граней, 12
    state = 1;                      //флаг для включения сглаживая
    B = 65;                         //установка угла по заданию
    X = 15;                         //установка длины основания
    persp = false;
}

void Graphic::Init()                //преднастройка перед рисованием
{
    map.dots.clear();               //очистка точек мировой сис-мы координат (МСК)
    map.rebra.clear();              //очистка ребер МСК
    int R = 2*X/tan(M_PI/edges);    //расчет радиуса конуса
    int H = R*1/tan(B*M_PI/180);    //расчет высоты конуса
    /*нахождение точек на основании конуса*/
    qreal grad = 360/edges;         //шаг по углу
    for(int i = 0; i < edges; i++)
    {
        map.addDot(R*cos(i*grad*M_PI/180),R*sin(i*grad*M_PI/180),0);    //добавление точек МСК
        map.addRebro(i,i+1);                                            //добавление ребер наосновании
        map.addRebro(i,edges);                                          //добавление ребер основание-вершина
    }
    map.addRebro(0,edges-1);
    map.addDot(0,0,H);             //добавление точки вершины
    /*расчет необходимых данных для нахождения cos и sin*/
    qreal a = sqrt(pow(dot[0],2) + pow(dot[1],2));
    qreal e = sqrt(pow(dot[0],2) + pow(dot[1],2) + pow(dot[2],2));
    /*преобразования систем координат по методике*/
    map.setAngleZ(dot[0]/a,dot[1]/a);           //поворот оси по Z
    map.setAngleY(dot[2]/e,a/e);                //поворот оси по У
    map.setPos(-e,0,0);                         //перенос начала координат
    map.changeOSI();                            //изменение осей
    /*перспективное трансформирование МСК по необходимости*/
    if (persp)
    {
        QVector<QVector<qreal> >::iterator p;
        for (p = map.dots.begin(); p!=map.dots.end(); p++)
        {
            if ((*p)[2] == 0) continue;
           (*p)[0] = e*((*p)[0]/(*p)[2]);
           (*p)[1] = e*((*p)[1]/(*p)[2]);
        }
    }
    Xpos = width()/2;       //расчет центра...
    Ypos = height()/2;      //...экрана
}

void Graphic::paintEvent(QPaintEvent *pe) //функция прорисовки
{
    Init();                 //подготовка к рисованию
    painter.begin(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));  //кисть
    painter.drawRect(QRect(0,0,width(),height()));          //закраска всей облисти белым цветом
    if(state) painter.setRenderHint(QPainter::Antialiasing, true);  //включение сглаживания
    else      painter.setRenderHint(QPainter::Antialiasing, false); //выключеие сглаживания
    /*рисование конуса по ребрам*/
    QList<QPair<int,int> >::iterator p; //указатель на массив ребер
    for (p = map.rebra.begin(); p!=map.rebra.end(); p++)
    {
        int start = (*p).first;     //начальная точка ребра
        int end   = (*p).second;    //конечная точка ребра
        /*рисование линии, соединяющей эти точки*/
        painter.drawLine(QPoint(map.dots[start][0]+Xpos,Ypos-map.dots[start][1]),QPoint(map.dots[end][0]+Xpos,Ypos-map.dots[end][1]));
    }
    painter.end();
}
