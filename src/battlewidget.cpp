
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>

#include "traits.h"
#include "battlewidget.h"
#include "animation.h"

BattleWidget::BattleWidget(QWidget *parent /* = nullptr */) : QWidget(parent), _animation(nullptr, 1000, true) {

    _gview = new QGraphicsView(new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height), this);

    _animation.setScene(_gview->scene());

    QPixmap im1 = QPixmap(":/testimage.png").scaled(100, 100);
    QPixmap im2 = QPixmap(":/testimage_red.png").scaled(100, 100);

    auto *item = new QGraphicsPixmapItem(QPixmap(":/testimage.png").scaled(100, 100));

    _animation.setObject(&_obj);

    UIntegerType last = 0, i = 0;
    while(last < 1000){

        _animation.addImage(im1, last + 3*i);

        last += 6*i;
        _animation.addImage(im2, last);

        if(last < 500) i++;
        else i--;
    }

    _animation.start();

    step();

   _gview->scene()->addItem(item);

   _timer = new QTimer(this);

   _timer->setInterval(10);

   QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

   _timer->start();
}

void BattleWidget::step(){

    _animation.step();

    _obj.setAngle((_obj.angle() + 1)%360);
    if(_obj.angle() < 180) _obj.setPos(100 + _obj.angle(), 100 + _obj.angle());
    else _obj.setPos(460 - _obj.angle(), 460 - _obj.angle());

    _animation.update();
}
