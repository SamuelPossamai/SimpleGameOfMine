
#include <limits>
#include <cmath>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QScrollBar>
#include <QKeyEvent>

#include <memory/memorymanager.h>

#include "mainwindow.h"
#include "battlewidget.h"
#include "battleengine.h"
#include "idbutton.h"
#include "unitanimationitem.h"
#include "unitanimationitemfactory.h"

BattleWidget::BattleWidget(MainWindow *parent /* = nullptr */) :
    QWidget(parent), _arrow_item(nullptr), _message(nullptr), _input_interface(std::make_shared<InputManager>(this)) {

    MemoryManager::cleanAll(25);

    _gview_construct();
    _engine_construct();
    _arrow_construct();
    _retbutton_construct();
    _timer_construct();
    _cancel_button_construct();

    setStyleSheet("background-color:lightGray;");

    _input_interface->enable();
}

BattleWidget::~BattleWidget() {

    _input_interface->disable();

    for(auto *animation : _animations) {

        delete animation;
    }
}

void BattleWidget::setParent(MainWindow *p) {

    QWidget::setParent(p);
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

bool BattleWidget::skillButtonsVisible() const {

    if(_skill_buttons.empty()) return false;
    _skill_buttons.front()->setVisible(true);

    return _skill_buttons.front()->isVisible();
}

void BattleWidget::step(){

    _input_interface->handleEvents();
    for(auto *animation : _animations) animation->redraw();

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

void BattleWidget::graphicsViewMouseMoveEvent(QMouseEvent *event) {

    QPointF p = _gview->mapToScene(event->pos());

    auto x = p.x() - _arrow_item->x();
    auto y = p.y() - _arrow_item->y();

    RealType angle = 180*atan2(y, x)/M_PI;

    _arrow_item->setRotation(angle);
}

void BattleWidget::graphicsViewMouseReleaseEvent(QMouseEvent *event) {

    _input_interface->interfaceMouseReleaseEvent(event);
}

void BattleWidget::start(){

    _engine->placeUnits();

    _timer->start();
}

void BattleWidget::addUnit(UnitInfo *u, UnitController *c, UnitAnimationItemFactory *f, UIntegerType team) {

    _animations.push_back(f->create(_engine->addUnit(u, c, team)));

    _animations.back()->setScene(_gview->scene());
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

    _input_interface->interfaceSkillButtonClicked(id);
}

void BattleWidget::_cancel_button_clicked() {

    _input_interface->interfaceCancelButtonClicked();
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

void BattleWidget::_gview_construct() {

    _gview = new GraphicsView(this, new QGraphicsScene(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height, this), this);

    _gview->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    QPixmap p(Traits<MainWindow>::width, Traits<MainWindow>::height);

    p.fill(Qt::white);

    _gview->scene()->addPixmap(p);

    _gview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _gview->setMouseTracking(true);
}

void BattleWidget::_engine_construct() {

    _engine = new BattleEngine(this);
}

void BattleWidget::_arrow_construct() {

    _arrow_item = new QGraphicsPixmapItem(QPixmap(":/arrow_image.png").scaled(100, 50));

    hideArrow();

    _arrow_item->setOffset(0, -_arrow_item->pixmap().height()/2);

    _gview->scene()->addItem(_arrow_item);
}

void BattleWidget::_retbutton_construct() {

    QPushButton *ret_button = new QPushButton("Return", this);

    ret_button->setGeometry(0, 0.9*Traits<MainWindow>::height,
                            0.1*Traits<MainWindow>::width, 0.1*Traits<MainWindow>::height);

    QObject::connect(ret_button, &QPushButton::clicked, this, &BattleWidget::_return_button_pressed);

    ret_button->setFocusPolicy(Qt::NoFocus);

    ret_button->show();
}

void BattleWidget::_timer_construct() {

    _timer = new QTimer(this);

    _timer->setInterval(10);

    QObject::connect(_timer, &QTimer::timeout, this, &BattleWidget::step);
}

void BattleWidget::_cancel_button_construct() {

    _cancel_button = new QPushButton("Cancel", this);
    _cancel_button->hide();
    _cancel_button->setGeometry(0.9*Traits<MainWindow>::width, 0.9*Traits<MainWindow>::height,
                                0.1*Traits<MainWindow>::width, 0.1*Traits<MainWindow>::height);

    QObject::connect(_cancel_button, &QPushButton::clicked, this, &BattleWidget::_cancel_button_clicked);
}

void BattleWidget::InputManager::handleEvents() {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    while(!_events.empty()) {

        auto event = _events.front();
        _events.pop();

        switch (event.first) {

            case Event::AskSkillStart:
                _interface->showSkillButtons(reinterpret_cast<const Unit *>(event.second)->unitInfo());
                break;

            case Event::AskSkillFinish:
                _interface->hideSkillButtons();
                break;

            case Event::AskAngleStart:
                {
                    auto u = reinterpret_cast<const Unit *>(event.second);
                    _interface->showArrow(u->x(), u->y());
                    _interface->showCancelButton();
                }
                break;

            case Event::AskAngleFinish:
                _interface->hideArrow();
                _interface->hideCancelButton();
                break;
        }
    }
}


UIntegerType BattleWidget::InputManager::askSkill() {

    std::unique_lock<std::mutex> lock(_input_mut);

    if(!_interface->skillButtonsVisible()) return std::numeric_limits<UIntegerType>::max();

    _last_skill_button_clicked = _interface->_skill_buttons.size();

    while(_last_skill_button_clicked >= _interface->_skill_buttons.size() && _enable) _input_wait.wait(lock);

    return _enable ? _last_skill_button_clicked : 0;
}

Vec2Type<IntegerType> BattleWidget::InputManager::askMouseClick() {

    std::unique_lock<std::mutex> lock(_input_mut);

    _mouse_clicked = false;

    while(!_mouse_clicked && _enable && !_canceled) _input_wait.wait(lock);

    return _last_clicked_point;
}

void BattleWidget::InputManager::interfaceMouseReleaseEvent(QMouseEvent *event) {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    _last_clicked_point.x = event->x();
    _last_clicked_point.y = event->y();

    _mouse_clicked = true;

    _input_wait.notify_all();
}


UIntegerType BattleWidget::InputManager::controllerUserInterfaceAskSkillInput(const Unit *u) {

    _events.push(std::make_pair(Event::AskSkillStart, reinterpret_cast<const void *>(u)));

    UIntegerType input;
    while((input = askSkill()) == std::numeric_limits<UIntegerType>::max());

    _events.push(std::make_pair(Event::AskSkillFinish, nullptr));

    return input;
}

std::optional<UnitController::AngleType> BattleWidget::InputManager::controllerUserInterfaceAskAngleInput(const Unit *u) {

    _events.push(std::make_pair(Event::AskAngleStart, reinterpret_cast<const void *>(u)));

    _canceled = false;
    auto cursor = askMouseClick();

    _events.push(std::make_pair(Event::AskAngleFinish, nullptr));

    if(_canceled) return std::nullopt;

    QPointF p = _interface->_gview->mapToScene(cursor.x, cursor.y);

    return atan2(p.y() - u->y(), p.x() - u->x());
}


void BattleWidget::InputManager::interfaceSkillButtonClicked(UIntegerType id) {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    _last_skill_button_clicked = id;

    _input_wait.notify_all();
}

void BattleWidget::InputManager::interfaceCancelButtonClicked() {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    _canceled = true;

    _input_wait.notify_all();
}
