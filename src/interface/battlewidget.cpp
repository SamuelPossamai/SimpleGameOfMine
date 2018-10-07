
#include <cmath>

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QMessageBox>

#include <animation/projectileanimationitemfactory.h>
#include <animation/projectileanimationitem.h>
#include <config/engine_traits.h>
#include <memory/memorymanager.h>
#include <unittypes/creatures.h>
#include <unittypes/jobs.h>
#include <engine/controllers/human.h>

#include "ui_battlewidget.h"
#include "mainwindow.h"
#include "battlewidget.h"
#include "battleengine.h"
#include "idbutton.h"
#include "unitanimationitem.h"
#include "unitanimationitemfactory.h"

BattleWidget::BattleWidget(MainWindow *parent /* = nullptr */, UIntegerType *result /* = nullptr */) :
    MainWidget(parent), _result(result), _current_buttons(0), _arrow_item(nullptr), _message(nullptr),
    _input_interface(std::make_shared<InputManager>(this)), _ui(new Ui::BattleWidget) {

    MemoryManager::cleanAll(25);

    _gview_construct();
    _engine_construct();
    _arrow_construct();
    _timer_construct();
    _ui->setupUi(this);

    _ui->cursorLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    hideCancelButton();

    setStyleSheet("background-color:lightGray;");

    _input_interface->enable();

}

BattleWidget::~BattleWidget() {

    _input_interface->disable();

    for(auto *animation : _animations) {

        delete animation;
    }
}

void BattleWidget::showSkillButtons(const UnitInfo *info) {

    static const auto button_size = Traits<BattleWidget>::skillButtonSize;

    while(_skill_buttons.size() < info->skills()) {

        _skill_buttons.push_back(new IdButton(_skill_buttons.size(), this));

        _skill_buttons.back()->setFocusPolicy(Qt::NoFocus);

        _skill_buttons.back()->setIconSize(QSize(button_size, button_size));

        QObject::connect(_skill_buttons.back(), &IdButton::clickedId, this, &BattleWidget::_skill_button_clicked);
    }

    _current_buttons = info->skills();

    _update_buttons();

    for(UIntegerType i = 0; i < _current_buttons; i++) _skill_buttons[i]->setIcon(QIcon(info->skillIcon(i)));
    for(UIntegerType i = _current_buttons; i < _skill_buttons.size(); i++) _skill_buttons[i]->hide();
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

    if(!_message && _engine->finished()) return _exit();

    _input_interface->handleEvents();
    for(auto *animation : _animations) animation->redraw();

    _engine->step();
}

void BattleWidget::resizeEvent(QResizeEvent *event) {

    _update_buttons();
    _gview->resize(this->size());
    MainWidget::resizeEvent(event);
}

void BattleWidget::keyPressEvent(QKeyEvent *event) {

    if(_engine->finished()) _exit();
    else if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier){

        if(event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) zoomIn();
        else if(event->key() == Qt::Key_Minus) zoomOut();
    }
    else {

        if(event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) _skill_button_clicked(event->key() - Qt::Key_1);
        else event->key();
    }
}

void BattleWidget::graphicsViewMouseMoveEvent(QMouseEvent *event) {

    QPointF p = _gview->mapToScene(event->pos());

    _ui->cursorLabel->setText(QString("%1, %2").arg(p.x()).arg(p.y()));

    if(!_arrow_item->isVisible()) return;

    auto x = p.x() - _arrow_item->x();
    auto y = p.y() - _arrow_item->y();

    RealType angle = 180*atan2(y, x)/M_PI;

    _arrow_item->setRotation(angle);
    _ui->cursorLabel->setText(_ui->cursorLabel->text() + QString(" (%1°)").arg(IntegerType(angle)));
}

void BattleWidget::graphicsViewMouseReleaseEvent(QMouseEvent *event) {

    if(_message) {

        delete _message;
        _message = nullptr;
    }

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

bool BattleWidget::addCreature(std::string name, UIntegerType level, UIntegerType team) {

    auto opt = Creatures::get(name, level);
    if(!opt.has_value()) return false;

    Creatures::Info i = *opt;
    addUnit(std::get<0>(i), std::get<2>(i), std::get<1>(i), team);

    return true;
}

bool BattleWidget::addHero(std::string name, const Character::Attributes& attr, UIntegerType team) {

    auto opt = Jobs::get(name, attr);
    if(!opt.has_value()) return false;

    Jobs::Info i = *opt;
    addUnit(std::get<0>(i), controller::Human::getController(), std::get<1>(i), team);

    return true;
}

void BattleWidget::addProjectile(ProjectileFactory *projFactory, ProjectileAnimationItemFactory *itemFactory,
                                 Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle) {

    _animations.push_back(itemFactory->create(_engine->addProjectile(projFactory, dir, pos, angle)));

    _animations.back()->setScene(_gview->scene());
}

void BattleWidget::showArrow(UIntegerType x, UIntegerType y) {

    _arrow_item->setPos(x, y); _arrow_item->show();
}

void BattleWidget::hideArrow() {

    _arrow_item->hide();
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

void BattleWidget::showCancelButton() {

    _ui->cancelButton->show();
}

void BattleWidget::hideCancelButton() {

    _ui->cancelButton->hide();
}

void BattleWidget::on_cancelButton_clicked() {

    _input_interface->interfaceCancelButtonClicked();
}

void BattleWidget::on_returnButton_clicked() {

    if(QMessageBox::question(this, "SGOM Dialog", "Are you sure that you want to exit from battle?")
            == QMessageBox::Yes) _exit();
}

void BattleWidget::_update_buttons() {

    static const auto button_size = Traits<BattleWidget>::skillButtonSize;

    RealType button_x, button_y;

    if(Traits<BattleWidget>::skillButtonDirection == Traits<BattleWidget>::Direction::Horizontal){

        button_y = _button_pos_calculate_static(false, UIntegerType(Traits<BattleWidget>::skillButtonVerticalAlign));
    }else {

        button_x = _button_pos_calculate_static(true, UIntegerType(Traits<BattleWidget>::skillButtonHorizontalAlign));
    }

    for(UIntegerType i = 0; i < _current_buttons; i++){

        auto *button = _skill_buttons[i];

        if(Traits<BattleWidget>::skillButtonDirection == Traits<BattleWidget>::Direction::Horizontal){

            button_x = _button_pos_calculate_dynamic(i, _current_buttons, true,
                                                     UIntegerType(Traits<BattleWidget>::skillButtonHorizontalAlign));

        }else {

            button_y = _button_pos_calculate_dynamic(i, _current_buttons, false,
                                                     UIntegerType(Traits<BattleWidget>::skillButtonVerticalAlign));
        }

        button->setGeometry(button_x, button_y, button_size, button_size);

        button->show();
    }
}

void BattleWidget::_exit() {

    if(_engine->finished()) *_result = _engine->winningTeam();

    parent()->popWidget();
}

void BattleWidget::_skill_button_clicked(UIntegerType id){

    if(id < _current_buttons) _input_interface->interfaceSkillButtonClicked(id);
}

RealType BattleWidget::_button_pos_calculate_static(bool x_dir, UIntegerType mode) {

    auto max = x_dir ? this->width() : this->height();
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


    auto max = x_dir ? this->width() : this->height();
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

    _gview->setGeometry(this->geometry());

    QPixmap p(Traits<Map>::width, Traits<Map>::height);

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

void BattleWidget::_timer_construct() {

    _timer = new QTimer(this);

    _timer->setInterval(10);

    QObject::connect(_timer, &QTimer::timeout, this, &BattleWidget::step);
}

