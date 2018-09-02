
#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

template <typename T>
class SingleObject {

public:

    SingleObject() : _obj(nullptr) {}
    SingleObject(const SingleObject&) = delete;
    ~SingleObject() { destroy(); }
    
    T *get() {
    
        if(_obj == nullptr) _obj = new T;
        return _obj;
    }
    
    void create() { get(); }
    
    void destroy() {
    
        if(_obj) {
        
            delete _obj;
            _obj = nullptr;
        }
    }
    
    T *operator->() { return get(); }
    
    operator T *() { return get(); }
    
private:

    T *_obj;
};


#endif // SINGLEOBJECT_H
