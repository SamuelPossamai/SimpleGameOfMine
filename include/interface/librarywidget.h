
#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include "mainwidget.h"

namespace Ui {
class LibraryWidget;
}

class LibraryWidget : public MainWidget {

    Q_OBJECT

public:

    explicit LibraryWidget(MainWindow *parent = 0);
    ~LibraryWidget();

private slots:

    void on_returnButton_clicked();

private:

    void _add_info(const std::string& filename);
    bool _add_info_verify(UIntegerType size, UIntegerType desired_size, const char *filetext, const char *entrytext);
    static IntegerType _tab_widget_tab_exist(QTabWidget *tab_widget, QString tab_name);

    Ui::LibraryWidget *_ui;
};

#endif // LIBRARYWIDGET_H
