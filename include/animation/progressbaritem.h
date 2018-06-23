
#ifndef PROGRESSBARITEM_H
#define PROGRESSBARITEM_H

#include <QGraphicsItem>

#include "config/types.h"

class ProgressBarItem : public QGraphicsItem {

public:

    using PercentType = RealType;
    using ColorType = QColor;

    ProgressBarItem(QGraphicsItem *p = nullptr) :
        QGraphicsItem(p), _percent(maxPercentage()), _bg_color(0, 0, 0), _fg_color(255, 0, 0), _w(0), _h(0) {}

    constexpr PercentType maxPercentage() const { return 100; }
    constexpr PercentType minPercentage() const { return 0; }

    void setValue(PercentType p) {

        if(p > maxPercentage()) _percent = maxPercentage();
        else if(p < minPercentage()) _percent = minPercentage();
        else _percent = p;
    }

    PercentType value() const { return _percent; }

    void setBgColor(ColorType c) { _bg_color = c; }
    ColorType bgColor() const { return _bg_color; }

    void setFgColor(ColorType c) { _fg_color = c; }
    ColorType fgColor() const { return _fg_color; }

    void setWidth(UIntegerType w) { _w = w; }
    UIntegerType width() const { return _w; }

    void setHeight(UIntegerType h) { _h = h; }
    UIntegerType height() const { return _h; }

protected:

    QRectF boundingRect() const override { return QRectF(x(), y(), _w, _h); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:

    PercentType _percent;
    ColorType _bg_color;
    ColorType _fg_color;
    UIntegerType _w, _h;
};

#endif // PROGRESSBARITEM_H
