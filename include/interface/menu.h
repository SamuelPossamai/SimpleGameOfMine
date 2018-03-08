#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>

#include "types.h"

class Menu : public QWidget {

public:

    Menu(MainWindow *parent = nullptr);

    void setParent(MainWindow *);
    void setParent(QWidget *) = delete;

private slots:

    void _player_vs_ai_start_button_clicked();
    void _player_vs_player_start_button_clicked();
    void _help_button_clicked();
    void _challenge_start_button_clicked();

private:

    using ButtonsVector = std::vector<QPushButton *>;

    void _place_buttons();

    ButtonsVector _buttons;
};

#endif // MENU_H
