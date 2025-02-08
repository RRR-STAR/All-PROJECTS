
/** *.h++ file for classes and @def */

#include <iostream>
using namespace std;
#define  System  (*System)

class out_{
  private :  out_(){}  virtual ~out_(){}  friend class sys_;
  public :  void print(auto val){ cout << val; }
};
class in_{
  private :  in_(){}  virtual ~in_(){}  friend class sys_;
  public :  auto scan(auto &val){ cin >> val;  return val; }
};
class sys_{
  private :  sys_(){}  virtual ~sys_(){}
  public :  out_ out;  in_ in;
} 
System;
