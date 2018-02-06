
#include <QPushButton>

#include "menu.h"
#include "traits.h"
#include "mainwindow.h"
#include "battlewidget.h"

Menu::Menu(MainWindow *parent /* = nullptr */) : QWidget(parent) {

    auto start_button = new QPushButton("Start", this);
    start_button->setFocusPolicy(Qt::NoFocus);
    start_button->setGeometry(Traits<Menu>::buttonsX, Traits<Menu>::buttonsY,
                              Traits<Menu>::buttonsWidth, Traits<Menu>::buttonsHeight);

    QObject::connect(start_button, &QPushButton::clicked, this, &Menu::_start_button_clicked);

    start_button->show();
}

void Menu::setParent(MainWindow *parent){

    QWidget::setParent(parent);
}

void Menu::_start_button_clicked(){

    static_cast<MainWindow *>(parent())->switchWidget(new BattleWidget);
}
