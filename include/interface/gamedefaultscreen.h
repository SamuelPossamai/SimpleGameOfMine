
#ifndef GAMEDEFAULTSCREEN_H
#define GAMEDEFAULTSCREEN_H

#include <engine/character.h>

#include "mainwidget.h"

namespace Ui {
class GameDefaultScreen;
} /* namespace Ui */

class QListWidgetItem;

/*!
 * \brief Basic screen to display basic information about characters and to explore maps
 */
class GameDefaultScreen : public MainWidget {

    Q_OBJECT

public:

    /*!
     * \brief Construct a GameDefaultScreen, passing the players
     * \param players Characters that are currently playing
     * \param parent Parent of this QObject
     */
    explicit GameDefaultScreen(std::vector<std::string> players, MainWindow *parent = nullptr);
    virtual ~GameDefaultScreen() override;

protected:

    virtual void activate() override;

private slots:

    void on_menuButton_clicked();

    void on_charactersList_itemClicked(QListWidgetItem *item);

    void on_exploreButton1_clicked();

    void on_exploreButton2_clicked();

    void on_exploreButton3_clicked();

    void on_strAddButton_clicked();

    void on_vitAddButton_clicked();

    void on_dexAddButton_clicked();

    void on_agiAddButton_clicked();

    void on_wisAddButton_clicked();

    void on_infoButton_clicked();

    void on_changeJobButton_clicked();

private:

    void _start_battle(gameinfo::CreatureMap *m);
    void _reselect() { _select_char_info(_selected); }
    void _select_char_info(UIntegerType id);
    void _assign_point(UIntegerType id);

    UIntegerType _xp_for_victory;
    UIntegerType _result;
    UIntegerType _selected;

    std::vector<std::string> _itens_for_victory;

    std::vector<Character> _chars;

    Ui::GameDefaultScreen *_ui;
};

#endif // GAMEDEFAULTSCREEN_H
