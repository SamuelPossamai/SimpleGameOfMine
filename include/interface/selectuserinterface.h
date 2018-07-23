
#ifndef SELECTUSERINTERFACE_H
#define SELECTUSERINTERFACE_H

#include <vector>

#include <QTableWidget>
#include <QLabel>
#include <QPushButton>

#include "mainwidget.h"

class SelectUserInterface : public MainWidget {

public:

    SelectUserInterface(MainWindow *parent = nullptr);

    virtual void activate() override;

private slots:

    void _return_button_clicked();
    void _delete_button_clicked();
    void _new_button_clicked();
    void _select_button_clicked();

private:

    UIntegerType _selected_count() const;
    std::vector<std::string> _get_selecteds() const;

    QTableWidget *_list;
    QLabel *_char_label;

    std::vector<QPushButton *> _buttons;
};

#endif // SELECTUSERINTERFACE_H
