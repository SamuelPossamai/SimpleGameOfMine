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

    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    void translate(IntegerType dx, IntegerType dy);

public slots:

    void step();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

private:

    void _set_zoom(RealType zoom) { _gview->scale(zoom, zoom); }

    QGraphicsView *_gview;
    QTimer *_timer;

    AnimatedObject *_obj;
    Map *_map;
};

#endif // BATTLEWIDGET_H
