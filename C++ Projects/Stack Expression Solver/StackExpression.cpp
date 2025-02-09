/**
 * @brief @details
 *  @a CODEㅤTHROUGHㅤC++ㅤFORㅤIMPLEMENTINGㅤANㅤAPPLICATIONㅤOFㅤSTACKㅤEXPRESSIONㅤCONVERTER
 * This is a program which not only can be used by the user's,
 * but also programmers can use this by inheriting the class.
 * Therefore by including the @file ["StackExpression.h++"],
 * programmer's can create objects of @class ["StackExpression<...>"] and, 
 * can use the functionalities like a converter.
 * 
*/
#include <iostream>
#include <ostream>
#include <typeinfo>
#include <conio.h>

#include "InfixExpression.cpp"
#include "PrefixExpression.cpp"
#include "PostfixExpression.cpp"

using namespace std;

/*
class  StackExpression<...>  is the Implemented template class for converting the Stack Expressions in between  Infix, Prefix, Postfix  notations. And this class can't be inherited furthur to any other classes.

- < InFix >   : for selecting Infix Expression and it's functionalities
- < PreFix >  : for selecting Prefix Expression and it's functionalities
- < PostFix > : for selecting Postfix Expression and it's functionalities

< OtherTypes > : built-in datatypes or any other types are not allowed as an template arguement for this class, only the above mentioned three are allowed as a template arguement for this class
*/
template <typename ExpType>
class StackExpression final { // as final therefore can't inherited
  
  private : 
  
  char exp_type;
  char *exp;
  friend void operator<<(ostream &, StackExpression<InFix> &);
  
  public : 
  
  StackExpression();
  virtual ~StackExpression();
  
  void input(const char *);
  void input(string &);
  void input(istream &);
  
  const char* getInfixNotation();
  const char* getPrefixNotation();
  const char* getPostfixNotation();
};


template <typename ExpType>
StackExpression<ExpType> :: StackExpression(){
  
  try { // cross check the user provided type
    if (typeid(ExpType) == typeid(InFix)){ exp_type = 'I'; }
    else if (typeid(ExpType) == typeid(PreFix)){ exp_type = 'P'; }
    else if (typeid(ExpType) == typeid(PostFix)){ exp_type = 'O'; }
    else { throw "\n\t TypeError : built-in types and pre-defined types or any other types are not allowed "; }
  }
  catch(const char err_msz[]){
    exp = nullptr;
    exp_type = '\0';
    printf("%s", err_msz);
    return;
  }
  exp = new char[100]();
}

template <typename ExpType>
StackExpression<ExpType> :: ~StackExpression(){
  exp_type = '\0';
  delete exp;  exp = nullptr;
}


// this function reads an expression as input from the user
template <typename ExpType>
void StackExpression<ExpType> :: input(const char *ip_exp){
  
  if (exp == nullptr || exp_type == '\0'){
    printf("\n\t LogicalError : object was not intialized with a proper Stack Expression type ");
    return;
  }
}


// this function reads an expression as input from the user
template <typename ExpType>
void StackExpression<ExpType> :: input(string &ip_exp){
  
  if (exp == nullptr || exp_type == '\0'){
    printf("\n\t LogicalError : object was not intialized with a proper Stack Expression type ");
    return;
  }
}


// this function accepts a input stream and takes input from the user in console screen 
template <typename ExpType>
void StackExpression<ExpType> :: input(istream &ist){
  
  if (exp == nullptr || exp_type == '\0'){
    printf("\n\t LogicalError : object was not intialized with a proper Stack Expression type ");
    return;
  }
  
}


void operator<<(ostream &ost, StackExpression<InFix> &exp){
  short int exp_len = static_cast<string>(exp.exp).size();
  for (short int i = 0 ; i < exp_len; ++i){
    ost << exp.exp[i];
  }
}


int main(){
  char *a = new char[20]();
  
  InFix obj;  obj.input("A / B + C + F  - D");
  cout <<endl<< obj.getInputExp();
  
  // if (a == nullptr) cout <<endl<<"a = nullptr";
  // if (*a == '\0') cout <<endl<<"a = 0";
  
  getch();  return 0;
}
