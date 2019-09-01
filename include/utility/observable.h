
#ifndef UTILITY_OBSERVABLE_H
#define UTILITY_OBSERVABLE_H

#include <vector>
#include <algorithm>
#include <forward_list>

namespace utility {

template<typename ObservableClass, typename... Args>
class Observable {

public:

    class Observer;
    using ObserverList = std::vector<Observer *>;

    virtual ~Observable();

    bool attach(Observer *obs);
    bool detach(Observer *obs);

    void detachAll();

    void notify(Args... args) const;

    const ObserverList& observers() const { return _observers; }

private:

    ObservableClass *self() { return static_cast<ObservableClass *>(this); }
    const ObservableClass *self() const { return static_cast<const ObservableClass *>(this); }

    bool _simple_detach(Observer *obs);

    ObserverList _observers;
};

template<typename ObservableClass, typename... Args>
class Observable<ObservableClass, Args...>::Observer {

    friend class Observable;

public:

    using ObservedList = std::forward_list<ObservableClass *>;

    virtual ~Observer();

    virtual void update(const ObservableClass *, Args...) = 0;

    virtual void observableDestroyed(const ObservableClass *) {}

    const ObservedList& observeds() const { return _observeds; }

private:

    void _attach(ObservableClass *obsvable) { _observeds.push_front(obsvable); }

    bool _detach(ObservableClass *obsvable) {

        auto prev_it = _observeds.before_begin();
        for(auto it = _observeds.begin(); it != _observeds.end(); ++it) {

            if(*it == obsvable) {

                _observeds.erase_after(prev_it);
                return true;
            }

            prev_it = it;
        }

        return false;
    }

    ObservedList _observeds;
};

template<typename ObservableClass, typename... Args>
Observable<ObservableClass, Args...>::~Observable() {

    for(Observer *obs : _observers) {

        if(obs->_detach(self())) obs->observableDestroyed(self());
    }
}

template<typename ObservableClass, typename... Args>
bool Observable<ObservableClass, Args...>::attach(Observer *obs) {

    if(std::find(_observers.begin(), _observers.end(), obs) != _observers.end()) return false;

    _observers.push_back(obs);
    obs->_attach(self());

    return true;
}

template<typename ObservableClass, typename... Args>
bool Observable<ObservableClass, Args...>::detach(Observer *obs) {

    if(_simple_detach(obs)) {

        obs->_detach(self());
        return true;
    }

    return false;
}

template<typename ObservableClass, typename... Args>
void Observable<ObservableClass, Args...>::detachAll() {

    for(Observer *obs : _observers) obs->_detach(self());

    _observers.clear();
}

template<typename ObservableClass, typename... Args>
void Observable<ObservableClass, Args...>::notify(Args... args) const {

    for(Observer *obs : _observers) obs->update(self(), args...);
}

template<typename ObservableClass, typename... Args>
bool Observable<ObservableClass, Args...>::_simple_detach(Observer *obs) {

    auto it = std::find(_observers.begin(), _observers.end(), obs);

    if(it == _observers.end()) return false;

    *it = _observers.back();
    _observers.pop_back();

    return true;
}

template<typename ObservableClass, typename... Args>
Observable<ObservableClass, Args...>::Observer::~Observer() {

    for(Observable *obsvable : _observeds) obsvable->_simple_detach(this);
}

} /* namespace utility */

#endif // UTILITY_OBSERVABLE_H
