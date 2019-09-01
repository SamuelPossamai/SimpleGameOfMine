
#include <QStyleOption>
#include <QPainter>

#include "imagewidget.h"

void ImageWidget::paintEvent(QPaintEvent *) {

    QStyleOption opt;
    opt.init(this);

    QPainter painter(this);

    painter.setPen(opt.palette.background().color());
    painter.setBrush(opt.palette.background().color());

    painter.drawRect(this->rect());

    QRegion r(this->rect(), QRegion::Ellipse);
    painter.setClipRegion(r);

    painter.setPen(opt.palette.foreground().color());
    painter.setBrush(opt.palette.foreground());

    painter.drawEllipse(this->rect());
    painter.drawImage(this->rect(), _im);
}
