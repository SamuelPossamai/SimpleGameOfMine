
#include <QPainter>

#include "partialimageitem.h"

void PartialImageItem::setValue(RealType new_value) {

    auto old_val = _value;

    if(new_value < 0) _value = 0;
    else if(new_value > 100) _value = 1;
    else _value = new_value/100;

    if(old_val != _value) _im = _original_im.copy(0, (1 - _value)*_im.height(), _im.width(), _im.height());
}

void PartialImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    QRect r = _im.rect();

    r.setY((1 - _value)*_original_im.height());
    r.setHeight(r.height() + r.y());

    painter->drawImage(r, _im);
}
