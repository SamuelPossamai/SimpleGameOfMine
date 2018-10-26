
#include <config/sgomfiles.h>
#include <engine/character.h>

#include <QMessageBox>
#include <QInputDialog>

#include "ui_selectuserinterface.h"
#include "selectuserinterface.h"

SelectUserInterface::SelectUserInterface(const utility::Interval<UIntegerType>& n_characters /* = {1, 3} */,
                                         MainWindow *parent /* = nullptr */) :
    SelectUserInterfaceBase(n_characters, parent), _ui(new Ui::SelectUserInterface) {

    this->setPalette(QPalette(Qt::white));
    this->setAutoFillBackground(true);

    _ui->setupUi(this);

    _ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    _ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _ui->tableWidget->setDragEnabled(false);
}

void SelectUserInterface::activate() {

    SGOMFiles *sgomf = SGOMFiles::get();

    auto chars = sgomf->characters();

    _ui->tableWidget->clearContents();

    _ui->tableWidget->setRowCount(chars.size());

    for(UIntegerType i = 0; i < chars.size(); i++) {

        const std::string& name = chars[i];

        Character ch(name);

        _ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(name)));
        _ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ch.className())));
        _ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(ch.level())));

        for(UIntegerType j = 0; j < Character::Attributes::statsCount(); j++) {

            _ui->tableWidget->setItem(i, j + 3, new QTableWidgetItem(QString::number(ch.attributes().getAttributeValue(j))));
        }
    }
}

void SelectUserInterface::on_selectButton_clicked() {

    std::vector characters = _get_selecteds();

    if(finalize(characters)) return;

    QMessageBox::information(this, "SGOM Warning",
                             QString("You must select between %0 and %1 characters").arg(minCharacters()).arg(maxCharacters()));
}

void SelectUserInterface::on_deleteButton_clicked() {

    std::vector characters = _get_selecteds();

    for(const std::string& ch : characters) SGOMFiles::get()->removeChar(ch);

    this->activate();
}


void SelectUserInterface::on_newButton_clicked() {

    std::string name = QInputDialog::getText(this, "SGOM Input", "New character name?").toStdString();

    const char *info_message = nullptr;

    if(name.empty()) info_message = "Can't create a character without a name";
    else if(SGOMFiles::get()->charExists(name)) info_message = "There is already a character with this name.";

    if(info_message){

        QMessageBox::information(this, "SGOM Warning", info_message);

        return;
    }

    Character::newChar(name, "fighter");

    this->activate();
}

void SelectUserInterface::on_returnButton_clicked() {

    parent()->popWidget();
}

UIntegerType SelectUserInterface::_selected_count() const {

    return _ui->tableWidget->selectedItems().size()/_ui->tableWidget->columnCount();
}

std::vector<std::string> SelectUserInterface::_get_selecteds() const {

    QList<QTableWidgetItem *> l = _ui->tableWidget->selectedItems();

    std::vector<std::string> characters;
    for(auto *item : l) if(item->column() == 0) characters.push_back(item->text().toStdString());

    return characters;
}
