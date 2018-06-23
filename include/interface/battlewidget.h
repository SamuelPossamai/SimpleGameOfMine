#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <mutex>
#include <condition_variable>

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QLabel>

#include "interface_traits.h"
#include "battleview.h"
#include "unitcontroller.h"

/*!
 * \brief Widget that manages the interface in a battle
 */
class BattleWidget : public QWidget, public BattleView::Handler, public UnitController::UserInterface {

    Q_OBJECT

public:

    BattleWidget(MainWindow *parent = nullptr);

    void setParent(MainWindow *p);
    void setParent(QWidget *) = delete;

    ~BattleWidget();

    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    void translate(IntegerType dx, IntegerType dy) { _gview->translate(dx, dy); }

    void showArrow(UIntegerType x, UIntegerType y) { _arrow_item->setPos(x, y); _arrow_item->show(); }
    void hideArrow() { _arrow_item->hide(); }

    Vec2Type<IntegerType> askMouseClick();

    UIntegerType askSkill();

    bool skillButtonsVisible() const;

    void start();

    void addUnit(UnitInfo *, UnitController *, UIntegerType team);

    void displayMessage(std::string);

signals:

    void showSkillButtonsSignal(const UnitInfo *info);
    void hideSkillButtonsSignal();

    void showArrowSignal(UIntegerType x, UIntegerType y);
    void hideArrowSignal();

    void startTimer();
    void stopTimer();

public slots:

    void step();

    void showSkillButtons(const UnitInfo *info);
    void hideSkillButtons();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void battleViewMouseMoveEvent(QMouseEvent *event) override;

    virtual void battleViewMouseReleaseEvent(QMouseEvent *event) override;

    virtual UIntegerType controllerUserInterfaceAskSkillInput(const Unit *) override;

    virtual UnitController::AngleType controllerUserInterfaceAskAngleInput(const Unit *) override;

private slots:

    void _return_button_pressed();

    void _skill_button_clicked(UIntegerType id);

private:

    static void _step_internal(BattleWidget *);
    void _set_zoom(RealType zoom) { _gview->scale(zoom, zoom); }
    RealType _button_pos_calculate_static(bool x_dir, UIntegerType mode);
    RealType _button_pos_calculate_dynamic(UIntegerType i, UIntegerType i_max, bool x_dir, UIntegerType mode);

    QGraphicsView *_gview;
    QTimer *_timer;

    BattleEngine *_engine;

    std::vector<IdButton *> _skill_buttons;

    UIntegerType _last_skill_button_clicked;
    Vec2Type<IntegerType> _last_clicked_point;

    bool _mouse_clicked;

    QGraphicsPixmapItem *_arrow_item;
    QLabel *_message;

    bool _input_allowed;
    UIntegerType _waiting_input;

    std::mutex _input_mut;
    std::condition_variable _input_wait;
};

#endif // BATTLEWIDGET_H
