
#include <QStyle>
#include <QMessageBox>
#include <QInputDialog>

#include <config/sgomfiles.h>

#include "characterselectionscreen.h"
#include "ui_characterselectionscreen.h"

CharacterSelectionScreen::CharacterSelectionScreen(const utility::Interval<UIntegerType>& n_characters, MainWindow *parent) :
    SelectUserInterfaceBase(n_characters, parent), ui(new Ui::CharacterSelectionScreen), _cur(0) {

    ui->setupUi(this);

    _char_names = SGOMFiles::get()->characters();

    _update_image();
}

CharacterSelectionScreen::~CharacterSelectionScreen() {

    delete ui;
}

void CharacterSelectionScreen::_update_image() {

    bool is_valid = _selecteds.size() >= minCharacters() && _selecteds.size() <= maxCharacters();

    ui->selNumLabel->setText(QString("Selecteds: %1/%2").arg(_selecteds.size()).arg(maxCharacters()));

    ui->selNumLabel->setProperty("selectValid", is_valid);
    ui->selNumLabel->style()->unpolish(ui->selNumLabel);
    ui->selNumLabel->style()->polish(ui->selNumLabel);

    ui->goButton->setEnabled(is_valid);

    bool valid_char = _cur < _char_names.size();

    ui->selectButton->setEnabled(valid_char);
    ui->deleteButton->setEnabled(valid_char);
    ui->nextButton->setVisible(_char_names.size() > 1);
    ui->prevButton->setVisible(_char_names.size() > 1);

    if(_char_names.empty()) {

        ui->classNameLabel->setText("-");

        ui->iconWidget->setImage(QImage(":/icons/unknown_icon.png"));

        return;
    }

    if(_is_selected(_char_names[_cur])) ui->selectButton->setText("Select");
    else ui->selectButton->setText("Unselect");

    Character c(_char_names[_cur]);

    ui->classNameLabel->setText((" Lv %1 - " + QString::fromStdString(c.name())).arg(c.level()));

    QImage im(QString::fromStdString(":/icons/" + c.className() + ".png"));

    if(im.isNull()) im = QImage(":/icons/unknown_icon.png");

    ui->iconWidget->setImage(im);
}

void CharacterSelectionScreen::on_prevButton_clicked() {

    if(_cur == 0) _cur = _char_names.size() - 1;
    else _cur--;

    _update_image();
}

void CharacterSelectionScreen::on_nextButton_clicked() {

    if(_cur == _char_names.size() - 1) _cur = 0;
    else _cur++;

    _update_image();
}

void CharacterSelectionScreen::on_returnButton_clicked() {

    parent()->popWidget();
}

void CharacterSelectionScreen::on_selectButton_clicked() {

    auto it = std::find(_selecteds.begin(), _selecteds.end(), _char_names[_cur]);

    if(it == _selecteds.end()) _selecteds.push_back(_char_names[_cur]);
    else _selecteds.erase(it);

    _update_image();
}

void CharacterSelectionScreen::on_goButton_clicked() {

    if(finalize(_selecteds)) return;
}

void CharacterSelectionScreen::on_deleteButton_clicked() {

    if(QMessageBox::question(this, "SGOM Dialog", "Are you sure that you want to delete this character?") == QMessageBox::Yes) {

        auto sel_it = std::find(_selecteds.begin(), _selecteds.end(), _char_names[_cur]);

        if(sel_it != _selecteds.end()) _selecteds.erase(sel_it);

        SGOMFiles::get()->removeChar(_char_names[_cur]);

        _char_names = SGOMFiles::get()->characters();

        if(_cur == _char_names.size()) _cur = 0;

        _update_image();
    }
}

void CharacterSelectionScreen::on_newButton_clicked() {

    std::string name = QInputDialog::getText(this, "SGOM Input", "New character name?").toStdString();

    const char *info_message = nullptr;

    if(name.empty()) info_message = "Can't create a character without a name";
    else if(SGOMFiles::get()->charExists(name)) info_message = "There is already a character with this name.";

    if(info_message){

        QMessageBox::information(this, "SGOM Warning", info_message);

        return;
    }

    Character::newChar(name, "fighter");

    std::string cur_name;

    if(_cur < _char_names.size()) cur_name = _char_names[_cur];

    _char_names = SGOMFiles::get()->characters();

    if(cur_name.empty()) _cur = 0;
    else _cur = UIntegerType(std::distance(_char_names.begin(), std::find(_char_names.begin(), _char_names.end(), cur_name)));

    _update_image();
}
