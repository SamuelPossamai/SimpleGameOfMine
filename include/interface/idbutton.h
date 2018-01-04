#ifndef IDBUTTON_H
#define IDBUTTON_H

#include <QPushButton>

#include "types.h"

class IdButton : public QPushButton {

    Q_OBJECT

public:

    IdButton(UIntegerType id, QWidget *parent) : QPushButton(parent), _id(id) {

        QObject::connect(this, &IdButton::clicked, this, &IdButton::_button_signal_received);
    }

private slots:

    void _button_signal_received() {

        emit clickedId(_id);
    }

signals:

    void clickedId(UIntegerType id);

private:

    UIntegerType _id;
};

#endif // IDBUTTON_H
