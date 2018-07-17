
#include <QPushButton>

#include "menu.h"
#include "mainwindow.h"
#include "battlewidget.h"
#include "helpwidget.h"
#include "unitsinfo/slime.h"
#include "unitsinfo/fighter.h"
#include "unitsinfo/rslime.h"
#include "controllers/human.h"
#include "controllers/ai/slime.h"
#include "unitanimationfactories/fighteranimationfactory.h"
#include "unitanimationfactories/slimeanimationfactory.h"
#include "unitanimationfactories/redslimeanimationfactory.h"

Menu::Menu(MainWindow *parent /* = nullptr */) : QWidget(parent) {

    _buttons.push_back(new QPushButton("Player vs Player", this));
    QObject::connect(_buttons.back(), &QPushButton::clicked, this, &Menu::_player_vs_player_start_button_clicked);

    _buttons.push_back(new QPushButton("Player vs Ai", this));
    QObject::connect(_buttons.back(), &QPushButton::clicked, this, &Menu::_player_vs_ai_start_button_clicked);

    _buttons.push_back(new QPushButton("Challenge", this));
    QObject::connect(_buttons.back(), &QPushButton::clicked, this, &Menu::_challenge_start_button_clicked);

    _buttons.push_back(new QPushButton("help", this));
    QObject::connect(_buttons.back(), &QPushButton::clicked, this, &Menu::_help_button_clicked);

    _place_buttons();
}

void Menu::setParent(MainWindow *parent){

    QWidget::setParent(parent);
}

void Menu::_player_vs_ai_start_button_clicked(){

    BattleWidget *bw = new BattleWidget;

    bw->addUnit(unitsinfo::Fighter::getInfo(), controller::Human::getController(),
                unitanimationfactory::FighterAnimationFactory::getFactory(), 0);
    bw->addUnit(unitsinfo::Slime::getInfo(), controller::AI::Slime::getController(),
                unitanimationfactory::SlimeAnimationFactory::getFactory(), 1);

    bw->start();

    static_cast<MainWindow *>(parent())->pushWidget(bw);
}

void Menu::_player_vs_player_start_button_clicked() {

    BattleWidget *bw = new BattleWidget;

    bw->addUnit(unitsinfo::RSlime::getInfo(), controller::Human::getController(),
                unitanimationfactory::RedSlimeAnimationFactory::getFactory(), 0);
    bw->addUnit(unitsinfo::Slime::getInfo(), controller::Human::getController(),
                unitanimationfactory::SlimeAnimationFactory::getFactory(), 1);

    bw->start();

    static_cast<MainWindow *>(parent())->pushWidget(bw);
}

void Menu::_help_button_clicked() {

    HelpWidget *hw = new HelpWidget;

    static_cast<MainWindow *>(parent())->pushWidget(hw);
}

void Menu::_challenge_start_button_clicked() {

    BattleWidget *bw = new BattleWidget;

    bw->addUnit(unitsinfo::Slime::getInfo(), controller::Human::getController(),
                unitanimationfactory::SlimeAnimationFactory::getFactory(), 0);
    for(UIntegerType i = 0; i < 5; i++) {
        bw->addUnit(unitsinfo::Slime::getInfo(), controller::AI::Slime::getController(),
                    unitanimationfactory::SlimeAnimationFactory::getFactory(), 1);
    }

    bw->start();

    static_cast<MainWindow *>(parent())->pushWidget(bw);
}

void Menu::_place_buttons() {

    for(UIntegerType i = 0; i < _buttons.size(); i++){

        auto& button = _buttons[i];

        auto distance = Traits<Menu>::buttonsHeight + Traits<Menu>::buttonsDistance;

        button->setFocusPolicy(Qt::NoFocus);
        button->setGeometry(Traits<Menu>::buttonsX, Traits<Menu>::buttonsY + i*distance,
                            Traits<Menu>::buttonsWidth, Traits<Menu>::buttonsHeight);

        button->show();
    }
}
