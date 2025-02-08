/**
 * @brief 
 * 
 * This @file [ NumberSystem.C++ ] contains the definations of 
 * all functions mentioned in the @c ++header @file [ NumberSystem.h++ ] 
 * 
*/


#ifndef  _NUMBERSYSTEM_CPP_
#define  _NUMBERSYSTEM_CPP_


#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <cmath>
#include <conio.h>
#include "NumberSystem.h++"

using namespace std;


NumSys_:: NumSys_(){
  num_type = '\0';
  num = new char[200]();
  res_num = new char[100]();
  // cout <<"\n ctor : NumSys_ \n";
}
NumSys_:: ~NumSys_(){
  delete []num;  num = nullptr;
  delete []res_num;  res_num = nullptr;
  // cout <<"\n des : NumSys_ \n"; 
}


void NumSys_:: validateBinaryInput(){
  bool valid_input_provided = false;
  // this loop will continue until user provides a valid input
  while (valid_input_provided != true){
    
    char *ip_num = new char[50]();  
    cout <<"\n\n Enter the Binary Number : ";
    cin.getline(ip_num, 50);
    
    // Exception Handling (only 0's and 1's are allowed) 
    try {
      short int count_dots = 0;
      short int ip_num_len = static_cast<string>(ip_num).size();
      
      for (short int  i = 0; i < ip_num_len; ++i){
        
        switch (ip_num[i]){
          case '0' : break;
          case '1' : break;
          case '.' : ++count_dots;  break;
          case ' ' : throw  ' ';
          default : throw  "including other things in Binary no.";
        }
      }
      if (count_dots > 1 || ip_num[0] == '.' || ip_num[ip_num_len-1] == '.'){ throw  0; }
    }
    catch(int){
      cout <<"\n Not a valid Expression !\n Dot placing is Invalid. ";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(char){
      cout <<"\n Spaces can't be included !";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(...){
      cout <<"\n Binary Numbers[0's and 1's] are only allowed !\n Please enter a appropriate Binary Number.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    // Exception Handling Over
    
    valid_input_provided = true;
    strcpy(num, ip_num);  num_type = 'B';
    delete []ip_num;  ip_num = nullptr;
  }
}


void NumSys_:: validateOctalInput(){
  bool valid_input_provided = false;
  // this loop will continue until a valid input provided
  while (valid_input_provided != true){
    
    char *ip_num = new char[50]();  
    cout <<"\n\n Enter the Octal Number : ";
    cin.getline(ip_num, 50);
    
    // Exception Handling (only Numbers are allowed [0 - 9]) 
    try {
      short int count_dots = 0;
      short int ip_num_len = static_cast<string>(ip_num).size();
      
      for (short int  i = 0; i < ip_num_len; ++i){
        
        switch (ip_num[i]){
          case '0' : break;  case '1' : break;
          case '2' : break;  case '3' : break;
          case '4' : break;  case '5' : break;
          case '6' : break;  case '7' : break;
          case '.' : ++count_dots;  break;
          case ' ' : throw  ' ';
          default : throw  "including other things in Octal no.";
        }
      }
      if (count_dots > 1 || ip_num[0] == '.' || ip_num[ip_num_len-1] == '.'){ throw  0; }
    }
    catch(int){
      cout <<"\n Not a valid Expression !\n Dot placing is Invalid.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(char){
      cout <<"\n Spaces can't be included !";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(...){
      cout <<"\n Numbers[ between 0 - 7 ] are only allowed !\n Please enter a appropriate Ocatl Number.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    // Exception Handling Over 
    
    valid_input_provided = true;
    strcpy(num, ip_num);  num_type = 'O';
    delete []ip_num;  ip_num = nullptr;
  }
}


void NumSys_:: validateDecimalInput(){
  bool valid_input_provided = false;
  // this loop will continue until a valid input provided
  while (valid_input_provided != true){
    
    char *ip_num = new char[50]();  
    cout <<"\n\n Enter the Decimal Number : ";
    cin.getline(ip_num, 50);
    
    // Exception Handling (only Numbers are allowed [0 - 9]) 
    try {
      short int count_dots = 0;
      short int ip_num_len = static_cast<string>(ip_num).size();
      
      for (short int  i = 0; i < ip_num_len; ++i){
        
        switch (ip_num[i]){
          case '0' : break;  
          case '1' : break;  case '2' : break;  case '3' : break;
          case '4' : break;  case '5' : break;  case '6' : break;
          case '7' : break;  case '8' : break;  case '9' : break;
          case '.' : ++count_dots;  break;
          case ' ' : throw  ' ';
          default : throw  "including other things in Decimal no.";
        }
      }
      if (count_dots > 1 || ip_num[0] == '.' || ip_num[ip_num_len-1] == '.'){ throw  0; }
    }
    catch(int){
      cout <<"\n Not a valid Expression !\n Dot placing is Invalid.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(char){
      cout <<"\n Spaces can't be included !";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(...){
      cout <<"\n Numbers are only allowed !\n Please enter a appropriate Number.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    // Exception Handling Over 
    
    valid_input_provided = true;
    strcpy(num, ip_num);  num_type = 'D';
    delete []ip_num;  ip_num = nullptr;
  }
}


void NumSys_:: validateHexaDecimalInput(){
  bool valid_input_provided = false;
  // this loop will continue until a valid input provided
  while (valid_input_provided != true){
    
    char *ip_num = new char[50]();  
    cout <<"\n\n Enter the HexaDecimal Number : ";
    cin.getline(ip_num, 50);
    
    // Exception Handling (only Numbers[0 - 9] & letters[a - f] are allowed) 
    try {
      short int count_dots = 0;
      short int ip_num_len = static_cast<string>(ip_num).size();
      
      for (short int  i = 0; i < ip_num_len; ++i){
        
        switch (ip_num[i]){
          case '0' : break;  
          case '1' : break;  case '2' : break;  case '3' : break;
          case '4' : break;  case '5' : break;  case '6' : break;
          case '7' : break;  case '8' : break;  case '9' : break;
          case 'a' : break;  case 'A' : break;
          case 'b' : break;  case 'B' : break;
          case 'c' : break;  case 'C' : break;
          case 'd' : break;  case 'D' : break;
          case 'e' : break;  case 'E' : break;
          case 'f' : break;  case 'F' : break;
          case '.' : ++count_dots;  break;
          case ' ' : throw  ' ';
          default : throw  "including other things in HexaDecimal no.";
        }
      }
      if (count_dots > 1 || ip_num[0] == '.' || ip_num[ip_num_len-1] == '.'){ throw  0; }
    }
    catch(int){
      cout <<"\n Not a valid Expression !\n Dot placing is Invalid.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(char){
      cout <<"\n Spaces can't be included !";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    catch(...){
      cout <<"\n Numbers[ between 0 - 9 ] and letters[ between A - F ] are only allowed !\n Please enter a appropriate Hexa Decimal Number.";
      delete []ip_num;  ip_num = nullptr;
      continue;
    }
    // Exception Handling Over 
    
    valid_input_provided = true;
    strcpy(num, ip_num);  num_type = 'H';
    delete []ip_num;  ip_num = nullptr;
  }
}


void NumSys_:: input(){
  cout <<"\n Press ... ";
  cout <<"\n {B} To enter a Binary value ";
  cout <<"\n {O} To enter a Octal value ";
  cout <<"\n {D} To enter a Decimal value ";
  cout <<"\n {H} To enter a HexaDecimal value ";
  cout <<"\n ->  Enter :  ";
  switch (getche()){
    case 'R' : cout <<endl;  break;
    case 'r' : cout <<endl;  break;
    case 'B' : validateBinaryInput();  break;
    case 'b' : validateBinaryInput();  break;
    case 'O' : validateOctalInput();  break;
    case 'o' : validateOctalInput();  break;
    case 'D' : validateDecimalInput();  break;
    case 'd' : validateDecimalInput();  break;
    case 'H' : validateHexaDecimalInput();  break;
    case 'h' : validateHexaDecimalInput();  break;
    default  : cout <<"\n\n Invalid Choise !\n Please Choose a right Option.\n";
  }
}


/**
*@p     CONVERTINGㅤLOGICSㅤOFㅤ[_OTHER'Sㅤ->ㅤBINARY_]
*/


const char* NumSys_:: convertOctalToBinary(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[150]();
  
  short int num_len = static_cast<string>(num).size();
  for (short int  i = 0, _x_ = 0; _x_ < num_len; ++_x_){
    
    switch (num[_x_]){
      case '.' : res_num[i] = '.';  ++i;  break;
      case '0' : //  0 - 000
        res_num[i] = '0';  ++i;
        res_num[i] = '0';  ++i;
        res_num[i] = '0';  ++i;
      break;
      case '1' : //  1 - 001
        res_num[i] = '0';  ++i;
        res_num[i] = '0';  ++i;
        res_num[i] = '1';  ++i;
      break;
      case '2' : //  2 - 010
        res_num[i] = '0';  ++i;
        res_num[i] = '1';  ++i;
        res_num[i] = '0';  ++i;
      break;
      case '3' : //  3 - 011
        res_num[i] = '0';  ++i;
        res_num[i] = '1';  ++i;
        res_num[i] = '1';  ++i;
      break;
      case '4' : //  4 - 100
        res_num[i] = '1';  ++i;
        res_num[i] = '0';  ++i;
        res_num[i] = '0';  ++i;
      break;
      case '5' : //  5 - 101
        res_num[i] = '1';  ++i;
        res_num[i] = '0';  ++i;
        res_num[i] = '1';  ++i;
      break;
      case '6' : //  6 - 110
        res_num[i] = '1';  ++i;
        res_num[i] = '1';  ++i;
        res_num[i] = '0';  ++i;
      break;
      case '7' : //  7 - 111
        res_num[i] = '1';  ++i;
        res_num[i] = '1';  ++i;
        res_num[i] = '1';  ++i;
      break;
      default : break;
    }
  }
  return  res_num;
}


const char* NumSys_:: convertDecimalToBinary(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[100]();
  
  // check if the number is a floting point value or not
  bool point_value = false;
  short int num_len = static_cast<string>(num).size();
  for (short int  i = 0; i < num_len; ++i){
    if (num[i] == '.'){ point_value = true; }
  }
  // two different calculation methods
  
  // if the value is not a point value then no need to do the complicated calculation
  if (point_value == false){
    unsigned long long int *the_num = new unsigned long long int(0);
    
    // "stoull()" built-in function to convert str to unsigned long long
    *the_num = stoull(num);
    // declare a stack to store result & retrive the reault in reverse format
    stack<bool> *stk = new stack<bool>();
    while (*the_num > 0){
      // push the remainders
      stk->push(*the_num % 2);
      *the_num /= 2;
    }
    //  put the result into the res_num
    for (short int  i = 0; stk->empty() != true; ++i, stk->pop()){
      // convert the int to char then put
      res_num[i] = (stk->top() + '0');
    }
    delete the_num;  the_num = nullptr;
    delete stk;  stk = nullptr;
    
    // if the control not enter in the loop means [num = 0] then,
    if (static_cast<string>(res_num).empty() == true){ res_num[0] = '0'; }
    
    return  res_num;
  }
  
  
  /** @c elsePartㅤ:ㅤif-the-value-is-a-point-value-then,  */
  unsigned long int *bef_p_num = new unsigned long int(0);
  unsigned long long int *whole_num = new unsigned long long int(0);
  
  // "stold()" built-in function to convert str to long double
  // and long double to int implicitly converted
  *bef_p_num = stold(num);
  // multiply with 2^10 to avoid calculation of point part explicitly
  // and the more power increased the more it contains Binary numbers
  *whole_num = stold(num) * pow(2, 10);
  
  stack<bool> *stk_1 = new stack<bool>();
  // a stack to store the first half result(before point part)
  while (*bef_p_num > 0){
    // push the remainders into stack
    stk_1->push(*bef_p_num % 2);
    *bef_p_num /= 2;
  }
  
  stack<bool> *stk_2 = new stack<bool>();
  // another stack to hold the whole result(incl. point part)
  while (*whole_num > 0){
    // push the remainders into stack
    stk_2->push(*whole_num % 2);
    *whole_num /= 2;
  }
  // comapring and storing the result in [ res_num ]
  for (short int  i = 0; stk_2->empty() != true; ++i){
    
    // after first part put the '.' into it's pos
    if (i == stk_1->size()){
      res_num[i] = '.';
    }
    else {
      // convert the int into char and put 
      res_num[i] = (stk_2->top() + '0');
      stk_2->pop();
    }
  }
  delete bef_p_num;  bef_p_num = nullptr;
  delete whole_num;  whole_num = nullptr;
  delete stk_1;  stk_1 = nullptr;
  delete stk_2;  stk_2 = nullptr;
  
  // if the control not enter in the loop means [num = 0.0] then,
  if (static_cast<string>(res_num).empty() == true){ 
    res_num[0] = '0'; 
    res_num[1] = '.'; 
    res_num[2] = '0'; 
  }
  return  res_num;
}


const char* NumSys_:: convertHexaDecimalToBinary(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[200]();
  
  short int num_len = static_cast<string>(num).size();
  for (short int  i = 0, k = 0; k < num_len; ++k){
    
    if (num[k] == '.'){ res_num[i] = '.';  ++i; }
    else if (num[k] == '0'){ // 0 - 0000
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == '1'){ // 1 - 0001
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == '2'){ // 2 - 0010
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == '3'){ // 3 - 0011
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == '4'){ // 4 - 0100
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == '5'){ // 5 - 0101
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == '6'){ // 6 - 0110
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == '7'){ // 7 - 0111
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == '8'){ // 8 - 1000
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == '9'){ // 9 - 1001
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
    } 
    else if (num[k] == 'A' || num[k] == 'a'){ // 10_A - 1010 
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
    } 
    else if (num[k] == 'B' || num[k] == 'b'){ // 11_B - 1011
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == 'C' || num[k] == 'c'){ // 12_C - 1100
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == 'D' || num[k] == 'd'){ // 13_D - 1101
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
      res_num[i] = '1';  ++i;
    }
    else if (num[k] == 'E' || num[k] == 'e'){ // 14_E - 1110
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '0';  ++i;
    }
    else if (num[k] == 'F' || num[k] == 'f'){ // 15_F - 1111
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
      res_num[i] = '1';  ++i;
    }
    else { break; }
  }
  return  res_num;
}



/**
*@p     CONVERTINGㅤLOGICSㅤOFㅤ[_OTHER'Sㅤ->ㅤDECIMAL_]
*/


const char* NumSys_:: convertBinaryToDecimal(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[50]();
  
  short int num_len = static_cast<string>(num).size();
  short int point_index = 0;
  
  // finding the point postion
  for (short int i = 0; i < num_len; ++i){
    if (num[i] == '.'){ point_index = i; }
  }
  // now if the point doesn't exist then, set the length value to it,
  // so it will work like num_len for non-point numbers
  if (point_index == 0){ point_index = num_len; }
  
  long double *sum_of_num = new long double(0.0);
  for (short int  i = 0, k = point_index - 1; i < num_len; ++i, --k){
    
    // skipping the dot value
    if (num[i] == '.'){ 
      // it is done bcoz in the flow of iteration,
      // the k will increment for '.' also, so ++k & --k = k 
      ++k;  continue; 
    }
    // only calculate 1's no need to calculate 0's 
    if (num[i] == '1'){
      *sum_of_num = *sum_of_num + (1 * pow(2, k));
    }
  }
  // convert the res into str then copy it to the [ res_num ]
  strcpy(res_num, to_string(*sum_of_num).c_str());
  
  delete sum_of_num;  sum_of_num = nullptr;
  return  res_num;
}


const char* NumSys_:: convertOctalToDecimal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to Decimal in next step
  strcpy(num, convertOctalToBinary());
  
  // now converting the num into Decimal and,
  // the converted number automatically stored into res_num
  convertBinaryToDecimal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


const char* NumSys_:: convertHexaDecimalToDecimal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to decimal in next step
  strcpy(num, convertHexaDecimalToBinary());
  
  // now converting the num into Decimal and,
  // the converted number automatically stored into res_num
  convertBinaryToDecimal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


/**
*@p     CONVERTINGㅤLOGICSㅤOFㅤ[_OTHER'Sㅤ->ㅤOCTAL_]
*/


const char* NumSys_:: convertBinaryToOctal(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[50]();
  
  // a local nested function under a class block to operate on different values
  // this block also provides the reusability of code by the function
  class func {  func();  ~func();  public :
    static bool putValuesIntoResult(char &fval, char &sval, char &tval, char *res_num, short int &res_i){
      
      if (fval == '0' && sval == '0' && tval == '0'){ 
        res_num[res_i] = '0';  ++res_i;
      }
      else if (fval == '0' && sval == '0' && tval == '1'){ 
        res_num[res_i] = '1';  ++res_i;
      }
      else if (fval == '0' && sval == '1' && tval == '0'){ 
        res_num[res_i] = '2';  ++res_i;
      }
      else if (fval == '0' && sval == '1' && tval == '1'){ 
        res_num[res_i] = '3';  ++res_i;
      }
      else if (fval == '1' && sval == '0' && tval == '0'){ 
        res_num[res_i] = '4';  ++res_i;
      }
      else if (fval == '1' && sval == '0' && tval == '1'){ 
        res_num[res_i] = '5';  ++res_i;
      }
      else if (fval == '1' && sval == '1' && tval == '0'){ 
        res_num[res_i] = '6';  ++res_i;
      }
      else if (fval == '1' && sval == '1' && tval == '1'){ 
        res_num[res_i] = '7';  ++res_i;
      }
      else {// it indicates that there is any wrong value occoured
        cout <<"\n Some Unknown error occoured !";
        return  false;
      }
      return  true;
    }
  };
  
  // declare three vars for pointing to three different values
  char  fval, sval, tval;   fval = sval = tval = '\0';
  short int num_len = static_cast<string>(num).size();
  short int  start_index = 0, point_index = 0, res_i = 0;
  
  // checking that the dot-point is exist or not,
  for (short int i = 0; i < num_len; ++i){
    if (num[i] == '.'){ point_index = i; }
  }
  // and if not exist then set the length of the num to it
  // so that we can use it in for both normal & floting num
  if (point_index == 0){ point_index = num_len; }
  
  if (point_index % 3 == 1){
    // it means user input can't be grouped as 3 upto dot-point
    // and first two values should be '0'
    fval = sval = '0';  tval = num[0]; 
    start_index = 1;
  }
  else if (point_index % 3 == 2){ 
    // it means user input can't be grouped as 3 upto dot-point 
    // and first one value should be '0'
    fval = '0';  sval = num[0];  tval = num[1];
    start_index = 2;
  }
  else {
    // it mean [num_upto_point % 3 == 0], 
    // therefore num can be grouped as 3 upto dot-point 
    fval = num[0];  sval = num[1];  tval = num[2]; 
    start_index = 3;
  }
  
  // calculate the 1st part and put the ans's into res_num
  for (short int i = start_index; i <= point_index; i += 3){
    
    if (func::putValuesIntoResult(fval, sval, tval, res_num, res_i)){ 
      // if returns true then do nothing
    } else { return  (const char*)"\0"; }
    
    // set the values for the next iteration
    fval = num[i];  sval = num[i + 1];  tval = num[i + 2];
  }
  
  // putting the dot-point after calculation of 1st part,
  // if user provided number is a dot-point number  
  if (point_index != num_len){ res_num[res_i] = '.';  ++res_i; }
  // re-setting the vars for calculate 2nd part
  fval = sval = tval = '\0';
  
  // calculate the 2nd part and put the ans's into same res_num
  for (short int i = point_index + 1; i < num_len; i += 3){
    
    // set values to the vars 
    fval = num[i];  sval = num[i + 1];  tval = num[i + 2];
    // validate the out of range values,
    // bcoz in last iteration may be the  2nd,3rd  val goes out of range
    if (sval != '0' && sval != '1'){ sval = '0'; }
    if (tval != '0' && tval != '1'){ tval = '0'; }
    
    if (func::putValuesIntoResult(fval, sval, tval, res_num, res_i)){
      // if returns true then do nothing
    } else { return  (const char*)"\0"; }  
  }
  
  return  res_num;
}


const char* NumSys_:: convertDecimalToOctal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to Ocatl in next step
  strcpy(num, convertDecimalToBinary());
  
  // now converting the num into Octal and,
  // the converted number automaticaly stored into res_num
  convertBinaryToOctal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


const char* NumSys_:: convertHexaDecimalToOctal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to Ocatl in next step
  strcpy(num, convertHexaDecimalToBinary());
  
  // now convert thinge num into Octal and,
  // the converted number automatically stored into res_num
  convertBinaryToOctal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


/**
*@p     CONVERTINGㅤLOGICSㅤOFㅤ[_OTHER'Sㅤ->ㅤHEXA-DECIMAL_]
*/


const char* NumSys_:: convertBinaryToHexaDecimal(){
  // Allocate fresh memory for the Result
  delete []res_num;  res_num = nullptr;
  res_num = new char[50]();
  
  // a local nested function under a class block to operate on different values
  // this block also provides the reusability of code by the function
  class func {  func();  ~func();  public :
    static bool putValuesIntoResult(char &v1, char &v2, char &v3, char &v4, char *res_num, short int &res_i){
      
      if (v1 == '0' && v2 == '0' && v3 == '0' && v4 == '0'){ 
        res_num[res_i] = '0';  ++res_i;
      }
      else if (v1 == '0' && v2 == '0' && v3 == '0' && v4 == '1'){ 
        res_num[res_i] = '1';  ++res_i;
      }
      else if (v1 == '0' && v2 == '0' && v3 == '1' && v4 == '0'){ 
        res_num[res_i] = '2';  ++res_i;
      }
      else if (v1 == '0' && v2 == '0' && v3 == '1' && v4 == '1'){ 
        res_num[res_i] = '3';  ++res_i;
      }
      else if (v1 == '0' && v2 == '1' && v3 == '0' && v4 == '0'){ 
        res_num[res_i] = '4';  ++res_i;
      }
      else if (v1 == '0' && v2 == '1' && v3 == '0' && v4 == '1'){ 
        res_num[res_i] = '5';  ++res_i;
      }
      else if (v1 == '0' && v2 == '1' && v3 == '1' && v4 == '0'){ 
        res_num[res_i] = '6';  ++res_i;
      }
      else if (v1 == '0' && v2 == '1' && v3 == '1' && v4 == '1'){ 
        res_num[res_i] = '7';  ++res_i;
      }
      else if (v1 == '1' && v2 == '0' && v3 == '0' && v4 == '0'){ 
        res_num[res_i] = '8';  ++res_i;
      }
      else if (v1 == '1' && v2 == '0' && v3 == '0' && v4 == '1'){ 
        res_num[res_i] = '9';  ++res_i;
      }
      else if (v1 == '1' && v2 == '0' && v3 == '1' && v4 == '0'){ 
        res_num[res_i] = 'A';  ++res_i;
      }
      else if (v1 == '1' && v2 == '0' && v3 == '1' && v4 == '1'){ 
        res_num[res_i] = 'B';  ++res_i;
      }
      else if (v1 == '1' && v2 == '1' && v3 == '0' && v4 == '0'){ 
        res_num[res_i] = 'C';  ++res_i;
      }
      else if (v1 == '1' && v2 == '1' && v3 == '0' && v4 == '1'){ 
        res_num[res_i] = 'D';  ++res_i;
      }
      else if (v1 == '1' && v2 == '1' && v3 == '1' && v4 == '0'){ 
        res_num[res_i] = 'E';  ++res_i;
      }
      else if (v1 == '1' && v2 == '1' && v3 == '1' && v4 == '1'){ 
        res_num[res_i] = 'F';  ++res_i;
      }
      else {// it indicates that there is any wrong value occoured
        cout <<"\n Some Unknown error occoured !";
        return  false;
      }
      return  true;
    }
  };
  
  // declare four vars for pointing to four different values
  char  val1 = '\0', val2 = '\0', val3 = '\0', val4 = '\0';
  short int num_len = static_cast<string>(num).size();
  short int  start_index = 0, point_index = 0, res_i = 0;
  
  // checking that the dot-point is exist or not,
  for (short int i = 0; i < num_len; ++i){
    if (num[i] == '.'){ point_index = i; }
  }
  // and if not exist then set the length of the num to it
  // so that we can use it in for both normal & floating num
  if (point_index == 0){ point_index = num_len; }
  
  if (point_index % 4 == 1){
    // it means user input can't be grouped as 4 upto dot-point
    // and first three values should be '0'
    val1 = val2 = val3 = '0';  val4 = num[0]; 
    start_index = 1;
  }
  else if (point_index % 4 == 2){ 
    // it means user input can't be grouped as 4 upto dot-point 
    // and first two value should be '0'
    val1 = val2 = '0';  val3 = num[0];  val4 = num[1];
    start_index = 2;
  }
  else if (point_index % 4 == 3){ 
    // it means user input can't be grouped as 4 upto dot-point 
    // and first one value should be '0'
    val1 = '0';  val2 = num[0];  val3 = num[1];  val4 = num[2];
    start_index = 3;
  }
  else {
    // it mean [num_upto_point % 4 == 0], 
    // therefore num can be grouped as 4 upto dot-point 
    val1 = num[0];  val2 = num[1];  val3 = num[2];  val4 = num[3];
    start_index = 4;
  }
  
  // calculate the 1st part and put the ans's into res_num
  for (short int i = start_index; i <= point_index; i += 4){
    
    if (func::putValuesIntoResult(val1, val2, val3, val4, res_num, res_i)){ 
      // if returns true then do nothing
    } else { return  (const char*)"\0"; }
    
    // set the values for the next iteration
    val1 = num[i];  val2 = num[i + 1];  
    val3 = num[i + 2];  val4 = num[i + 3];
  }
  
  // putting the dot-point after calculation of 1st part,
  // if user provided number is a dot-point number  
  if (point_index != num_len){ res_num[res_i] = '.';  ++res_i; }
  // re-setting the vars for calculate 2nd part
  val1 = val2 = val3 = val4 = '\0';
  
  // calculate the 2nd part and put the ans's into same res_num
  for (short int i = point_index + 1; i < num_len; i += 4){
    
    // set values to the vars 
    val1 = num[i];  val2 = num[i + 1];  
    val3 = num[i + 2];  val4 = num[i + 3];
    // validate the out of range values,
    // bcoz in last iteration may be the  2nd,3rd,4th  val goes out of range
    if (val2 != '0' && val2 != '1'){ val2 = '0'; }
    if (val3 != '0' && val3 != '1'){ val3 = '0'; }
    if (val4 != '0' && val4 != '1'){ val4 = '0'; }
    
    if (func::putValuesIntoResult(val1, val2, val3, val4, res_num, res_i)){
      // if returns true then do nothing
    } else { return  (const char*)"\0"; }  
  }
  
  return  res_num;
}


const char* NumSys_:: convertOctalToHexaDecimal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to HexaDecimal in next step
  strcpy(num, convertOctalToBinary());
  
  // now converting the num into HexaDecimal and,
  // converted number automatically stored into res_num
  convertBinaryToHexaDecimal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


const char* NumSys_:: convertDecimalToHexaDecimal(){
  
  // store the initial input number of user
  const char *initial_num = new char[50]();
  strcpy(const_cast<char*>(initial_num), num);
  
  // modify the user input number temporary by re-writing
  // for calculate Binary to HexaDecimal in next step
  strcpy(num, convertDecimalToBinary());
  
  // now converting the num into HexaDecimal and,
  // converted number automatically stored into res_num
  convertBinaryToHexaDecimal();
  
  // re-assign the user input to num
  strcpy(num, initial_num);
  
  delete []initial_num;  initial_num = nullptr;
  return  res_num;
}


/**
*@b     PUBLICㅤFUNCTION'sㅤDEFINATION's
*/


const char* NumSys_:: getBinary(){
  // if there doesn't input taken by user 
  if (static_cast<string>(num).empty() || num_type == '\0'){
    cout <<"\n Please take a input first !";
    return  (const char*)"\0";
  }
  if (num_type == 'B'){
    // if the Number input taken from user,
    // is already Binary then,
    return  num;
  }
  if (num_type == 'O'){
    return  convertOctalToBinary();
  }
  if (num_type == 'D'){ 
    return  convertDecimalToBinary();
  }
  if (num_type == 'H'){
    return  convertHexaDecimalToBinary();
  } 
}


const char* NumSys_:: getOctal(){
  // if there doesn't input taken by user 
  if (static_cast<string>(num).empty() || num_type == '\0'){
    cout <<"\n Please take a input first !";
    return  (const char*)"\0";
  }
  if (num_type == 'B'){
    return  convertBinaryToOctal();
  }
  if (num_type == 'O'){
    // if the number taken as user input,
    // is alrady Octal then,
    return  num;
  }
  if (num_type == 'D'){
    return  convertDecimalToOctal();
  }
  if (num_type == 'H'){
    return  convertHexaDecimalToOctal();
  }
}


const char* NumSys_:: getDecimal(){
  // if there doesn't input taken by user 
  if (static_cast<string>(num).empty() || num_type == '\0'){
    cout <<"\n Please take a input first !";
    return  (const char*)"\0";
  }
  if (num_type == 'B'){
    return  convertBinaryToDecimal();
  }
  if (num_type == 'O'){
    return  convertOctalToDecimal();
  }
  if (num_type == 'D'){
    // if the number taken as user input,
    // is alrady Decimal then,
    return  num;
  }
  if (num_type == 'H'){
    return  convertHexaDecimalToDecimal();
  }
}


const char* NumSys_:: getHexaDecimal(){
  // if there doesn't input taken by user 
  if (static_cast<string>(num).empty() || num_type == '\0'){
    cout <<"\n Please take a input first !";
    return  (const char*)"\0";
  }
  if (num_type == 'B'){
    return  convertBinaryToHexaDecimal();
  }
  if (num_type == 'O'){
    return  convertOctalToHexaDecimal();
  }
  if (num_type == 'D'){ 
    return  convertDecimalToHexaDecimal();
  }
  if (num_type == 'H'){
    // if the Number input taken from user,
    // is already Binary then,
    return  num;
  } 
}


#endif /* _NUMBERSYSTEM_CPP_ */
