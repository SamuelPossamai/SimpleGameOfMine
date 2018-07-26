
#ifndef CHARACTERINFODIALOG_H
#define CHARACTERINFODIALOG_H

#include <QDialog>

#include <config/types.h>

namespace Ui {
class CharacterInfoDialog;
} /* namespace Ui */

class CharacterInfoDialog : public QDialog {

    Q_OBJECT

public:

    explicit CharacterInfoDialog(const Character& c, QWidget *parent = 0);
    ~CharacterInfoDialog();

private:

    void _init(const Character& c);

    Ui::CharacterInfoDialog *_ui;
};

#endif // CHARACTERINFODIALOG_H
