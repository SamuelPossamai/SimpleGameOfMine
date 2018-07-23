
#include <QLabel>
#include <QPushButton>

#include "helpwidget.h"
#include "interface_traits.h"
#include "mainwindow.h"

HelpWidget::HelpWidget(MainWindow *w) : MainWidget(w) {

    QPalette pal = palette();

    pal.setColor(QPalette::Background, Qt::white);

    setPalette(pal);
    setAutoFillBackground(true);

    QLabel *title = new QLabel("Help", this);

    title->setAlignment(Qt::AlignCenter);
    title->setGeometry(0, 0, Traits<MainWindow>::width, 0.3*Traits<MainWindow>::height);

    QFont font = title->font();

    font.setPointSize(32);
    font.setBold(true);

    title->setFont(font);

    title->show();

    QLabel *text = new QLabel("Texto\nTexto2\nTexto3", this);

    text->setGeometry(0.25*Traits<MainWindow>::width, 0.35*Traits<MainWindow>::height,
                      0.5*Traits<MainWindow>::width, 0.3*Traits<MainWindow>::height);

    text->show();

    QPushButton *ret_button = new QPushButton("Return", this);

    ret_button->setGeometry(0, 0.9*Traits<MainWindow>::height,
                            0.1*Traits<MainWindow>::width, 0.1*Traits<MainWindow>::height);

    QObject::connect(ret_button, &QPushButton::clicked, this, &HelpWidget::_return_button_pressed);

    ret_button->setFocusPolicy(Qt::NoFocus);

    ret_button->show();
}

void HelpWidget::_return_button_pressed() {

    parent()->popWidget();
}
