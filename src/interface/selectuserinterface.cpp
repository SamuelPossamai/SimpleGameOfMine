
#include <config/sgomfiles.h>
#include <engine/character.h>

#include <QHeaderView>
#include <QPalette>
#include <QMessageBox>
#include <QInputDialog>

#include "selectuserinterface.h"
#include "gamedefaultscreen.h"

SelectUserInterface::SelectUserInterface(MainWindow *parent /* = nullptr */) : MainWidget(parent) {

    QPalette pal(Qt::white);

    this->setPalette(pal);
    this->setAutoFillBackground(true);

    _list = new QTableWidget(this);

    _list->verticalHeader()->setVisible(false);
    _list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _list->setSelectionBehavior(QAbstractItemView::SelectRows);
    _list->setSelectionMode(QAbstractItemView::MultiSelection);
    _list->setDragEnabled(false);
    _list->setEditTriggers(QAbstractItemView::NoEditTriggers);

    _list->setColumnCount(7);

    _list->setHorizontalHeaderLabels({ "Name", "Class", "Level", "Strength", "Vitality", "Dexterity", "Agility" });

    _char_label = new QLabel("Characters", this);

    _char_label->setPalette(pal);
    _char_label->setAutoFillBackground(true);

    _char_label->setAlignment(Qt::AlignCenter);

    _buttons.push_back(new QPushButton("Return", this));
    _buttons.push_back(new QPushButton("Delete", this));
    _buttons.push_back(new QPushButton("New", this));
    _buttons.push_back(new QPushButton("Select", this));

    QObject::connect(_buttons[0], &QPushButton::clicked, this, &SelectUserInterface::_return_button_clicked);
    QObject::connect(_buttons[1], &QPushButton::clicked, this, &SelectUserInterface::_delete_button_clicked);
    QObject::connect(_buttons[2], &QPushButton::clicked, this, &SelectUserInterface::_new_button_clicked);
    QObject::connect(_buttons[3], &QPushButton::clicked, this, &SelectUserInterface::_select_button_clicked);
}

void SelectUserInterface::activate() {

    SGOMFiles *sgomf = SGOMFiles::get();

    auto chars = sgomf->characters();

    _list->clearContents();

    _list->setRowCount(chars.size());

    for(UIntegerType i = 0; i < chars.size(); i++) {

        const std::string& name = chars[i];

        Character ch(name);

        _list->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(name)));
        _list->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ch.className())));
        _list->setItem(i, 2, new QTableWidgetItem(QString::number(ch.level())));
        _list->setItem(i, 3, new QTableWidgetItem(QString::number(ch.attributes().strength())));
        _list->setItem(i, 4, new QTableWidgetItem(QString::number(ch.attributes().vitality())));
        _list->setItem(i, 5, new QTableWidgetItem(QString::number(ch.attributes().dexterity())));
        _list->setItem(i, 6, new QTableWidgetItem(QString::number(ch.attributes().agility())));
    }

    auto rect = this->geometry();
    rect.setY(rect.height()*0.1);
    rect.setHeight(rect.height()*0.8);

    _list->setGeometry(rect);
    _list->show();

    rect = this->geometry();
    rect.setHeight(rect.height()*0.1);

    _char_label->setGeometry(rect);
    _char_label->show();

    rect = this->geometry();
    rect.setY(rect.height()*0.85);
    rect.setX(rect.x() + 10);
    rect.setHeight(rect.height()*0.10);

    const UIntegerType x_offset = rect.width()/_buttons.size();

    for(QPushButton *button : _buttons) {

        button->setGeometry(rect);
        button->setFixedSize(x_offset - 10, 7*rect.height());
        rect.setX(rect.x() + x_offset);
        button->show();
    }
}

void SelectUserInterface::_select_button_clicked() {

    const UIntegerType selected_count = _selected_count();

    static const char *info_title = "SGOM Warning";

    const char *fail_message = nullptr;

    if(selected_count == 0) fail_message = "You need to select at least one.";
    else if(selected_count > 3) fail_message = "You can select three characters at most.";

    if(fail_message) {

        QMessageBox::information(this, info_title, fail_message);

        return;
    }

    std::vector characters = _get_selecteds();

    parent()->swapWidget(new GameDefaultScreen(characters));
}

void SelectUserInterface::_delete_button_clicked() {

    std::vector characters = _get_selecteds();

    for(const std::string& ch : characters) SGOMFiles::get()->removeChar(ch);

    this->activate();
}

void SelectUserInterface::_new_button_clicked() {

    std::string name = QInputDialog::getText(this, "SGOM Input", "New character name?").toStdString();

    if(SGOMFiles::get()->charExists(name)) {

        QMessageBox::information(this, "SGOM Warning", "There is already a character with this name.");

        return;
    }

    Character::newChar(name, "fighter");

    this->activate();
}

void SelectUserInterface::_return_button_clicked() {

    parent()->popWidget();
}

UIntegerType SelectUserInterface::_selected_count() const {

    return _list->selectedItems().size()/_list->columnCount();
}

std::vector<std::string> SelectUserInterface::_get_selecteds() const {

    QList<QTableWidgetItem *> l = _list->selectedItems();

    std::vector<std::string> characters;
    for(auto *item : l) if(item->column() == 0) characters.push_back(item->text().toStdString());

    return characters;
}

