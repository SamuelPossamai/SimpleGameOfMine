
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget : public QWidget {

    Q_OBJECT

public:

    explicit ImageWidget(QWidget *parent = nullptr) : ImageWidget(QImage(), parent) {}
    explicit ImageWidget(const QImage& im, QWidget *parent = nullptr) : QWidget(parent), _im(im),
        _bg(Qt::white), _fg(Qt::lightGray) {}
    virtual ~ImageWidget() override {}

    void setBackground(QColor c) { _bg = c ; update(); }
    QColor background() const { return _bg; }

    void setForeground(QColor c) { _fg = c ; update(); }
    QColor foreground() const { return _fg; }

    void setImage(const QImage& im) { _im = im; update(); }
    QImage image() const { return _im; }

protected:

    virtual void paintEvent(QPaintEvent *) override;

private:

    QImage _im;
    QColor _bg, _fg;
};

#endif // IMAGEWIDGET_H
