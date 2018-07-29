
#ifndef CHARACTERINFODIALOG_H
#define CHARACTERINFODIALOG_H

#include <QDialog>

#include <config/types.h>

namespace Ui {
class CharacterInfoDialog;
} /* namespace Ui */

/*!
 * \brief The CharacterInfoDialog class is used to display information about a character
 */
class CharacterInfoDialog : public QDialog {

    Q_OBJECT

public:

    /*!
     * \brief Construct an CharacterInfoDialog to display the information about a character
     * \param c Character whose information will be shown
     * \param parent Parent object
     */
    explicit CharacterInfoDialog(const Character& c, QWidget *parent = 0);
    ~CharacterInfoDialog();

private:

    void _init(const Character& c);

    Ui::CharacterInfoDialog *_ui;
};

#endif // CHARACTERINFODIALOG_H
