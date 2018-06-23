
#include <QPainter>

#include "animation/progressbaritem.h"

void ProgressBarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QRectF out_rect = boundingRect();

    painter->setBrush(QBrush(_bg_color));
    painter->drawRect(out_rect);

    painter->setBrush(QBrush(_fg_color));
    painter->drawRect(x(), y(), value()*out_rect.width()/maxPercentage(), out_rect.height());
}
