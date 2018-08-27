
#include <QMessageBox>

#include <engine/character.h>

#include "selectjobdialog.h"
#include "ui_selectjobdialog.h"

SelectJobDialog::SelectJobDialog(Character& c, QWidget *parent) : QDialog(parent), _char(c), _ui(new Ui::SelectJobDialog) {

    _ui->setupUi(this);

    _ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    _ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _ui->tableWidget->setDragEnabled(false);
}

SelectJobDialog::~SelectJobDialog() {

    delete _ui;
}

void SelectJobDialog::on_buttonBox_accepted() {

    std::string new_job;
    UIntegerType req_stats[Character::Attributes::statsCount()] = {};

    for(auto selected : _ui->tableWidget->selectedItems()) {

        if(selected->column() == 0) new_job = selected->text().toStdString();
        else req_stats[selected->column() - 1] = selected->text().toULongLong();
    }

    if(new_job.empty()) {

        QMessageBox::information(this, "SGOM Warning", "An option was not selected.");
        return;
    }

    bool can_change = true;
    for(UIntegerType i = 0; i < Character::Attributes::statsCount(); i++) {

        if(_char.attributes().stats[i] < req_stats[i]) {

            can_change = false;
            break;
        }
    }

    if(can_change) _char.setClass(new_job);
    else QMessageBox::information(this, "SGOM Warning", "Requirements not accomplished.");
}
