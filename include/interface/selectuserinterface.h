
#ifndef SELECTUSERINTERFACE_H
#define SELECTUSERINTERFACE_H

#include <vector>

#include "mainwidget.h"

namespace Ui {
class SelectUserInterface;
} /* namespace Ui */

class SelectUserInterface : public MainWidget {

    Q_OBJECT

public:

    SelectUserInterface(MainWindow *parent = nullptr);

    virtual void activate() override;

private slots:

    void on_returnButton_clicked();

    void on_deleteButton_clicked();

    void on_newButton_clicked();

    void on_selectButton_clicked();

private:

    UIntegerType _selected_count() const;
    std::vector<std::string> _get_selecteds() const;

    Ui::SelectUserInterface *_ui;
};

#endif // SELECTUSERINTERFACE_H
