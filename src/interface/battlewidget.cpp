
#include <limits>
#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

#include "unit.h"
#include "mainwindow.h"
#include "battlewidget.h"
#include "battleengine.h"
#include "unit.h"
#include "idbutton.h"

BattleWidget::BattleWidget(MainWindow *parent /* = nullptr */) :
    QWidget(parent), _arrow_item(nullptr), _message(nullptr), _input_allowed(true), _waiting_input(0) {

    _gview = new BattleView(this, new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height, this), this);

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

    QPushButton *ret_button = new QPushButton("Return", this);

    ret_button->setGeometry(0, 0.9*Traits<MainWindow>::height,
                            0.1*Traits<MainWindow>::width, 0.1*Traits<MainWindow>::height);

    QObject::connect(ret_button, &QPushButton::clicked, this, &BattleWidget::_return_button_pressed);

    ret_button->setFocusPolicy(Qt::NoFocus);

    ret_button->show();

    qRegisterMetaType<UIntegerType>("UIntegerType");

    QObject::connect(this, &BattleWidget::hideSkillButtonsSignal, this, &BattleWidget::hideSkillButtons);
    QObject::connect(this, &BattleWidget::showSkillButtonsSignal, this, &BattleWidget::showSkillButtons);
    QObject::connect(this, &BattleWidget::showArrowSignal, this, &BattleWidget::showArrow);
    QObject::connect(this, &BattleWidget::hideArrowSignal, this, &BattleWidget::hideArrow);

    _timer = new QTimer(this);

    _timer->setInterval(10);

    QObject::connect(_timer, &QTimer::timeout, this, &BattleWidget::step);
    QObject::connect(this, &BattleWidget::startTimer, _timer, static_cast<void (QTimer::*)()>(&QTimer::start));
    QObject::connect(this, &BattleWidget::stopTimer, _timer, &QTimer::stop);
}

BattleWidget::~BattleWidget() {

    std::unique_lock<std::mutex> l(_input_mut);

    _input_wait.notify_all();

    _input_allowed = false;
}

void BattleWidget::setParent(MainWindow *p) {

    QWidget::setParent(p);
}

void BattleWidget::showSkillButtons(const UnitInfo *info) {

    std::unique_lock<std::mutex> lock(_input_mut);
    Q_UNUSED(lock);

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

    std::unique_lock<std::mutex> lock(_input_mut);
    Q_UNUSED(lock);

    for(UIntegerType i = 0; i < _skill_buttons.size(); i++) _skill_buttons[i]->hide();
}

UIntegerType BattleWidget::askSkill() {

    std::unique_lock<std::mutex> lock(_input_mut);

    _waiting_input++;

    if(!skillButtonsVisible()) return std::numeric_limits<UIntegerType>::max();

    _last_skill_button_clicked = _skill_buttons.size();

    while(_last_skill_button_clicked >= _skill_buttons.size() && _input_allowed) _input_wait.wait(lock);

    _waiting_input--;

    return _input_allowed ? _last_skill_button_clicked : 0;
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
    else {

        if(event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) _skill_button_clicked(event->key() - Qt::Key_1);
    }
}

Vec2Type<IntegerType> BattleWidget::askMouseClick() {

    std::unique_lock<std::mutex> lock(_input_mut);

    _waiting_input++;

    _mouse_clicked = false;

    while(!_mouse_clicked && _input_allowed) _input_wait.wait(lock);

    _waiting_input--;

    return _last_clicked_point;
}

void BattleWidget::battleViewMouseMoveEvent(QMouseEvent *event) {

    QPointF p = _gview->mapToScene(event->pos());

    auto x = p.x() - _arrow_item->x();
    auto y = p.y() - _arrow_item->y();

    RealType angle = 180*atan2(y, x)/M_PI;

    _arrow_item->setRotation(angle);
}

void BattleWidget::battleViewMouseReleaseEvent(QMouseEvent *event) {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    _last_clicked_point.x = event->x();
    _last_clicked_point.y = event->y();

    _mouse_clicked = true;

    _input_wait.notify_all();
}

void BattleWidget::start(){

    _engine->placeUnits();

    _timer->start();
}

void BattleWidget::addUnit(UnitInfo *u, UnitController *c, UIntegerType team) {

    _engine->addUnit(u, c, team);
}

UIntegerType BattleWidget::controllerUserInterfaceAskSkillInput(const Unit *u) {

    emit showSkillButtonsSignal(u->unitInfo());
    if(!Traits<BattleWidget>::allowIdleAnimation) emit stopTimer();

    UIntegerType input;
    while((input = askSkill()) == std::numeric_limits<UIntegerType>::max());

    emit hideSkillButtonsSignal();
    if(!Traits<BattleWidget>::allowIdleAnimation) emit startTimer();

    return input;
}

UnitController::AngleType BattleWidget::controllerUserInterfaceAskAngleInput(const Unit *u) {

    emit showArrowSignal(u->x(), u->y());
    if(!Traits<BattleWidget>::allowIdleAnimation) emit stopTimer();

    auto cursor = askMouseClick();

    emit hideArrow();
    if(!Traits<BattleWidget>::allowIdleAnimation) emit startTimer();

    QPointF p = _gview->mapToScene(cursor.x, cursor.y);

    return atan2(p.y() - _arrow_item->y(), p.x() - _arrow_item->x());
}

void BattleWidget::displayMessage(std::string message) {

    if(_message == nullptr){

        _message = new QLabel(this);
        _message->setGeometry(this->geometry());
        _message->setAlignment(Qt::AlignCenter);
        _message->setFocusPolicy(Qt::NoFocus);
        _message->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        QFont font = _message->font();

        font.setBold(true);
        font.setPointSize(40);

        _message->setFont(font);
    }

    _message->setText(QString::fromStdString(message));
    _message->show();
}

void BattleWidget::_return_button_pressed(){

    static_cast<MainWindow *>(parent())->popWidget();
}

void BattleWidget::_skill_button_clicked(UIntegerType id){

    std::unique_lock<std::mutex> lock(_input_mut);

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

