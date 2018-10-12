
#include <QPainter>

#include "imagewidget.h"

void ImageWidget::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    painter.setPen(_bg);
    painter.setBrush(_bg);

    painter.drawRect(this->rect());

    QRegion r(this->rect(), QRegion::Ellipse);
    painter.setClipRegion(r);

    painter.setPen(_fg);
    painter.setBrush(_fg);

    painter.drawEllipse(this->rect());
    painter.drawImage(this->rect(), _im);
}
