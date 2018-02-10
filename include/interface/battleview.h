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

    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:

    Handler *_handler;

};

#endif // BATTLEVIEW_H
