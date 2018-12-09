
#include <iostream>

#include <QMessageBox>
#include <QThread>

#include "sgomfiles.h"
#include "configurationscreen.h"
#include "ui_configurationscreen.h"

ConfigurationScreen::ConfigurationScreen(MainWindow *parent) : MainWidget(parent),
    ui(new Ui::ConfigurationScreen) {

    ui->setupUi(this);

    auto map = SGOMFiles::get()->readSGOMConfigFile();

    IntegerType mode_id = ui->characterSelectionScreenComboBox->findText(map["Character Selection Screen"]["mode"].c_str());

    if(mode_id == -1) {

        std::cerr << "Invalid option chosen for character selection screen mode in the configuration" << std::endl;
    }
    else ui->characterSelectionScreenComboBox->setCurrentIndex(mode_id);

    ui->windowFullscreenCheckBox->setChecked(map["Game Start"]["fullscreen"] == "yes");

    _saved = true;
}

ConfigurationScreen::~ConfigurationScreen() {

    delete ui;
}

void ConfigurationScreen::on_returnButton_clicked() {

    if(!_saved) {

        if(QMessageBox::question(this, "SGOM Warning", "Are you sure you want to exit without saving?")
                != QMessageBox::Yes) {

            return;
        }
    }

    parent()->popWidget();
}

void ConfigurationScreen::on_saveButton_clicked() {

    QMessageBox::information(this, "SGOM Info", "Settings saved");

    _saved = true;

    SGOMFiles::ConfigFileInfo cfi;

    cfi["Character Selection Screen"]["mode"] = ui->characterSelectionScreenComboBox->currentText().toStdString();
    cfi["Game Start"]["fullscreen"] = ui->windowFullscreenCheckBox->isChecked() ? "yes" : "no";

    SGOMFiles::get()->writeSGOMConfigFile(cfi);
}

void ConfigurationScreen::on_characterSelectionScreenComboBox_currentIndexChanged(int) {

    _saved = false;
}
