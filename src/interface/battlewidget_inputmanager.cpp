
#include <cmath>

#include <QMouseEvent>

#include <engine/unit.h>

#include "battlewidget_inputmanager.h"

void BattleWidget::InputManager::handleEvents() {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    while(!_events.empty()) {

        auto event = _events.front();
        _events.pop();

        switch (event.first) {

            case Event::AskSkillStart:
                _interface->showSkillButtons(reinterpret_cast<const Unit *>(event.second));
                break;

            case Event::AskSkillFinish:
                _interface->hideSkillButtons();
                break;

            case Event::AskAngleStart:
                {
                    auto u = reinterpret_cast<const Unit *>(event.second);
                    _interface->showArrow(UIntegerType(u->x()), UIntegerType(u->y()));
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

    auto p = _interface->_gview->mapToScene(event->x(), event->y());
    interfaceClickedEvent(QPoint(p.x(), p.y()));
}

void BattleWidget::InputManager::interfaceClickedEvent(const QPoint& click_point) {

    std::unique_lock<std::mutex> lock(_input_mut);

    Q_UNUSED(lock);

    _last_clicked_point.x = click_point.x();
    _last_clicked_point.y = click_point.y();

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

    return std::atan2(cursor.y - u->y(), cursor.x - u->x());
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
