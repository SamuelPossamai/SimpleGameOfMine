
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

#include "traits.h"
#include "battlewidget.h"
#include "battleengine.h"
#include "unit.h"

BattleWidget::BattleWidget(QWidget *parent /* = nullptr */) : QWidget(parent) {

    _gview = new QGraphicsView(new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height), this);

    _gview->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    _gview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _engine = new BattleEngine();
    _engine->setScene(_gview->scene());

    Unit *unit1 = new Unit(new UnitInfo);
    Unit *unit2 = new Unit(new UnitInfo);

    unit1->setX(300);
    unit1->setY(140);

    unit1->setAngle(3.14/4);

    unit2->setX(600);
    unit2->setY(140);

    unit2->setAngle(0);

    _engine->addUnit(unit1);
    _engine->addUnit(unit2);

    QPixmap im1 = QPixmap(":/testimage.png").scaled(100, 100);
    QPixmap im2 = QPixmap(":/testimage_red.png").scaled(100, 100);
    QPixmap im3 = im1.scaled(100, 50);

    Animation animation1(100);
    Animation animation2(1000);

    animation1.addImage(im1, 0);
    animation1.addImage(im2, 50);

    animation2.addImage(im3, 0);

    unit1->addAnimation(animation1);
    unit2->addAnimation(animation2);

   _timer = new QTimer(this);

   _timer->setInterval(10);

   QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

   _timer->start();
}

void BattleWidget::step(){

    _engine->step();
}

void BattleWidget::keyPressEvent(QKeyEvent *event) {

    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier){

        if(event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) zoomIn();
        else if(event->key() == Qt::Key_Minus) zoomOut();
    }
}
