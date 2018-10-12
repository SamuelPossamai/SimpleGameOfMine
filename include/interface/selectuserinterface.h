
#ifndef SELECTUSERINTERFACE_H
#define SELECTUSERINTERFACE_H

#include <vector>

#include "selectuserinterfacebase.h"

namespace Ui {
class SelectUserInterface;
} /* namespace Ui */

class SelectUserInterface : public SelectUserInterfaceBase {

    Q_OBJECT

public:

    SelectUserInterface(const utility::Interval<UIntegerType>& n_characters = {1, 3}, MainWindow *parent = nullptr);

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
