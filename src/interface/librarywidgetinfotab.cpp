
#include "config/types.h"
#include "librarywidgetinfotab.h"
#include "ui_librarywidgetinfotab.h"

LibraryWidgetInfoTab::LibraryWidgetInfoTab(QWidget *parent) : QWidget(parent), ui(new Ui::LibraryWidgetInfoTab) {

    ui->setupUi(this);
}

LibraryWidgetInfoTab::~LibraryWidgetInfoTab() {

    delete ui;
}

void LibraryWidgetInfoTab::setImage(const char *image_file) {

    ui->imageLabel->setText(QString("<html><head/><body><p><img src=\"") + image_file + "\"/></p></body></html>");
}

void LibraryWidgetInfoTab::_update_text() {

    QString text_prologue = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                            "p, li { white-space: pre-wrap; } </style></head><body style=\" font-family:'Noto Sans'; "
                            "font-size:10pt; font-weight:400; font-style:normal;\">";

    QString string_prologue = "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; "
                              "-qt-block-indent:0; text-indent:0px;\">";

    QString string_epilogue = "</p>";

    QString text_epilogue = "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; "
                            "margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>";

    QString final_text = text_prologue;

    for(const auto& text_line : _text) {

        final_text += string_prologue + QString::fromStdString(text_line) + string_epilogue;
    }

    _write_attr(final_text, _major_attrs, "Main Attributes: ", string_prologue, string_epilogue);
    _write_attr(final_text, _minor_attrs, "Minor Attributes: ", string_prologue, string_epilogue);

    for(const auto& text_line : _observation) {

        final_text += string_prologue + QString::fromStdString(text_line) + string_epilogue;
    }

    final_text += text_epilogue;

    ui->textBrowser->setText(final_text);
}

void LibraryWidgetInfoTab::_write_attr(QString& target, const std::vector<std::string>& attrs, const char *start_str,
                                       const QString& string_prologue, const QString& string_epilogue) {
    if(attrs.empty()) return;

    target += string_prologue;
    target += "<b>";
    target += start_str;
    target += "</b>";

    for(UIntegerType i = 0; i < attrs.size() - 1; i++) {

        _write_single_attr(target, attrs[i]);
        target += ", ";
    }

    _write_single_attr(target, attrs[attrs.size() - 1]);

    target += string_epilogue;
}

void LibraryWidgetInfoTab::_write_single_attr(QString& target, const std::string& attr) {

    const char *color = "black";

    if(attr == "VIT" || attr == "Vitality") color = "#f8c471";
    else if(attr == "STR" || attr == "Strength") color = "red";
    else if(attr == "AGI" || attr == "Agility") color = "blue";
    else if(attr == "DEX" || attr == "Dexterity") color = "green";
    else if(attr == "WIS" || attr == "Wisdom") color = "purple";

    target += "<font color='";
    target += color;
    target += "'>";

    target += attr.c_str();
    target += "</font>";
}
