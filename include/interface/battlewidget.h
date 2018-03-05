#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <mutex>
#include <condition_variable>

#include <QWidget>
#include <QGraphicsPixmapItem>

#include "interface_traits.h"
#include "battleview.h"
#include "unitcontroller.h"

class BattleWidget : public QWidget, public BattleView::Handler, public UnitController::UserInterface {

    Q_OBJECT

public:

    BattleWidget(QWidget *parent = nullptr);

    ~BattleWidget() { _mouse_clicked = true; _skill_button_clicked(0); }

    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    void translate(IntegerType dx, IntegerType dy) { _gview->translate(dx, dy); }

    void showSkillButtons(const UnitInfo *info);
    void hideSkillButtons();

    void showArrow(UIntegerType x, UIntegerType y) { _arrow_item->setPos(x, y); _arrow_item->show(); }
    void hideArrow() { _arrow_item->hide(); }

    Vec2Type<IntegerType> askMouseClick();

    UIntegerType askSkill();

    bool skillButtonsVisible() const;

    void start();

public slots:

    void step();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void battleViewMouseMoveEvent(QMouseEvent *event) override;

    virtual void battleViewMouseReleaseEvent(QMouseEvent *event) override;

    virtual UIntegerType controllerUserInterfaceAskSkillInput();

    virtual UnitController::AngleType controllerUserInterfaceAskAngleInput();

private slots:

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

    std::mutex _input_mut;
    std::condition_variable _input_wait;
};

#endif // BATTLEWIDGET_H
