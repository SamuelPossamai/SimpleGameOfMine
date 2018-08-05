
#ifndef PARTIALIMAGEITEM_H
#define PARTIALIMAGEITEM_H

#include <QGraphicsItem>

#include <config/types.h>

class PartialImageItem : public QGraphicsItem {

public:

    explicit PartialImageItem(QGraphicsItem *p = nullptr) : PartialImageItem(QImage(), p) {}
    explicit PartialImageItem(const QImage& image, QGraphicsItem *p = nullptr) :
        QGraphicsItem(p), _im(image), _original_im(image), _value(1) {}

    void setValue(RealType new_value);
    RealType value() const { return _value; }

protected:

    QRectF boundingRect() const override { return QRectF(0, 0, _im.width(), 2*_im.height()); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:

    QImage _im;
    QImage _original_im;

    RealType _value;
};

#endif // PARTIALIMAGEITEM_H
