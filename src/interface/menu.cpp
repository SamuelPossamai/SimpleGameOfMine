
#include "ui_menu.h"

#include "menu.h"
#include "selectuserinterface.h"
#include "characterselectionscreen.h"
#include "helpwidget.h"
#include "librarywidget.h"

Menu::Menu(MainWindow *parent /* = nullptr */) : MainWidget(parent), _ui(new Ui::Menu) {

    _ui->setupUi(this);
}

void Menu::activate() {

    _ui->startButton->setFocus();
    _ui->testButton->hide();
}

Menu::~Menu() {

    delete _ui;
}

void Menu::on_startButton_clicked() {

    //parent()->pushWidget(new SelectUserInterface);
    parent()->pushWidget(new CharacterSelectionScreen({1, 3}));
}

void Menu::on_helpButton_clicked() {

    parent()->pushWidget(new HelpWidget);
}

void Menu::on_testButton_clicked() {

}

void Menu::on_libraryButton_clicked() {

    parent()->pushWidget(new LibraryWidget);
}
