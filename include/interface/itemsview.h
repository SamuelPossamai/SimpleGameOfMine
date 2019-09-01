
#ifndef ITEMSVIEW_H
#define ITEMSVIEW_H

#include <QWidget>

#include "types.h"
#include "character.h"

namespace Ui {
class ItemsView;
} /* namespace Ui */

class ItemsView : public QWidget {

    Q_OBJECT

public:

    explicit ItemsView(QWidget *parent = nullptr);
    explicit ItemsView(const std::string& character, QWidget *parent = nullptr) : ItemsView(parent) { setCharacter(character); }

    virtual ~ItemsView() override;

    void setCharacter(const std::string& name) { setCharacter(Character(name)); }
    void setCharacter(const Character& c) { _c = c; updateItems(); }
    void clear();

    void updateItems();

protected:

    virtual void resizeEvent(QResizeEvent *) override;

private:

    void _update_row_count();
    UIntegerType _min_rows() const;

    Ui::ItemsView *_ui;
    Character _c;
};

#endif // ITEMSVIEW_H
