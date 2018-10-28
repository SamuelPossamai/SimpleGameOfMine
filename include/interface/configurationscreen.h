
#ifndef CONFIGURATIONSCREEN_H
#define CONFIGURATIONSCREEN_H

#include "mainwidget.h"

namespace Ui {
class ConfigurationScreen;
} /* namespace Ui */

class ConfigurationScreen : public MainWidget {

    Q_OBJECT

public:

    explicit ConfigurationScreen(MainWindow *parent = nullptr);
    ~ConfigurationScreen() final;

private slots:

    void on_returnButton_clicked();

    void on_saveButton_clicked();

    void on_characterSelectionScreenComboBox_currentIndexChanged(int);

private:

    Ui::ConfigurationScreen *ui;

    bool _saved;
};

#endif // CONFIGURATIONSCREEN_H
