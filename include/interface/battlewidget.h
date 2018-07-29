
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

namespace Ui {
class BattleWidget;
} /* namespace Ui */

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

    /*!
     * \brief Zoom in the battle view
     * \param value Multiplier for the zoom intensity, if less than one will zoom out
     * \sa zoomOut(RealType)
     */
    void zoomIn(RealType value = Traits<BattleWidget>::zoomInMultiplier) { _set_zoom(value);  }

    /*!
     * \brief Zoom out the battle view
     * \param value Multiplier for the zoom intensity, if less than one will zoom in
     * \sa zoomIn(RealType)
     */
    void zoomOut(RealType value = Traits<BattleWidget>::zoomOutMultiplier) { _set_zoom(1/value);  }

    /*!
     * \brief Move the battle view
     * \param dx X parameter, it will move(not to outside the scene) this amount in the x diretion
     * \param dy Y parameter, it will move(not to outside the scene) this amount in the y diretion
     */
    void translate(IntegerType dx, IntegerType dy) { _gview->translate(dx, dy); }

    /*!
     * \brief Show an arrow following the mouse
     * \param x Arrow's tail x position
     * \param y Arrow's tail y position
     * \sa hideArrow()
     */
    void showArrow(UIntegerType x, UIntegerType y) { _arrow_item->setPos(x, y); _arrow_item->show(); }

    /*!
     * \brief Hide the arrow
     * \sa showArrow(UIntegerType, UIntegerType)
     */
    void hideArrow() { _arrow_item->hide(); }

    /*!
     * \brief Verify if the skill buttons are visible
     * \return true if they are visible, false otherwise
     */
    bool skillButtonsVisible() const;

    /*!
     * \brief Show the skill buttons based on the information in 'u'
     * \param u The UnitInfo containing the information about the skills' icon and quantity
     */
    void showSkillButtons(const UnitInfo *u);

    /*!
     * \brief Hide the skill buttons
     */
    void hideSkillButtons();

    /*!
     * \brief Add an unit to the graphics scene and to the battle engine
     * \param i Information about the unit that will be added
     * \param c Unit controller, it will choose the skills to be performed
     * \param f Factory to create the unit animation
     * \param team Team of the unit that will be added
     */
    void addUnit(UnitInfo *i, UnitController *c, UnitAnimationItemFactory *f, UIntegerType team);

    /*!
     * \brief Add a creature to the graphics scene and to the battle engine
     * \param name Name of the creature type that will be added
     * \param level Level of the creature
     * \param team Team of the creature
     * \sa addUnit(UnitInfo *, UnitController *, UnitAnimationItemFactory, UIntegerType)
     * \return true if it succeds, false otherwise(It can fail if the creature type is invalid)
     */
    bool addCreature(std::string name, UIntegerType level, UIntegerType team);

    /*!
     * \brief Add a hero to the graphics scene and to the battle engine
     * \param name Name of the hero's job/class
     * \param attr The attributes of the hero
     * \param team Hero's team
     * \sa addUnit(UnitInfo *, UnitController *, UnitAnimationItemFactory, UIntegerType)
     * \return true if it succeds, false otherwise(It can fail if the job/class is invalid)
     */
    bool addHero(std::string name, const Character::Attributes& attr, UIntegerType team);

    /*!
     * \brief Add a hero to the graphics scene and to the battle engine
     * \param c Hero/Character that will be added
     * \param team Hero's team
     * \return true if it succeds, false otherwise(It can fail if the hero has an invalid job/class)
     */
    bool addHero(const Character& c, UIntegerType team) { return addHero(c.className(), c.attributes(), team); }

    /*!
     * \brief Display a message on the screen, it will stay there until a click is performed
     */
    void displayMessage(std::string);

    /*!
     * \brief Return the interface for input
     * \return Input interface of the BattleWidget
     */
    InputInterface inputInterface() const { return _input_interface; }

    /*!
     * \brief Show the cancel button
     */
    void showCancelButton();

    /*!
     * \brief Hide the cancel button
     */
    void hideCancelButton();

public slots:

    /*!
     * \brief Perform a step in the engine and redraw animations
     */
    void step();

protected:

    virtual void resizeEvent(QResizeEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void graphicsViewMouseMoveEvent(QMouseEvent *event) override;

    virtual void graphicsViewMouseReleaseEvent(QMouseEvent *event) override;

private slots:

    void _skill_button_clicked(UIntegerType id);

    void on_cancelButton_clicked();

    void on_returnButton_clicked();

private:

    void _update_buttons();
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

    UIntegerType _current_buttons;
    std::vector<IdButton *> _skill_buttons;

    QGraphicsPixmapItem *_arrow_item;
    QLabel *_message;

    InputInterface _input_interface;

    std::vector<UnitAnimationItem *> _animations;

    Ui::BattleWidget *_ui;
};

#include "battlewidget_inputmanager.h"

#endif // BATTLEWIDGET_H
