
#include "battleview.h"

void BattleView::mouseMoveEvent(QMouseEvent *event) {

    if(_handler) _handler->battleViewMouseMoveEvent(event);

    QGraphicsView::mouseMoveEvent(event);
}

void BattleView::mousePressEvent(QMouseEvent *event) {

    if(_handler) _handler->battleViewMousePressEvent(event);

    QGraphicsView::mousePressEvent(event);
}

void BattleView::mouseReleaseEvent(QMouseEvent *event) {

    if(_handler) _handler->battleViewMouseReleaseEvent(event);

    QGraphicsView::mouseReleaseEvent(event);
}
