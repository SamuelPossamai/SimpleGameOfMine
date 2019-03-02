
#ifndef BATTLEWIDGET_H
#define BATTLEWIDGET_H

#include <memory>

#include <config/metatypes.h>
#include <config/interface_traits.h>
#include <engine/unitcontroller.h>
#include <engine/character.h>
#include <engine/projectile.h>

#include "gameinfo/projectiles.h"
#include "graphicsview.h"
#include "mainwidget.h"

namespace Ui {
class BattleWidget;
} /* namespace Ui */

class QLabel;
class QGraphicsPixmapItem;

/*!
 * \brief Widget that manages the interface in a battle
 */
class BattleWidget : public MainWidget, public GraphicsView::Handler {

    Q_OBJECT
    Q_PROPERTY(Qt::Alignment skillButtonAlign READ skillButtonAlign WRITE setSkillButtonAlign)
    Q_PROPERTY(RealType skillButtonSize READ skillButtonSize WRITE setSkillButtonSize)
    Q_PROPERTY(RealType skillButtonDistance READ skillButtonDistance WRITE setSkillButtonDistance)
    Q_PROPERTY(RealType skillButtonBorderVDistance READ skillButtonBorderVDistance WRITE setSkillButtonBorderVDistance)
    Q_PROPERTY(RealType skillButtonBorderHDistance READ skillButtonBorderHDistance WRITE setSkillButtonBorderHDistance)

public:

    class InputManager;
    using InputInterface = std::shared_ptr<InputManager>;

    class ProjectileCreationInterface;

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

    virtual ~BattleWidget() override;

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
    void showArrow(UIntegerType x, UIntegerType y);

    /*!
     * \brief Hide the arrow
     * \sa showArrow(UIntegerType, UIntegerType)
     */
    void hideArrow();

    /*!
     * \brief Verify if the skill buttons are visible
     * \return true if they are visible, false otherwise
     */
    bool skillButtonsVisible() const;

    /*!
     * \brief Show the skill buttons based on the information in 'u'
     * \param u The Unit whose skills will be shown
     */
    void showSkillButtons(const Unit *u);

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
    void addUnit(UnitInfo *i, UnitController *c, UnitAnimationItemFactory *f,
                 const UnitAttributes& attr, UIntegerType level, UIntegerType team);

    /*!
     * \brief Add a creature to the graphics scene and to the battle engine
     * \param name Name of the creature type that will be added
     * \param level Level of the creature
     * \param team Team of the creature
     * \sa addUnit(UnitInfo *, UnitController *, UnitAnimationItemFactory, UIntegerType)
     * \return true if it succeds, false otherwise(It can fail if the creature type is invalid)
     */
    bool addCreature(std::string name, const UnitAttributes& attr, UIntegerType level, UIntegerType team);

    /*!
     * \brief Add a hero to the graphics scene and to the battle engine
     * \param name Name of the hero's job/class
     * \param attr The attributes of the hero
     * \param team Hero's team
     * \sa addUnit(UnitInfo *, UnitController *, UnitAnimationItemFactory, UIntegerType)
     * \return true if it succeds, false otherwise(It can fail if the job/class is invalid)
     */
    bool addHero(std::string name, const Character::Attributes& attr, UIntegerType level, UIntegerType team);

    /*!
     * \brief Add a hero to the graphics scene and to the battle engine
     * \param c Hero/Character that will be added
     * \param team Hero's team
     * \return true if it succeds, false otherwise(It can fail if the hero has an invalid job/class)
     */
    bool addHero(const Character& c, UIntegerType team) { return addHero(c.className(), c.attributes(), c.level(), team); }

    void addProjectile(ProjectileFactory *projFactory, ProjectileAnimationItemFactory *itemFactory,
                       const Unit *creator, Projectile::AngleType dir, Projectile::PointType pos,
                       Projectile::AngleType angle);

    bool addProjectile(const std::string& projectile_type, const Unit *creator,
                       const gameinfo::Projectiles::ProjectileInfo& p_info,
                       Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle);

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

    void setSkillButtonAlign(Qt::Alignment alignment) { _alignment = alignment; }

    Qt::Alignment skillButtonAlign() const { return _alignment; }

    void setSkillButtonSize(RealType button_size) { _skill_button_size = button_size; }

    RealType skillButtonSize() const { return _skill_button_size; }

    void setSkillButtonDistance(RealType button_distance) { _skill_button_distance = button_distance; }

    RealType skillButtonDistance() const { return _skill_button_distance; }

    void setSkillButtonBorderVDistance(RealType border_vdist) { _skill_button_border_vertical_distance = border_vdist; }

    RealType skillButtonBorderVDistance() const { return _skill_button_border_vertical_distance; }

    void setSkillButtonBorderHDistance(RealType border_hdist) { _skill_button_border_horizontal_distance = border_hdist; }

    RealType skillButtonBorderHDistance() const { return _skill_button_border_horizontal_distance; }

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
    std::pair<UIntegerType, UIntegerType> _decode_aligment() const;

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

    std::vector<AnimationItemBase *> _animations;

    Qt::Alignment _alignment;

    RealType _skill_button_size;
    RealType _skill_button_distance;
    RealType _skill_button_border_vertical_distance;
    RealType _skill_button_border_horizontal_distance;

    Ui::BattleWidget *_ui;
};

class BattleWidget::ProjectileCreationInterface {

public:

    ProjectileCreationInterface(BattleWidget *bw) : _bw(bw) {}

    bool create(const std::string& projectile_type, const Unit *creator,
                const gameinfo::Projectiles::ProjectileInfo& p_info,
                Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle) {

        return _bw->addProjectile(projectile_type, creator, p_info, dir, pos, angle);
    }

private:

    BattleWidget *_bw;
};

#endif // BATTLEWIDGET_H

#include "battlewidget_inputmanager.h"
