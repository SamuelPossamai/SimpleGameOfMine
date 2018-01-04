
#include <limits>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

#include "battlewidget.h"
#include "battleengine.h"
#include "unit.h"
#include "skills/testskill.h"
#include "idbutton.h"

#include <iostream> // remove

BattleWidget::BattleWidget(QWidget *parent /* = nullptr */) : QWidget(parent), _t(nullptr) {

    _gview = new QGraphicsView(new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height), this);

    _gview->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    _gview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _engine = new BattleEngine();
    _engine->setScene(_gview->scene());


    QPixmap slime_im1 = QPixmap(":/slime_idle1.png").scaled(50, 50);
    QPixmap slime_im2 = QPixmap(":/slime_idle2.png").scaled(50, 50);
    QPixmap slime_im3 = QPixmap(":/slime_idle3.png").scaled(50, 50);
    QPixmap slime_im4 = QPixmap(":/slime_idle4.png").scaled(50, 50);
    QPixmap slime_im5 = QPixmap(":/slime_idle5.png").scaled(50, 50);

    Animation slime_animation(1000, true);

    slime_animation.setFlag(Animation::Flag::RandomStart);

    slime_animation.addImage(slime_im1, 0);
    slime_animation.addImage(slime_im2, 200);
    slime_animation.addImage(slime_im3, 400);
    slime_animation.addImage(slime_im4, 600);
    slime_animation.addImage(slime_im5, 800);

    QPixmap im1 = QPixmap(":/testimage.png").scaled(100, 100);
    QPixmap im2 = QPixmap(":/testimage_red.png").scaled(100, 100);
    QPixmap im3 = im1.scaled(100, 50);

    Animation animation1(100);
    Animation animation2(1000);

    animation1.addImage(im1, 0);
    animation1.addImage(im2, 50);

    animation2.addImage(im3, 0);

    UnitInfo *u_info = new UnitInfo;
    UnitSkill *test_skill = new Skill::TestSkill;

    u_info->addSkill(test_skill, slime_animation, im1);
    u_info->addSkill(test_skill, slime_animation, im2);
    u_info->addSkill(test_skill, slime_animation, slime_im1);
    u_info->addSkill(test_skill, slime_animation, slime_im2);
    u_info->setIdleAnimation(slime_animation);

    showSkillButtons(u_info);

    for(UIntegerType i = 0; i < 3; i++) _engine->addUnit(u_info, 0);

    _engine->placeUnits();

    _timer = new QTimer(this);

   _timer->setInterval(10);

   QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(step()));

   _timer->start();
}

void BattleWidget::showSkillButtons(UnitInfo *info) {

    static const auto button_size = Traits<BattleWidget>::skillButtonSize;

    while(_skill_buttons.size() < info->skills()) {

        _skill_buttons.push_back(new IdButton(_skill_buttons.size(), this));

        _skill_buttons.back()->setFocusPolicy(Qt::NoFocus);

        _skill_buttons.back()->setIconSize(QSize(button_size, button_size));

        QObject::connect(_skill_buttons.back(), &IdButton::clickedId, this, &BattleWidget::_skill_button_clicked);
    }

    RealType button_x, button_y;

    if(Traits<BattleWidget>::skillButtonDirection == Traits<BattleWidget>::Direction::Horizontal){

        button_y = _button_pos_calculate_static(false, UIntegerType(Traits<BattleWidget>::skillButtonVerticalAlign));
    }else {

        button_x = _button_pos_calculate_static(true, UIntegerType(Traits<BattleWidget>::skillButtonHorizontalAlign));
    }

    for(UIntegerType i = 0; i < info->skills(); i++){

        auto *button = _skill_buttons[i];

        if(Traits<BattleWidget>::skillButtonDirection == Traits<BattleWidget>::Direction::Horizontal){

            button_x = _button_pos_calculate_dynamic(i, info->skills(), true,
                                                     UIntegerType(Traits<BattleWidget>::skillButtonHorizontalAlign));

        }else {

            button_y = _button_pos_calculate_dynamic(i, info->skills(), false,
                                                     UIntegerType(Traits<BattleWidget>::skillButtonVerticalAlign));
        }

        button->setIcon(QIcon(info->skillIcon(i)));

        button->setGeometry(button_x, button_y, button_size, button_size);

        button->show();
    }
}

UIntegerType BattleWidget::askSkill() {

    if(!skillButtonsVisible()) return std::numeric_limits<UIntegerType>::max();

    _last_skill_button_clicked = _skill_buttons.size();

    while(_last_skill_button_clicked >= _skill_buttons.size());

    return _last_skill_button_clicked;
}

bool BattleWidget::skillButtonsVisible() const {

    if(_skill_buttons.empty()) return false;
    _skill_buttons.front()->setVisible(true);

    return _skill_buttons.front()->isVisible();
}

void BattleWidget::step(){

    _engine->step();

    if(_step_mut.try_lock()) {

        if(_t != nullptr) {

            if(_t->joinable()) _t->detach();
            delete _t;
        }

        _t = new std::thread(_step_internal, this);
    }
}

void BattleWidget::keyPressEvent(QKeyEvent *event) {

    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier){

        if(event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) zoomIn();
        else if(event->key() == Qt::Key_Minus) zoomOut();
    }
}

void BattleWidget::_step_internal(BattleWidget *bw) {

    std::cout << bw->askSkill() << std::endl; // test

    bw->_step_mut.unlock();
}

void BattleWidget::_skill_button_clicked(UIntegerType id){

    _last_skill_button_clicked = id;
}

RealType BattleWidget::_button_pos_calculate_static(bool x_dir, UIntegerType mode) {

    auto max = x_dir ? Traits<MainWindow>::width : Traits<MainWindow>::height;
    auto border_distance = x_dir ? Traits<BattleWidget>::skillButtonBorderHorizontalDistance :
                                   Traits<BattleWidget>::skillButtonBorderVerticalDistance;

    switch(mode) {

        case 0:
            return border_distance;
        case 1:
            return max/2 - Traits<BattleWidget>::skillButtonSize/2;
        default:
            return max - border_distance - Traits<BattleWidget>::skillButtonSize;
    }
}

RealType BattleWidget::_button_pos_calculate_dynamic(UIntegerType i, UIntegerType i_max, bool x_dir, UIntegerType mode) {

    static const auto button_size = Traits<BattleWidget>::skillButtonSize;
    static const auto buttons_distance = Traits<BattleWidget>::skillButtonDistance;


    auto max = x_dir ? Traits<MainWindow>::width : Traits<MainWindow>::height;
    auto border_distance = x_dir ? Traits<BattleWidget>::skillButtonBorderHorizontalDistance :
                                   Traits<BattleWidget>::skillButtonBorderVerticalDistance;

    switch(mode) {

        case 0:
            return border_distance + i*(button_size + buttons_distance);
        case 1:
            return max/2 + (RealType(i) - RealType(i_max)/2)*(button_size + buttons_distance) + \
                    (i_max%2 ? -button_size/2 : buttons_distance/2);
        default:
            return max - border_distance - i*(button_size + buttons_distance) - Traits<BattleWidget>::skillButtonSize;
    }
}
