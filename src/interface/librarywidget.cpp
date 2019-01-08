
#include <iostream>

#include "sgomfiles.h"
#include "librarywidgetinfotab.h"
#include "librarywidget.h"
#include "ui_librarywidget.h"

LibraryWidget::LibraryWidget(MainWindow *parent) : MainWidget(parent), _ui(new Ui::LibraryWidget) {

    _ui->setupUi(this);

    _ui->tabWidget->setCurrentIndex(0);

    for(auto s : SGOMFiles::findDataFiles("library", ".conf")) _add_info(s);
}

LibraryWidget::~LibraryWidget() {

    delete _ui;
}

void LibraryWidget::on_returnButton_clicked() {

    parent()->popWidget();
}

void LibraryWidget::_add_info(const std::string& filename) {

    auto opt = SGOMFiles::readSGOMEntryFile(filename);

    if(!opt) return;

    auto map = *opt;

    const auto & section_v = map["Section"];
    const auto & name_v = map["Name"];
    const auto & image_v = map["Image"];

    if(!_add_info_verify(section_v.size(), 1, filename.c_str(), "Section")) return;
    if(!_add_info_verify(name_v.size(), 1, filename.c_str(), "Name")) return;
    if(!_add_info_verify(image_v.size(), 1, filename.c_str(), "Image")) return;

    QString section_name = QString::fromStdString(section_v.front());
    IntegerType section_id = _tab_widget_tab_exist(_ui->tabWidget, section_name);

    if(section_id == -1) {

        _ui->tabWidget->addTab(new QTabWidget, section_name);
        section_id = _tab_widget_tab_exist(_ui->tabWidget, section_name);
    }

    QTabWidget *tab_section = static_cast<QTabWidget *>(_ui->tabWidget->widget(int(section_id)));

    QString name = QString::fromStdString(name_v.front());
    IntegerType name_id = _tab_widget_tab_exist(tab_section, name);

    if(name_id == -1) {

        tab_section->addTab(new LibraryWidgetInfoTab, name);
        name_id = _tab_widget_tab_exist(tab_section, name);
    }

    LibraryWidgetInfoTab *info_tab = static_cast<LibraryWidgetInfoTab *>(tab_section->widget(int(name_id)));

    info_tab->setImage(image_v.front());
    info_tab->setText(map["Text"]);
    info_tab->setMainAttributes(map["Main Attributes"]);
    info_tab->setMinorAttributes(map["Minor Attributes"]);
    info_tab->setObservation(map["Observation"]);
}

bool LibraryWidget::_add_info_verify(UIntegerType size, UIntegerType desired_size, const char *filetext, const char *entrytext){

    if(size != desired_size) {

        std::cerr << "Library file " << filetext << " must have exactly "
                  << desired_size << " '" << entrytext << "' but has " << size << std::endl;

        return false;
    }

    return true;
}

IntegerType LibraryWidget::_tab_widget_tab_exist(QTabWidget *tab_widget, QString tab_name) {

    for(IntegerType i = 0; i < tab_widget->count(); i++) {

        if(tab_widget->tabText(int(i)) == tab_name) return i;
    }

    return -1;
}
