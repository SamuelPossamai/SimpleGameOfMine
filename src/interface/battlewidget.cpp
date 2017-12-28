
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>

#include "traits.h"
#include "battlewidget.h"

BattleWidget::BattleWidget(QWidget *parent /* = nullptr */) : QWidget(parent) {

    _obj = new AnimatedObject;

    _gview = new QGraphicsView(new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height), this);

    _gview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap im1 = QPixmap(":/testimage.png").scaled(100, 100);
    QPixmap im2 = QPixmap(":/testimage_red.png").scaled(100, 100);

    Animation animation1(1000, true);

    UIntegerType last = 0, i = 0;
    while(last < 1000){

        animation1.addImage(im1, last + 3*i);

        last += 6*i;
        animation1.addImage(im2, last);

        if(last < 500) i++;
        else i--;
    }

    _obj->addAnimation(animation1);
    _obj->selectAnimation(0);

    _obj->show();

    step();

   _gview->scene()->addItem(_obj);

   _timer = new QTimer(this);

   _timer->setInterval(10);

   QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

   _timer->start();
}

void BattleWidget::step(){

    _obj->step();

    double x_base = 50;
    double y_base = 50;
    double x_mul = 3.9;
    double y_mul = 1.65;

    _obj->setRotation(int(_obj->rotation() + 1)%360);
    if(_obj->rotation() < 180) _obj->setPos(x_base + x_mul*_obj->rotation(), y_base + y_mul*_obj->rotation());
    else _obj->setPos(x_base + 360*x_mul - x_mul*_obj->rotation(), y_base + 360*y_mul - y_mul*_obj->rotation());
}
