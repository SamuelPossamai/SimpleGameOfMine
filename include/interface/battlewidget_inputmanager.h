
#ifndef BATTLEWIDGET_INPUTMANAGER_H
#define BATTLEWIDGET_INPUTMANAGER_H

#include "battlewidget.h"

class BattleWidget::InputManager : public UnitController::UserInterface {

    friend class BattleWidget;

    enum class Event : UIntegerType { AskSkillStart, AskSkillFinish, AskAngleStart, AskAngleFinish };
    using EventList = std::queue<std::pair<Event, const void *> >;

public:

    InputManager(BattleWidget *i) : _enable(false), _interface(i) {}

    Vec2Type<IntegerType> askMouseClick();

    UIntegerType askSkill();

protected:

    void handleEvents();

    void enable() { _enable = true; }
    void disable() { _enable = false; }

    virtual UIntegerType controllerUserInterfaceAskSkillInput(const Unit *) override;
    virtual std::optional<UnitController::AngleType> controllerUserInterfaceAskAngleInput(const Unit *) override;

    void interfaceSkillButtonClicked(UIntegerType id);
    void interfaceMouseReleaseEvent(QMouseEvent *event);
    void interfaceCancelButtonClicked();

private:

    bool _enable;

    UIntegerType _last_skill_button_clicked;
    Vec2Type<IntegerType> _last_clicked_point;

    bool _mouse_clicked;
    bool _canceled;

    std::mutex _input_mut;
    std::condition_variable _input_wait;

    BattleWidget *_interface;

    EventList _events;
};

#endif // BATTLEWIDGET_INPUTMANAGER_H
