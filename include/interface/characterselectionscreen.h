
#ifndef CHARACTERSELECTIONSCREEN_H
#define CHARACTERSELECTIONSCREEN_H

#include "selectuserinterfacebase.h"

namespace Ui {
class CharacterSelectionScreen;
} /* namespace Ui */

class CharacterSelectionScreen : public SelectUserInterfaceBase {

    Q_OBJECT

public:

    explicit CharacterSelectionScreen(const utility::Interval<UIntegerType>& n_characters, MainWindow *parent = nullptr);
    ~CharacterSelectionScreen();

    void activate() final;

private slots:

    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_returnButton_clicked();

    void on_selectButton_clicked();

    void on_goButton_clicked();

    void on_deleteButton_clicked();

    void on_newButton_clicked();

private:

    void _update_image();

    bool _is_selected(const std::string& name) { return std::find(_selecteds.begin(), _selecteds.end(), name) == _selecteds.end(); }

    Ui::CharacterSelectionScreen *ui;

    UIntegerType _cur;
    std::vector<std::string> _char_names;
    std::vector<std::string> _selecteds;
};

#endif // CHARACTERSELECTIONSCREEN_H
