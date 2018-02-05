#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QGraphicsView>

class BattleView : public QGraphicsView {

public:

    class Handler {

    public:
        virtual void battleViewMouseMoveEvent(QMouseEvent *) {}
        virtual void battleViewMousePressEvent(QMouseEvent *) {}
        virtual void battleViewMouseReleaseEvent(QMouseEvent *) {}
    };

    BattleView(Handler *handler, QWidget * parent = 0) : QGraphicsView(parent), _handler(handler) {}
    BattleView(Handler *handler, QGraphicsScene * scene, QWidget * parent = 0) : QGraphicsView(scene, parent), _handler(handler) {}

protected:

    virtual void mouseMoveEvent(QMouseEvent *event) override { if(_handler) _handler->battleViewMouseMoveEvent(event); }
    virtual void mousePressEvent(QMouseEvent *event) override { if(_handler) _handler->battleViewMousePressEvent(event); }
    virtual void mouseReleaseEvent(QMouseEvent *event) override { if(_handler) _handler->battleViewMouseReleaseEvent(event); }

private:

    Handler *_handler;

};

#endif // BATTLEVIEW_H
