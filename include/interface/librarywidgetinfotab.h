
#ifndef LIBRARYWIDGETINFOTAB_H
#define LIBRARYWIDGETINFOTAB_H

#include <vector>
#include <string>

#include <QWidget>

namespace Ui {
class LibraryWidgetInfoTab;
} /* namespace Ui */

class LibraryWidgetInfoTab : public QWidget {

    Q_OBJECT

public:

    explicit LibraryWidgetInfoTab(QWidget *parent = nullptr);

    ~LibraryWidgetInfoTab();

    void setImage(const std::string& image_file) { return setImage(image_file.c_str()); }
    void setImage(const char *image_file);

    void setText(const std::vector<std::string>& text) { _text = text; _update_text(); }
    void setMainAttributes(const std::vector<std::string>& attrs) { _major_attrs = attrs; _update_text(); }
    void setMinorAttributes(const std::vector<std::string>& attrs) { _minor_attrs = attrs; _update_text(); }
    void setObservation(const std::vector<std::string>& obs) { _observation = obs; _update_text(); }

private:

    void _update_text();
    void _write_attr(QString& target, const std::vector<std::string>& attrs, const char *start_str,
                     const QString& string_prologue, const QString& string_epilogue);
    void _write_single_attr(QString& target, const std::string& attr);

    Ui::LibraryWidgetInfoTab *ui;
    std::vector<std::string> _text;
    std::vector<std::string> _observation;
    std::vector<std::string> _major_attrs;
    std::vector<std::string> _minor_attrs;
};

#endif // LIBRARYWIDGETINFOTAB_H
