#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <QWidget>
#include <QGraphicsView>

#include "types.h"
#include "animatedobject.h"

class BattleWidget : public QWidget {

    Q_OBJECT

public:

    BattleWidget(QWidget *parent = nullptr);

public slots:

    void step();

private:

    QGraphicsView *_gview;
    QTimer *_timer;

    AnimatedObject *_obj;
};

#endif // BATTLEWIDGET_H
