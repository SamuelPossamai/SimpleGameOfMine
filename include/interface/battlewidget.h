#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <mutex>
#include <condition_variable>
#include <memory>
#include <queue>

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QPushButton>

#include <config/interface_traits.h>
#include <engine/unitcontroller.h>
#include <engine/character.h>

#include "graphicsview.h"
#include "mainwidget.h"

/*!
 * \brief Widget that manages the interface in a battle
 */
class BattleWidget : public MainWidget, public GraphicsView::Handler {

    Q_OBJECT

public:

    class InputManager;
    using InputInterface = std::shared_ptr<InputManager>;

    /*!
     * \brief Creates a BattleWidget passing it's parent
     * \param parent BattleWidget parent, it must be an MainWindow or a derived class
     * \param result Location to write the result of the battle after finishing
     */
    explicit BattleWidget(MainWindow *parent = nullptr, UIntegerType *result = nullptr);

    /*!
     * \brief Start the timer that will advance the battle
     */
    void start();

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
    bool addCreature(std::string name, UIntegerType level, UIntegerType team);
    bool addHero(std::string name, const Character::Attributes& attr, UIntegerType team);

    void displayMessage(std::string);

    InputInterface inputInterface() const { return _input_interface; }

    void showCancelButton() { _cancel_button->show(); }
    void hideCancelButton() { _cancel_button->hide(); }

public slots:

    void step();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void graphicsViewMouseMoveEvent(QMouseEvent *event) override;

    virtual void graphicsViewMouseReleaseEvent(QMouseEvent *event) override;

private slots:

    void _return_button_pressed();

    void _skill_button_clicked(UIntegerType id);

    void _cancel_button_clicked();

private:

    void _exit();

    static void _step_internal(BattleWidget *);
    void _set_zoom(RealType zoom) { _gview->scale(zoom, zoom); }
    RealType _button_pos_calculate_static(bool x_dir, UIntegerType mode);
    RealType _button_pos_calculate_dynamic(UIntegerType i, UIntegerType i_max, bool x_dir, UIntegerType mode);

    void _gview_construct();
    void _engine_construct();
    void _arrow_construct();
    void _retbutton_construct();
    void _timer_construct();
    void _cancel_button_construct();

    UIntegerType *_result;

    QGraphicsView *_gview;
    QTimer *_timer;

    BattleEngine *_engine;

    std::vector<IdButton *> _skill_buttons;
    QPushButton *_cancel_button;

    QGraphicsPixmapItem *_arrow_item;
    QLabel *_message;
    QLabel *_cursor_label;

    InputInterface _input_interface;

    std::vector<UnitAnimationItem *> _animations;
};

#include "battlewidget_inputmanager.h"

#endif // BATTLEWIDGET_H
