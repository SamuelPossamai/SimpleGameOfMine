
#include "graphicsview.h"

void GraphicsView::mouseMoveEvent(QMouseEvent *event) {

    if(_handler) _handler->graphicsViewMouseMoveEvent(event);

    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event) {

    if(_handler) _handler->graphicsViewMousePressEvent(event);

    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event) {

    if(_handler) _handler->graphicsViewMouseReleaseEvent(event);

    QGraphicsView::mouseReleaseEvent(event);
}
