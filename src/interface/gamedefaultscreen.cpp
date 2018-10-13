
#include <cmath>

#include <gameinfo/maps/greenvalley.h>
#include <gameinfo/maps/trainingground.h>

#include "battlewidget.h"
#include "characterinfodialog.h"
#include "selectjobdialog.h"
#include "gamedefaultscreen.h"
#include "ui_gamedefaultscreen.h"

GameDefaultScreen::GameDefaultScreen(std::vector<std::string> players, MainWindow *parent /* = nullptr */) :
    MainWidget(parent), _xp_for_victory(0), _selected(0), _ui(new Ui::GameDefaultScreen) {

    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    _ui->setupUi(this);

    for(const std::string& name : players) _chars.emplace_back(name);
}

GameDefaultScreen::~GameDefaultScreen() {

    delete _ui;
}

void GameDefaultScreen::activate() {

    if(_xp_for_victory && _result == 0) {

        _xp_for_victory = _xp_for_victory/_chars.size();

        for(Character& c : _chars) {

            c.receiveExperience(_xp_for_victory);
            c.save();
        }

        _xp_for_victory = 0;
    }

    _ui->charactersList->clear();

    for(const Character& c : _chars) {

        QString text;
        text.sprintf("Lv: %03lu %s %s", c.level(), c.className().c_str(), c.name().c_str());
        _ui->charactersList->addItem(text);
    }

    _reselect();
}

void GameDefaultScreen::on_menuButton_clicked() {

    parent()->popWidget();
}

void GameDefaultScreen::on_charactersList_itemClicked(QListWidgetItem *item) {

    _select_char_info(_ui->charactersList->row(item));
}

void GameDefaultScreen::on_exploreButton1_clicked() {

    _start_battle(gameinfo::map::TrainingGround::getMap());
}

void GameDefaultScreen::on_exploreButton2_clicked() {

    _start_battle(gameinfo::map::GreenValley::getMap());
}

void GameDefaultScreen::on_strAddButton_clicked() {

    _assign_point(0);
}

void GameDefaultScreen::on_vitAddButton_clicked() {

    _assign_point(1);
}

void GameDefaultScreen::on_dexAddButton_clicked() {

    _assign_point(2);
}

void GameDefaultScreen::on_agiAddButton_clicked() {

    _assign_point(3);
}

void GameDefaultScreen::on_wisAddButton_clicked() {

    _assign_point(4);
}

void GameDefaultScreen::on_infoButton_clicked() {

    CharacterInfoDialog(_chars[_selected], this).exec();
}

void GameDefaultScreen::on_changeJobButton_clicked() {

    SelectJobDialog(_chars[_selected], this).exec();
    activate();
}

void GameDefaultScreen::_start_battle(gameinfo::CreatureMap *m) {

    BattleWidget *bw = new BattleWidget(parent(), &_result);

    _result = 1;

    for(const Character& c : _chars) bw->addHero(c.className(), c.attributes(), 0);

    _xp_for_victory = 0;
    for(const gameinfo::CreatureMap::CreaturesContainerContent& creature_info : m->getCreatures()) {

        _xp_for_victory += std::ceil(std::pow(creature_info.creature_level + 3, 1.5));
        bw->addCreature(creature_info.creature_name, creature_info.creature_level, 1);
    }

    bw->start();

    parent()->pushWidget(bw);
}

void GameDefaultScreen::_select_char_info(UIntegerType id) {

    const Character& c = _chars[id];
    _selected = id;

    _ui->charNameLabel->setText(QString::fromStdString(c.name()));

    _ui->jobLabel->setText(QString::fromStdString(c.className()));
    _ui->levelLabel->setText(QString::number(c.level()));
    _ui->freePointsLabel->setText(QString::number(c.freePoints()));
    _ui->strLabel->setText(QString::number(c.attributes().strength()));
    _ui->vitLabel->setText(QString::number(c.attributes().vitality()));
    _ui->dexLabel->setText(QString::number(c.attributes().dexterity()));
    _ui->agiLabel->setText(QString::number(c.attributes().agility()));
    _ui->wisLabel->setText(QString::number(c.attributes().wisdom()));

    _ui->expLabel->setText(QString("%1 / %2").arg(c.experience()).arg(c.experienceNeeded()));
}

void GameDefaultScreen::_assign_point(UIntegerType id) {

    Character& c = _chars[_selected];
    c.assignPoint(id);
    c.save();
    _reselect();
}

