
#include <unittypes/creatures.h>

#include "battlewidget.h"
#include "gamedefaultscreen.h"
#include "ui_gamedefaultscreen.h"

#include "unitsinfo/fighter.h"
#include "unitanimationfactories/fighteranimationfactory.h"
#include "controllers/human.h"

GameDefaultScreen::GameDefaultScreen(std::vector<std::string> players, MainWindow *parent /* = nullptr */) :
    MainWidget(parent), _xp_for_victory(0), _ui(new Ui::GameDefaultScreen) {

    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);

    _ui->setupUi(this);

    for(const std::string& name : players) _chars.emplace_back(name);

    for(const Character& c : _chars) {

        QString text;
        text.sprintf("Lv: %03lu %s %s", c.level(), c.className().c_str(), c.name().c_str());
        _ui->charactersList->addItem(text);
    }

    _select_char_info(0);
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

    _reselect();
}

void GameDefaultScreen::on_menuButton_clicked() {

    parent()->popWidget();
}

void GameDefaultScreen::on_charactersList_itemClicked(QListWidgetItem *item) {

    _select_char_info(_ui->charactersList->row(item));
}

void GameDefaultScreen::on_exploreButton1_clicked() {

    BattleWidget *bw = new BattleWidget(parent(), &_result);

    _xp_for_victory = 30;
    _result = 1;

    for(const Character& c : _chars) {
        bw->addUnit(unitsinfo::Fighter::getInfo(c.attributes()), controller::Human::getController(),
                    unitanimationfactory::FighterAnimationFactory::getFactory(), 0);
    }
    bw->addCreature("slime", 0, 1);

    bw->start();

    parent()->pushWidget(bw);
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

    _ui->expLabel->setText(QString("%1 / %2").arg(c.experience()).arg(c.experienceNeeded()));
}

void GameDefaultScreen::_assign_point(UIntegerType id) {

    Character& c = _chars[_selected];
    c.assignPoint(id);
    c.save();
    _reselect();
}
