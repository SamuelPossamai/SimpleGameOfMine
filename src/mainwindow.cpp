
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>

#include "traits.h"
#include "mainwindow.h"
#include "animation.h"

void pos_image(QPoint p, double angle, QGraphicsPixmapItem *item){

    item->setRotation(angle);
    item->setOffset(-item->pixmap().width()/2, -item->pixmap().height()/2);
    item->setPos(p.x() + item->pixmap().width()/2, p.y() + item->pixmap().height()/2);
}

MainWindow::MainWindow() : _angle(0), _animation(100, true) {

    setGeometry(Traits<MainWindow>::x, Traits<MainWindow>::y, Traits<MainWindow>::width, Traits<MainWindow>::height);

    _gview = new QGraphicsView(new QGraphicsScene(), this);

    setCentralWidget(_gview);

    auto *item = new QGraphicsPixmapItem(QPixmap(":/testimage_red.png").scaled(100, 100));
    auto *item2 = new QGraphicsPixmapItem(QPixmap(":/testimage.png").scaled(100, 100));
    auto *item3 = new QGraphicsPixmapItem(QPixmap(":/testimage.png").scaled(100, 100));

    _animation.addItem(item, 0);
    _animation.addItem(item2, 80);

    _animation.start();

    step();

   _gview->scene()->addItem(item);
   _gview->scene()->addItem(item2);
   _gview->scene()->addItem(item3);

   _timer = new QTimer(this);

   _timer->setInterval(10);

   QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

   _timer->start();
}

void MainWindow::step(){

    _animation.step();

    pos_image({100, 100}, (++_angle)%360, reinterpret_cast<QGraphicsPixmapItem *>(_animation.item()));
}
