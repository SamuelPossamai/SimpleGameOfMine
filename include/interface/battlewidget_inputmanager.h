
#ifndef BATTLEWIDGET_INPUTMANAGER_H
#define BATTLEWIDGET_INPUTMANAGER_H

#include "battlewidget.h"

/*!
 * \brief UserInterface for the UnitController
 */
class BattleWidget::InputManager : public UnitController::UserInterface {

    friend class BattleWidget;

    enum class Event : UIntegerType { AskSkillStart, AskSkillFinish, AskAngleStart, AskAngleFinish };
    using EventList = std::queue<std::pair<Event, const void *> >;

public:

    /*!
     * \brief Constructs an InputManager
     * \param i BattleWidget from which the iputs will be receiveds
     */
    explicit InputManager(BattleWidget *i) : _enable(false), _interface(i) {}

    /*!
     * \brief Ask for a mouse click
     * \return The position that was clicked
     */
    Vec2Type<IntegerType> askMouseClick();

    /*!
     * \brief Ask to select an skill
     * \return The id of the selected skill
     */
    UIntegerType askSkill();

protected:

    /*!
     * \brief Overwritten virtual method from UnitController, this method is called when a controller ask for an skill
     * \return Id of the selected skill
     */
    virtual UIntegerType controllerUserInterfaceAskSkillInput(const Unit *) override;

    /*!
     * \brief Overwritten virtual method from UnitController, this method is called when a controller ask for an angle
     * \return if not canceled, the selected angle or else std::nullopt
     */
    virtual std::optional<UnitController::AngleType> controllerUserInterfaceAskAngleInput(const Unit *) override;

    void handleEvents();

    void enable() { _enable = true; }
    void disable() { _enable = false; }

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
