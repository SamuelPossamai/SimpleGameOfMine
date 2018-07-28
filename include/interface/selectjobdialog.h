
#ifndef SELECTJOBDIALOG_H
#define SELECTJOBDIALOG_H

#include <QDialog>

#include <config/types.h>

namespace Ui {
class SelectJobDialog;
} /* namespace Ui */

class SelectJobDialog : public QDialog {

    Q_OBJECT

public:

    explicit SelectJobDialog(Character& c, QWidget *parent = 0);

    ~SelectJobDialog();

private slots:

    void on_buttonBox_accepted();

private:

    Character& _char;
    Ui::SelectJobDialog *_ui;
};

#endif // SELECTJOBDIALOG_H
