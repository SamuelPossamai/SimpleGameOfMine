
#ifndef ITEMIMAGEWIDGET_H
#define ITEMIMAGEWIDGET_H

#include <QWidget>

#include "types.h"

class ItemImageWidget : public QWidget {

    Q_OBJECT

public:

    ItemImageWidget() : _img(), _qtd(0) {}
    explicit ItemImageWidget(QImage im, UIntegerType qtd = 0) : _img(im), _qtd(qtd) {}
    virtual ~ItemImageWidget() override;

protected:

    virtual void paintEvent(QPaintEvent *) override;

private:

    QImage _img;
    UIntegerType _qtd;
};

#endif // ITEMIMAGEWIDGET_H
