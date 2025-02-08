/**
 * @brief 
 * 
 * @a CODEㅤTHROUGHㅤC++ㅤFORㅤIMPLEMENTINGㅤTHEㅤNUMBERㅤSYSTEMㅤAPPLICATION.
 * This is a program which not only can be used by the user's,
 * but also programmers can use this by inheriting the class.
 * Therefore by including the @file  [ #include "NumberSystem.h++" ],
 * programmer's can create obj's of class NumberSystem and, 
 * can use the functionalities like a converter.
 * 
 * 
 * In this @file [ NumSystem.h++ ] the declarations are only here and the
 * definations are provided into another @file [ NumberSystem.C++ ] 
 * But there is no nedd to add the "cpp" file in programms ,
 * but it should have to be mentioned during compilation .
 * 
*/


#ifndef  _NUMBERSYSTEM_H_
#define  _NUMBERSYSTEM_H_

// class NumSys_ final { // to prevent inheriting
class NumSys_ {
  
  private :
  
  char *num;
  char num_type;
  char *res_num;
  
  // func's for validate the inputs
  
  void validateBinaryInput();
  void validateOctalInput();
  void validateDecimalInput();
  void validateHexaDecimalInput();
  
  // func's for converting 
  
  const char* convertOctalToBinary();
  const char* convertDecimalToBinary();
  const char* convertHexaDecimalToBinary();
  
  const char* convertBinaryToDecimal();
  const char* convertOctalToDecimal();
  const char* convertHexaDecimalToDecimal();
  
  const char* convertBinaryToOctal();
  const char* convertDecimalToOctal();
  const char* convertHexaDecimalToOctal();
  
  const char* convertBinaryToHexaDecimal();
  const char* convertOctalToHexaDecimal();
  const char* convertDecimalToHexaDecimal();
  
  public :  
  
  NumSys_();          // constructor
  virtual ~NumSys_(); // destructor
  
  // public functions
  
  // A pre-defined function to take input and as well as validate the input, which was provided through console and return void(nothing)
  virtual void input();
  // A pre-defined function which returns the equivalent Binary value of the given input value, in the form of character_array(char [])
  virtual const char* getBinary();
  // A pre-defined function which returns the equivalent Octal value of the given input value, in the form of character_array(char [])
  virtual const char* getOctal();
  // A pre-defined function which returns the equivalent Decimal value of the given input value, in the form of character_array(char [])
  virtual const char* getDecimal();
  // A pre-defined function which returns the equivalent HexaDecimal value of the given input value, in the form of character_array(char [])
  virtual const char* getHexaDecimal();
  
};


/**  changing the @class @name according to @file @name  */

/*  Implemented Class for performing conversion between Number Systems  */
typedef  NumSys_  NumberSystem;


#endif  /*  _NUMBERSYSTEM_H_  */