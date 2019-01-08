
#include <algorithm>

#include <QResizeEvent>
#include <QTableWidget>

#include "imagewidget.h"
#include "itemsview.h"
#include "ui_itemsview.h"

#include "gameinfo/items.h"

ItemsView::ItemsView(QWidget *parent) : QWidget(parent), _ui(new Ui::ItemsView) {

    _ui->setupUi(this);

    _ui->table->setColumnCount(8);
    _ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

ItemsView::~ItemsView() {

    delete _ui;
}

void ItemsView::updateItems() {

    clear();

    auto& items = _c.items();
    UIntegerType column_count = UIntegerType(_ui->table->columnCount());

    UIntegerType min_rows_for_char = items.size()/column_count + items.size()%column_count != UIntegerType(0);
    _ui->table->setRowCount(int(std::max(min_rows_for_char, _min_rows())));

    UIntegerType cur_row = 0;
    UIntegerType cur_col = 0;
    for(auto item_info : items) {

        auto opt = gameinfo::Items::get(item_info.first);

        QImage im;
        QString tooltip = "<" + QString::fromStdString(item_info.first) + ">: ";
        if(opt) {

            im = std::get<0>(*opt);
            tooltip += QString::fromStdString(std::get<1>(*opt));
        }
        else {

            im = QImage(":/question_mark.png");
            tooltip += "This item is not recognized in this version of the game";
        }

        ImageWidget *im_w = new ImageWidget(im);
        im_w->setForeground(Qt::transparent);
        im_w->setBackground(Qt::transparent);
        im_w->setToolTip(tooltip);

        _ui->table->setCellWidget(int(cur_row), int(cur_col), im_w);

        if(++cur_col >= column_count) {

            cur_col = 0;
            cur_row++;
        }
    }
}

void ItemsView::clear() {

    _ui->table->clearContents();
}

void ItemsView::resizeEvent(QResizeEvent *) {

    _ui->table->verticalHeader()->setDefaultSectionSize(_ui->table->width() / _ui->table->columnCount());
    updateItems();
}

UIntegerType ItemsView::_min_rows() const {

    return UIntegerType(_ui->table->height() / _ui->table->verticalHeader()->defaultSectionSize()) + 1;
}
