
#ifndef GAMEDEFAULTSCREEN_H
#define GAMEDEFAULTSCREEN_H

#include <engine/character.h>

#include "mainwidget.h"

namespace Ui {
class GameDefaultScreen;
} /* namespace Ui */

class QListWidgetItem;

class GameDefaultScreen : public MainWidget {

    Q_OBJECT

public:

    explicit GameDefaultScreen(std::vector<std::string> players, MainWindow *parent = nullptr);
    virtual ~GameDefaultScreen();

protected:

    virtual void activate() override;

private slots:

    void on_menuButton_clicked();

    void on_charactersList_itemClicked(QListWidgetItem *item);

    void on_exploreButton1_clicked();

    void on_strAddButton_clicked();

    void on_vitAddButton_clicked();

    void on_dexAddButton_clicked();

    void on_agiAddButton_clicked();

    void on_infoButton_clicked();

private:

    void _start_battle(CreatureMap *m);
    void _reselect() { _select_char_info(_selected); }
    void _select_char_info(UIntegerType id);
    void _assign_point(UIntegerType id);

    UIntegerType _xp_for_victory;
    UIntegerType _result;
    UIntegerType _selected;

    std::vector<Character> _chars;

    Ui::GameDefaultScreen *_ui;
};

#endif // GAMEDEFAULTSCREEN_H
