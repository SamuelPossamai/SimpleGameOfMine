
#include "ui_menu.h"

#include "menu.h"
#include "configurationscreen.h"
#include "selectuserinterfacebase.h"
#include "helpwidget.h"
#include "librarywidget.h"

Menu::Menu(MainWindow *parent /* = nullptr */) : MainWidget(parent), _ui(new Ui::Menu) {

    _ui->setupUi(this);
}

void Menu::activate() {

    _ui->startButton->setFocus();
}

Menu::~Menu() {

    delete _ui;
}

void Menu::on_startButton_clicked() {

    parent()->pushWidget(SelectUserInterfaceBase::create({1, 3}));
}

void Menu::on_helpButton_clicked() {

    parent()->pushWidget(new HelpWidget);
}

void Menu::on_libraryButton_clicked() {

    parent()->pushWidget(new LibraryWidget);
}

void Menu::on_configButton_clicked() {

    parent()->pushWidget(new ConfigurationScreen);
}
