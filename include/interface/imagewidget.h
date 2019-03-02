
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget : public QWidget {

    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage)

public:

    explicit ImageWidget(QWidget *parent = nullptr) : ImageWidget(QImage(), parent) {}
    explicit ImageWidget(const QImage& im, QWidget *parent = nullptr) : QWidget(parent), _im(im) {}
    virtual ~ImageWidget() override {}

    void setImage(const QImage& im) { _im = im; update(); }
    QImage image() const { return _im; }

protected:

    virtual void paintEvent(QPaintEvent *) override;

private:

    QImage _im;
};

#endif // IMAGEWIDGET_H
