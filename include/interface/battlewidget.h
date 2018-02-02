#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>

#include "types.h"
#include "animatedobject.h"

class BattleWidget : public QWidget {

    Q_OBJECT

public:

    BattleWidget(QWidget *parent = nullptr);

    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    void translate(IntegerType dx, IntegerType dy) { _gview->translate(dx, dy); }

    void showSkillButtons(UnitInfo *info);

    UIntegerType askSkill();

    bool skillButtonsVisible() const;

public slots:

    void step();

protected:

    virtual void keyPressEvent(QKeyEvent *event) override;

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
};

#endif // BATTLEWIDGET_H
