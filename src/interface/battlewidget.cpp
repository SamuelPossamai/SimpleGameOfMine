
#include <limits>
#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

#include "battlewidget.h"
#include "battleengine.h"
#include "unit.h"
#include "idbutton.h"
#include "skills/testskill.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"
#include "controllers/human.h"
#include "controllers/ai/slime.h"

BattleWidget::BattleWidget(QWidget *parent /* = nullptr */) : QWidget(parent), _arrow_item(nullptr) {

    _gview = new BattleView(this, new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height), this);

    _gview->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    _gview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _gview->setMouseTracking(true);

    _engine = new BattleEngine(this);
    _engine->setScene(_gview->scene());

    _arrow_item = new QGraphicsPixmapItem(QPixmap(":/arrow_image.png").scaled(100, 50));

    hideArrow();

    _arrow_item->setOffset(0, -_arrow_item->pixmap().height()/2);

    _gview->scene()->addItem(_arrow_item);

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

    Animation slime_attack_animation(10, true);

    slime_attack_animation.addImage(QPixmap(":/slime_attack.png").scaled(150, 50), 0);

    UnitInfo *u_info = new UnitInfo;

    u_info->addSkill(new skill::Walk(10, 100), slime_animation, QPixmap(":/wing_boot.png").scaled(50, 50));
    u_info->addSkill(new skill::Evade, slime_animation, QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    u_info->addSkill(new skill::Thrust(12, 90), slime_attack_animation, QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    u_info->setIdleAnimation(slime_animation);

    u_info->setSize(22);
    u_info->setHealth(10);

    UnitController *human = new controller::Human;
    UnitController *ai = new controller::AI::Slime;

    UIntegerType i = 0;

    for(; i < 1; i++) _engine->addUnit(u_info, human, i);
    for(; i < 2; i++) _engine->addUnit(u_info, ai, i);
}

void BattleWidget::showSkillButtons(const UnitInfo *info) {

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

    for(UIntegerType i = info->skills(); i < _skill_buttons.size(); i++) _skill_buttons[i]->hide();
}

void BattleWidget::hideSkillButtons() {

    for(UIntegerType i = 0; i < _skill_buttons.size(); i++) _skill_buttons[i]->hide();
}

UIntegerType BattleWidget::askSkill() {

    if(!skillButtonsVisible()) return std::numeric_limits<UIntegerType>::max();

    std::unique_lock<std::mutex> lock(_input_mut);

    _last_skill_button_clicked = _skill_buttons.size();

    while(_last_skill_button_clicked >= _skill_buttons.size()) _input_wait.wait(lock);

    return _last_skill_button_clicked;
}

bool BattleWidget::skillButtonsVisible() const {

    if(_skill_buttons.empty()) return false;
    _skill_buttons.front()->setVisible(true);

    return _skill_buttons.front()->isVisible();
}

void BattleWidget::step(){

    _engine->step();
}

void BattleWidget::keyPressEvent(QKeyEvent *event) {

    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier){

        if(event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) zoomIn();
        else if(event->key() == Qt::Key_Minus) zoomOut();
    }
}

Vec2Type<IntegerType> BattleWidget::askMouseClick() {

    std::unique_lock<std::mutex> lock(_input_mut);

    _mouse_clicked = false;

    while(!_mouse_clicked) _input_wait.wait(lock);

    return _last_clicked_point;
}

void BattleWidget::battleViewMouseMoveEvent(QMouseEvent *event) {

    auto x = event->x() - _arrow_item->x();
    auto y = event->y() - _arrow_item->y();

    RealType angle = 180*atan2(y, x)/M_PI;

    _arrow_item->setRotation(angle);
}

void BattleWidget::battleViewMouseReleaseEvent(QMouseEvent *event) {

    std::unique_lock lock(_input_mut);

    Q_UNUSED(lock);

    _last_clicked_point.x = event->x();
    _last_clicked_point.y = event->y();

    _mouse_clicked = true;

    _input_wait.notify_all();
}

void BattleWidget::start(){

    _engine->placeUnits();

    _timer = new QTimer(this);

    _timer->setInterval(10);

    QObject::connect(_timer, &QTimer::timeout, this, &BattleWidget::step);

    _timer->start();
}

UIntegerType BattleWidget::controllerUserInterfaceAskSkillInput() {

    return askSkill();
}

UnitController::AngleType BattleWidget::controllerUserInterfaceAskAngleInput() {

    auto cursor = askMouseClick();

    return atan2(cursor.y - _arrow_item->y(), cursor.x - _arrow_item->x());
}

void BattleWidget::_skill_button_clicked(UIntegerType id){

    std::unique_lock lock(_input_mut);

    Q_UNUSED(lock);

    _last_skill_button_clicked = id;

    _input_wait.notify_all();
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
            return max/2 + (RealType(i) - i_max/2)*(button_size + buttons_distance) + \
                    (i_max%2 ? -button_size/2 : RealType(buttons_distance)/2);
        default:
            return max - border_distance - i*(button_size + buttons_distance) - Traits<BattleWidget>::skillButtonSize;
    }
}

