#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QLabel>

#include "interface_traits.h"
#include "graphicsview.h"
#include "unitcontroller.h"

/*!
 * \brief Widget that manages the interface in a battle
 */
class BattleWidget : public QWidget, public GraphicsView::Handler {

    Q_OBJECT

public:

    class InputManager;
    using InputInterface = std::shared_ptr<InputManager>;

    /*!
     * \brief Creates a BattleWidget passing it's parent
     * \param parent BattleWidget parent, it must be an MainWindow or a derived class
     */
    BattleWidget(MainWindow *parent = nullptr);

    /*!
     * \brief Start the timer that will advance the battle
     */
    void start();

    void setParent(MainWindow *p);
    void setParent(QWidget *) = delete;

    ~BattleWidget();

    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    void translate(IntegerType dx, IntegerType dy) { _gview->translate(dx, dy); }

    void showArrow(UIntegerType x, UIntegerType y) { _arrow_item->setPos(x, y); _arrow_item->show(); }
    void hideArrow() { _arrow_item->hide(); }

    bool skillButtonsVisible() const;

    void showSkillButtons(const UnitInfo *);
    void hideSkillButtons();

    void addUnit(UnitInfo *, UnitController *, UnitAnimationItemFactory *, UIntegerType team);

    void displayMessage(std::string);

    InputInterface inputInterface() const { return _input_interface; }

public slots:

    void step();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void graphicsViewMouseMoveEvent(QMouseEvent *event) override;

    virtual void graphicsViewMouseReleaseEvent(QMouseEvent *event) override;

private slots:

    void _return_button_pressed();

    void _skill_button_clicked(UIntegerType id);

private:

    static void _step_internal(BattleWidget *);
    void _set_zoom(RealType zoom) { _gview->scale(zoom, zoom); }
    RealType _button_pos_calculate_static(bool x_dir, UIntegerType mode);
    RealType _button_pos_calculate_dynamic(UIntegerType i, UIntegerType i_max, bool x_dir, UIntegerType mode);

    void _gview_construct();
    void _engine_construct();
    void _arrow_construct();
    void _retbutton_construct();
    void _timer_construct();

    QGraphicsView *_gview;
    QTimer *_timer;

    BattleEngine *_engine;

    std::vector<IdButton *> _skill_buttons;

    QGraphicsPixmapItem *_arrow_item;
    QLabel *_message;

    InputInterface _input_interface;

    std::vector<UnitAnimationItem *> _animations;
};

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
    virtual UnitController::AngleType controllerUserInterfaceAskAngleInput(const Unit *) override;

    void interfaceSkillButtonClicked(UIntegerType id);
    void interfaceMouseReleaseEvent(QMouseEvent *event);

private:

    bool _enable;

    UIntegerType _last_skill_button_clicked;
    Vec2Type<IntegerType> _last_clicked_point;

    bool _mouse_clicked;

    std::mutex _input_mut;
    std::condition_variable _input_wait;

    BattleWidget *_interface;

    EventList _events;
};

#endif // BATTLEWIDGET_H
