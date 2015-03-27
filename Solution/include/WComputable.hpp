#pragma once

#include <memory>

class WComputable{
public:
  template <typename T>
  WComputable(T x): _sharedObject(std::make_shared< MComputable<T> >(std::move(x))) {
  }

  void calculate (){
    //Redirects to Model's _compute implementation
    _sharedObject->_compute();
  }

private:
  struct CComputable{
    virtual void _compute() = 0;
  };

  template<typename T>
  struct MComputable : CComputable {
    MComputable(T o) : o(std::move(o)) {}

    void _compute() {
      // This method has to be implemented in your classes
      o.compute();
    }

    T o;
  };

  
  std::shared_ptr<CComputable> _sharedObject;
};
