
#ifndef PROGRESSBARITEM_H
#define PROGRESSBARITEM_H

#include <QGraphicsItem>

#include "config/types.h"

/*!
 * \brief An item that display a progress bar, it can be used, for example, to display health bar
 */
class ProgressBarItem : public QGraphicsItem {

public:

    using PercentType = RealType;
    using ColorType = QColor;

    /*!
     * \brief Create an ProgressBarItem passing it's parent, if it have one
     * \brief The background color will be 'black' after contructing
     * \brief The foreground color will be 'red' after cosntructing
     * \param p QGraphicsItem that will be this object parent
     */
    ProgressBarItem(QGraphicsItem *p = nullptr) :
        QGraphicsItem(p), _percent(maxPercentage()), _bg_color(0, 0, 0), _fg_color(255, 0, 0), _w(0), _h(0) {}

    constexpr PercentType maxPercentage() const { return 100; }
    constexpr PercentType minPercentage() const { return 0; }

    /*!
     * \brief Set a value to represent how much of the progress bar is filled
     * \param p Percentage displayed by the progress bar, it should be between minPercentage() and maxPercentage()
     * \sa value()
     */
    void setValue(PercentType p) {

        if(p > maxPercentage()) _percent = maxPercentage();
        else if(p < minPercentage()) _percent = minPercentage();
        else _percent = p;
    }

    /*!
     * \brief Returns the progress bar percentage
     * \return Value of the percentage that is beeing displayed in the progress bar
     */
    PercentType value() const { return _percent; }

    /*!
     * \brief Set the color of the non filled portion of the progress bar
     * \param c The color that will be displayed in the non filled portion
     */
    void setBgColor(ColorType c) { _bg_color = c; }

    /*!
     * \brief Return the background color
     * \return The background color
     */
    ColorType bgColor() const { return _bg_color; }

    /*!
     * \brief Set the color of the filled portion of the progress bar
     * \param c The color that will be displayed in the filled portion
     */
    void setFgColor(ColorType c) { _fg_color = c; }

    /*!
     * \brief Return the foreground color
     * \return The foreground color
     */
    ColorType fgColor() const { return _fg_color; }

    /*!
     * \brief Set the progress bar width
     * \param w Width value
     */
    void setWidth(UIntegerType w) { _w = w; }

    /*!
     * \brief Return the width of the progress bar
     * \return The width of the progress bar
     */
    UIntegerType width() const { return _w; }

    /*!
     * \brief Set the progress bar height
     * \param h Height value
     */
    void setHeight(UIntegerType h) { _h = h; }

    /*!
     * \brief Return the height of the progress bar
     * \return The height of the progress bar
     */
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
