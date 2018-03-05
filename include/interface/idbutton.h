#ifndef IDBUTTON_H
#define IDBUTTON_H

#include <QPushButton>

#include "types.h"

/*!
 * \brief A simples pushn button, but with an id associated.
 */
class IdButton : public QPushButton {

    Q_OBJECT

public:

    /*!
     * \brief Create an IdButton with an id.
     * \sa clickedId
     * \param id identification number, will be sent with the signal.
     * \param parent Widget where this button will be placed.
     */
    IdButton(UIntegerType id, QWidget *parent = nullptr) : QPushButton(parent), _id(id) {

        QObject::connect(this, &IdButton::clicked, this, &IdButton::_button_signal_received);
    }

signals:

    /*!
     * \brief This signal is emitted when then button is clicked.
     * \param id button identification number.
     */
    void clickedId(UIntegerType id);

private slots:

    void _button_signal_received() { emit clickedId(_id); }

private:

    UIntegerType _id;
};

#endif // IDBUTTON_H
