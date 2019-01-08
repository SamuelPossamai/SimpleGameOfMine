
#include <QPainter>

#include "itemimagewidget.h"

ItemImageWidget::~ItemImageWidget() {

}

void ItemImageWidget::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    painter.drawImage(this->rect(), _img);

    painter.drawText(this->rect(), Qt::AlignRight | Qt::AlignBottom, QString("%0").arg(_qtd));
}
