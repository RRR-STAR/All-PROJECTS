
#include <iostream>
#include "NumberSystem.h++"


class __NumberSystem__ : public NumberSystem {
  
  public :
  
  __NumberSystem__():
  NumberSystem()/* constructor of the Base Class doesn't inherit but the derived class have the access of it */{}
  ~__NumberSystem__(){}
  
  void input() override { NumberSystem :: input(); }
  
  const char* getBinary(){
    std::cout <<"\n in __NumberSystem__.getBinary() : ";
    std::cout << NumberSystem :: getBinary(); 
  }
  
  // if the getOctal() or other functions is not mentioned virtual then the Base class func's are called rather than Derived class func's
  
  const char* getOctal(){
    std::cout <<"\n in __NumberSystem__.getOctal()  : ";
    std::cout << NumberSystem :: getOctal();
  }
  
};


main(){
  
  NumberSystem  *n = new __NumberSystem__();
  
  n->input();
  
  n->getBinary();
  n->getOctal();
  
  // if the getOctal() in the Base class is not virtual then ,
  // std::cout <<std::endl<< n->getOctal();
  
  delete n;   n = nullptr;
  
  std::cin.get();  return 0;
}

