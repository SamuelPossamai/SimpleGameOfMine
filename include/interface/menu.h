#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>

#include "types.h"
#include "mainwidget.h"

class Menu : public MainWidget {

public:

    Menu(MainWindow *parent = nullptr);

    void setParent(MainWindow *);
    void setParent(QWidget *) = delete;

private slots:

    void _player_vs_ai_start_button_clicked();
    void _start_button_clicked();
    void _help_button_clicked();
    void _challenge_start_button_clicked();

private:

    using ButtonsVector = std::vector<QPushButton *>;

    void _place_buttons();

    bool _wating_battle_result;
    UIntegerType _result;
    ButtonsVector _buttons;
};

#endif // MENU_H
