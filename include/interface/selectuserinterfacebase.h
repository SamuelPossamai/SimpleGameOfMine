
#ifndef SELECTUSERINTERFACEBASE_H
#define SELECTUSERINTERFACEBASE_H

#include <iterator>

#include "utility/interval.h"

#include "mainwidget.h"
#include "gamedefaultscreen.h"

class SelectUserInterfaceBase : public MainWidget {

    Q_OBJECT

public:

    SelectUserInterfaceBase(const utility::Interval<UIntegerType>& n_characters, MainWindow *parent = nullptr) :
        MainWidget(parent), _n_chars(n_characters) {}

    UIntegerType minCharacters() const { return _n_chars.min(); }
    UIntegerType maxCharacters() const { return _n_chars.max(); }

    const utility::Interval<UIntegerType>& charactersNumber() const { return _n_chars; }

protected:

    template <typename ITER>
    bool finalize(const ITER& begin, const ITER& end) {

        if(!_n_chars.inRange(std::distance(begin, end))) return false;

        parent()->swapWidget(new GameDefaultScreen({ begin, end }));

        return true;
    }

    template <typename CONTAINER>
    bool finalize(const CONTAINER& c) { return finalize(c.begin(), c.end()); }

private:

    utility::Interval<UIntegerType> _n_chars;
};

#endif // SELECTUSERINTERFACEBASE_H
