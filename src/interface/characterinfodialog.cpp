
#include <engine/unitinfo.h>
#include <engine/character.h>
#include <unittypes/jobs.h>

#include "characterinfodialog.h"
#include "ui_characterinfodialog.h"

CharacterInfoDialog::CharacterInfoDialog(const Character& c, QWidget *parent /* = nullptr */) :
    QDialog(parent), _ui(new Ui::CharacterInfoDialog) {

    _ui->setupUi(this);

    _init(c);
}

CharacterInfoDialog::~CharacterInfoDialog() {

    delete _ui;
}

void CharacterInfoDialog::_init(const Character& c) {

    _ui->nameLabel->setText(QString::fromStdString(c.name()));
    _ui->jobLabel->setText(QString::fromStdString(c.className()));
    _ui->levelLabel->setText(QString::number(c.level()));
    _ui->strLabel->setText(QString::number(c.attributes().strength()));
    _ui->vitLabel->setText(QString::number(c.attributes().vitality()));
    _ui->dexLabel->setText(QString::number(c.attributes().dexterity()));
    _ui->agiLabel->setText(QString::number(c.attributes().agility()));
    _ui->wisLabel->setText(QString::number(c.attributes().wisdom()));

    std::optional opt = Jobs::get(c.className(), c.attributes());
    if(!opt.has_value()) return;

    UnitInfo *info = std::get<0>(*opt);

    _ui->healthLabel->setText(QString::number(info->health()));
    _ui->energyLabel->setText(QString::number(info->energy()));
    _ui->attackLabel->setText(QString::number(info->baseAttack()));
    _ui->speedLabel->setText(QString::number(info->speed()));
    _ui->sizeLabel->setText(QString::number(info->size()));
}
