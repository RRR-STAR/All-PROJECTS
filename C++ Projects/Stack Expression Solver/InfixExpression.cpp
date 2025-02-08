/**
 * @brief @details
 *  
 *
*/

#ifndef  _INFIXEXPRESSION_H_
#define  _INFIXEXPRESSION_H_


#include <string>
#include <istream>
using namespace std;


class InFix {
  
  private : 
  
  char *res_exp;
  const char *exp;
  bool exp_validation;
  
  void convertToPostfix(const short int &, const char *, char *);
  const bool validateInputExp(const string &);
  
  public : 
  
  InFix();
  virtual ~InFix();
  
  void input(const char *);
  void input(istream &);
  void input(string &);
  
  void showInputExp();
  const char* getInputExp();
  
  void showPrefixExp();
  const char* getPrefixExp();
  
  void showPostfixExp();
  const char* getPostfixExp();
};


InFix :: InFix(){
  exp = new char[100]();
  res_exp = new char[100]();
  exp_validation = false;
}
InFix :: ~InFix(){
  delete []exp;  exp = nullptr;
  delete []res_exp;  res_exp = nullptr;
  exp_validation = NULL;
}


// validate the given expression according to Infix Expression
const bool InFix :: validateInputExp(const string &ip_exp){
  
  short int exp_len = ip_exp.size();
  short int  st_bracket_count = 0, end_bracket_count = 0, operator_count = 0, operand_count = 0;
  bool  st_bracket_occur = false, end_bracket_occur = false, operator_occur = false, num_operand_occur = false, alph_operand_occur = false;
  try {
    for (short int i = 0 ; i < exp_len; ++i){
      
      switch (ip_exp[i]){
        // (spaces, paranthisis, operators, digits, alphabets) are allowed only
        case '(' : break;  case ')' : break;
        case ' ' : break;  case '$' : break;
        case '^' : break;  case '/' : break;
        case '%' : break;  case '*' : break;  
        case '+' : break;  case '-' : break;
        
        default :// for any other character except alphabets & digits, it fetch exception
        if (isalpha(ip_exp[i]) && islower(ip_exp[i])){ 
          throw "\n ExpressionError : lower case letters are not allowed as operands "; 
        } 
        else if (isalpha(ip_exp[i]) || isdigit(ip_exp[i])){/*alphabets & digits are allowed */}
        else { throw "\n ExpressionError : contain invaild symbols "; }
      }
      /*
      if any exception was not raised from the switch block it means currently selected characters is syntatically correct, and now logically checking...
      conditions which are "not allowed" logically -> 
      -
      -  1.  start bracket    | operator         ->  '(+' or '(%'
      -  2.  operator         | operator         ->  '++' or '-/'
      -  3.  operator         | end bracket      ->  '-)' or '*)'
      -  4.  alphabet operand | alphabet operand ->  'AA' or 'Az'
      -  5.  alphabet operand | number operand   ->  'A99' or 'a2'
      -  6.  number operand   | alphabet operand ->  '108m' or '3X'
      -  7.  alphabet operand | start bracket    ->  'A(' or 'a('
      -  8.  number operand   | start bracket    ->  '1(' or '325('
      -  9.  end bracket      | alphabet operand ->  ')c' or ')D'
      -  10. end bracket      | number operand   ->  ')2' or ')324'
      -  11. end bracket      | start bracket    ->  ')('
      */
      if (ip_exp[i] == ' '){/* do-nothing when found space */}
      
      // start bracket only be placed after any operator or at begning
      else if (ip_exp[i] == '('){
        
        // if start brackets placed after any operand or end bracket, then
        if (num_operand_occur == true || alph_operand_occur == true || end_bracket_occur == true){ 
          throw "\n ExpressionError : opening bracket error, expected to be an operator before opening bracket "; 
        }
        st_bracket_occur = true;  ++st_bracket_count;
        
        // reset other flags
        end_bracket_occur = false;
        operator_occur = false;
        num_operand_occur = false;
        alph_operand_occur = false;
      }
      // end bracket only be placed after any operand
      else if (ip_exp[i] == ')'){
        
        // if end brackets placed after any operator, then
        if (operator_occur == true){
          throw "\n ExpressionError : closing bracket error, expected to be an operand before closing bracket ";
        }
        end_bracket_occur = true;  ++end_bracket_count;
        
        // reset other flags
        st_bracket_occur = false;
        operator_occur = false;
        num_operand_occur = false;
        alph_operand_occur = false;
      }
      // number operands are treated as constants
      // number operands can be placed after operator or start bracket or itselt
      else if (isdigit(ip_exp[i]) == true){
        
        // if number operand placed after any end bracket or alphabet operand
        if (alph_operand_occur == true || end_bracket_occur == true){
          throw "\n ExpressionError : constant error, expected to be an operator before constant ";
        }
        num_operand_occur = true;
        // if next char is not digit then multi-operand ends
        // and consider as a single constant operand
        if (not isdigit(ip_exp[i + 1])){ ++operand_count; }
        
        // reset other flags
        operator_occur = false;
        st_bracket_occur = false;
        end_bracket_occur = false;
        alph_operand_occur = false;
      }
      // alphabet operands can be placed after operator or start bracket
      else if (isalpha(ip_exp[i]) == true){
        
        // if alphabet operand placed after any end bracket or number operand or itselt
        if (alph_operand_occur == true || num_operand_occur == true || end_bracket_occur == true){
          throw "\n ExpressionError : operand error, expected to be an operator before operand ";
        }
        alph_operand_occur = true;  ++operand_count;
        
        // reset other flags
        operator_occur = false;
        st_bracket_occur = false;
        end_bracket_occur = false;
        num_operand_occur = false;
      }
      // operators can be placed between two operands or after & before of brackets
      else { /** @c elseㅤ:ㅤ_means_it_should_be_an_operator_ */
        
        // if operator placed after any operator or start bracket  
        if (operator_occur == true || st_bracket_occur == true){
          throw "\n ExpressionError : operator error, expected to be an operand before operator ";
        }
        operator_occur = true;  ++operator_count;
        
        // reset other flags 
        st_bracket_occur = false;
        end_bracket_occur = false;
        num_operand_occur = false;
        alph_operand_occur = false;
      }
    }
    // if brackets are not equal, means bracket open but not closed or close bracket without opening
    if (st_bracket_count != end_bracket_count){
      throw "\n ExpressionError : brackets are not closed properly ";
    }
    // if the exp doesn't conatin any operand
    if (operand_count == 0){
      throw "\n ExpressionError : doesn't found any operand in the expression ";
    }
    // if the operators and operands are not given properly 
    if (operand_count - 1 != operator_count){
      throw "\n ExpressionError : invalid infix expression ";
    }
  }
  catch (const char err_msz[]){
    printf("%s", err_msz);
    return false;
  }
  return true; // if the exp successfully validated
}


// This function read input and check validation of it
// Input is limmited to 100 (one hundred) charcters 
void InFix :: input(const char *ip_exp){
  
  // cast to string type and validate
  exp_validation = validateInputExp(string(ip_exp));
  
  // if expression is not correctly given or validated, then
  if (exp_validation != true){ 
    printf("\n InputError : given input can't be taken as expression ");
    return;
  }
  // if input() func is already have a validated input exp
  delete []exp; // de-allocate the existing memory
  exp = new char[100](); // re-allocate a new  memory
  exp = ip_exp; // if successfully validated then assigned
}


// This function read the input and check validation of it
// Input is limmited to 100 (one hundred) charcters 
void InFix :: input(string &ip_exp){
  
  // the only reason to copy the passed string into an another string only bcz string references multiple have some error when passed multiple times, and another reason is need of  dynamic memory for assignment
  string *copy_ip_exp = new string(ip_exp);
  
  // validate the given new expression
  exp_validation = validateInputExp(*copy_ip_exp);
  
  // if expression is not correctly given, then
  if (exp_validation != true){ 
    printf("\n InputError : given input can't be taken as expression ");
    delete copy_ip_exp;  copy_ip_exp = nullptr;
    return;
  }
  delete []exp; // if input() func called previous then delete the existed content of it
  exp = copy_ip_exp->c_str(); // then assigned the content along with allocated memory of another pointer
  copy_ip_exp = nullptr; // remove the other pointer from the content and no need to free this pointer memory bcz that memory is now pointed by the 'exp' pointer
}


// This function takes input[Max 100 characters] in run-time
// It accepts reference of input stream object like ("cin")
void InFix :: input(istream &ip){
  
  // first input the exp from user at run-time 
  char *ip_exp = new char[100]();
  ip.getline(ip_exp, 99);
  
  // cast to string type and validate
  exp_validation = validateInputExp(string(ip_exp));
  
  // if expression is not correctly given, then
  if (exp_validation != true){ 
    printf("\n InputError : given input can't be taken as expression ");
    delete []ip_exp;  ip_exp = nullptr;  
    return;
  }
  delete []exp; // if the input() func called previous then delete the existed content of it by free up the memory
  exp = ip_exp; // then assigned te content along with allocated memory of another pointer
  ip_exp = nullptr; // remove the other pointer from the content and no need to free the memory bcz that memory is now pointed by the 'exp' pointer 
}


// This function returns the successfully validated 
// input expression without spaces (if provided)
const char* InFix :: getInputExp(){
  
  if (exp_validation == false){
    printf("\n ValueError : input was not taken or validated to return any value ");  
    return  "\0";
  }
  unsigned short int exp_len = string(exp).length();
  char *copy_exp_without_spaces = new char[exp_len]();
  
  for (short int i = 0, x = 0; i < exp_len; ++i){
    if (exp[i] != ' '){ copy_exp_without_spaces[x] = exp[i];  ++x; }
  }
  // delete the content(with sapces) from memory
  delete []exp;  exp = nullptr;
  // assign the memory of the new content(without sapces)
  exp = copy_exp_without_spaces;  
  // remove the other pointer pointing
  copy_exp_without_spaces = nullptr;
  
  return exp;
}


// This function displays the 
// successfully validated input expression
void InFix :: showInputExp(){
  
  if (exp_validation == false){
    printf("\n DisplayError : input was not taken or validated to display ");
    return;
  }
  this->getInputExp(); // to remove the spaces
  unsigned short int exp_len = string(exp).length();
  
  printf("\n Input Expression   :  ");
  for (short int i = 0; i < exp_len; ++i){
    
    // digits should be printed without spaces
    if (isdigit(exp[i]) == true){ 
      printf("%c", exp[i]);
      // put a space at the end of constant operand
      if (not isdigit(exp[i + 1])){ printf(" "); }
    }
    else { printf("%c ", exp[i]); }
  }
}


// This function converts the given expression(_exp) into it's Postfix Notation and stored the result into another expression(final_exp) 
void InFix :: convertToPostfix(const short int &exp_len, const char *_exp, char *final_exp){
  
  // implementing a stack and some functions for operation
  struct stack {  string stack; 
    
    void Push(const char &C){ stack.push_back(C); }
    const char& top(){ return  stack.back(); }
    
    /** @note : string.back() -> returns the last char of the string */
    const char Pop(){
      if (stack.empty() == true){ return '\0'; }
      const char C = stack.back(); 
      stack.pop_back();
      return C;
    }
    const short int priority_(const char &C){
      if (C == '^' || C == '$') { return 3; }
      else if (C == '%' || C == '/' || C == '*'){ return 2; }
      else if (C == '-' || C == '+'){ return 1; }
      else { return 0; }
    }
  } s /*Object*/;
  
  // convertion logic starts...
  short int _x = 0; // for result expression index
  for (short int i = 0; i < exp_len; ++i){
    
    // if alphabet operand occur then directly goes to the final_exp
    if (isalpha(_exp[i]) == true){
      final_exp[_x] = _exp[i];
      ++_x;
    }
    // if constants occours then it also goes to the final_exp
    else if (isdigit(_exp[i]) == true){
      while (isdigit(_exp[i]) == true){
        final_exp[_x] = _exp[i];
        ++_x;  ++i;
      }
      --i; // to prevent the skip of one char
      // bcz while loop ++i (+) for loop ++i = skip one char
    }
    else { // means :  _exp[i] == 'ohers (operators / pairs)'
      if (s.stack.empty() != true){
        
        // if any open bracket occours then put into in satck
        // or if the stack top == '(' then also put the current elem
        // otherwise that elem(operator) is being compared with the '(' in the basis of priority and cause problem
        if (_exp[i] == '(' || s.top() == '('){ s.Push(_exp[i]); }
        
        // if any close pair occour then pop all elements until open pair
        else if (_exp[i] == ')'){
          
          // popped out all elems till open pair
          while (s.top() != '('){
            final_exp[_x] = s.Pop();
            ++_x;
          }
          s.Pop(); // to remove the open pair also
        }
        else { // means operators like (+,-,*,/,%,^)
          
          // as lower priority operators can't be put after higher priority operators that's why 
          if (s.priority_(_exp[i]) < s.priority_(s.top()) ){
            
            // pop all the elems till priority gets same / greater
            while (s.priority_(_exp[i]) < s.priority_(s.top()) ){
              final_exp[_x] = s.Pop();
              ++_x;
            }
            s.Push(_exp[i]); // push that lower priority operator
          }
          // if the ocoured operator priority is same or greater
          else { s.Push(_exp[i]); }
        }
      }
      else { // means stack is empty 
        s.Push('#'); // represent as a stack end
        s.Push(_exp[i]); // push the first occoured operator
      }
    }
  }
  // now if any thing left in the stack then pop all the things
  if (s.stack.empty() != true){
    while (s.top() != '#'){
      final_exp[_x] = s.Pop();
      ++_x;
    }
  }
}


// This function returns the Postfix Notation
// of the input expression (excluding spaces)
const char* InFix :: getPostfixExp(){
  
  if (exp_validation == false){
    printf("\n ValueError : input was not taken or validated to return any value ");
    return  "\0";
  }
  // for only one character the logical code is not needed
  unsigned short int exp_len = string(exp).length();
  if (exp_len < 2){ return  exp; }
  
  // delete & re-allocate the result for fresh result
  delete []res_exp;  res_exp = nullptr;
  res_exp = new char[100]();
  
  char *copy_exp = new char[exp_len]();
  // discard the spaces and copy into a new char[]
  for (short int i = 0, x = 0; i < exp_len; ++i){
    if (exp[i] != ' '){ copy_exp[x] = exp[i];  ++x; }
  }
  
  // convert it into the postfix expression 
  convertToPostfix(exp_len, copy_exp, res_exp);
  
  delete []copy_exp;  copy_exp = nullptr;
  return  res_exp;
}


// This function displays the 
// Postfix Notation of the input expression
void InFix :: showPostfixExp(){
  
  if (exp_validation == false){
    printf("\n DisplayError : input was not taken or validated to display ");
    return;
  }
  this->getPostfixExp(); // to convert into postfix
  unsigned short int exp_len = string(res_exp).length();
  
  printf("\n Postfix Expression :  ");
  for (short int i = 0; i < exp_len; ++i){
    
    // digits should be printed without spaces
    if (isdigit(res_exp[i]) == true){ 
      printf("%c", res_exp[i]);
      // put a space at the end of constant operand
      if (not isdigit(res_exp[i + 1])){ printf(" "); }
    }
    else { printf("%c ", res_exp[i]); }
  }
}


// This function returns the Prefix Notation
// of the input expression (excluding spaces)
const char* InFix :: getPrefixExp(){
  
  if (exp_validation == false){
    printf("\n ValueError : input was not taken or validated to return any value ");
    return  "\0";
  }
  // for only one character the logical code is not needed
  unsigned short int exp_len = string(exp).length();
  if (exp_len < 2){ return  exp; }
  
  // delete & re-allocate the result exp (if stored any)
  delete []res_exp;  res_exp = nullptr;
  res_exp = new char[100]();
  
  char *rev_exp = new char[exp_len]();
  char *final_exp = new char[exp_len]();
  
  // first reverse the whole exp properly
  for (short int  i = exp_len - 1,_i_ = 0;  i >= 0;  ){
    
    // reverse the constants(number operands)
    if (isdigit(exp[i]) == true){
      
      string *no = new string();
      // reverse the number operand
      while (isdigit(exp[i]) == true){
        no->push_back(exp[i]);
        --i;
      }
      // put the reversed number operand into the actual expression
      for (short int i = no->size() - 1; i >= 0; --i){
        rev_exp[_i_] = no->at(i);
        ++_i_;
      }
      delete no;  no = nullptr;
    }
    // discard the spaces
    else if (exp[i] == ' '){/* Do-nothing */ --i; }
    // convert the paranthesis
    else if (exp[i] == '('){ rev_exp[_i_] = ')';  ++_i_;  --i; }
    else if (exp[i] == ')'){ rev_exp[_i_] = '(';  ++_i_;  --i; }
    // else :  other things put as it is
    else { rev_exp[_i_] = exp[i];  ++_i_;  --i; }
  }
  
  // now convertng the reversed expression into postfix notation
  convertToPostfix(exp_len, rev_exp, final_exp);
  
  exp_len = string(final_exp).length(); // reuse the 'exp_len' var
  // now again reversing the final_exp to get the prefix notation
  for (short int  i = exp_len - 1, _i_ = 0;  i >= 0;  ){
    
    // reverse the constants(number operands)
    if (isdigit(final_exp[i]) == true){
      
      string *no = new string();
      // reverse the number operand
      while (isdigit(final_exp[i]) == true){
        no->push_back(final_exp[i]);
        --i;
      }
      // put the reversed number operand into the actual expression
      for (short int i = no->size() - 1; i >= 0; --i){
        res_exp[_i_] = no->at(i);
        ++_i_;
      }
      delete no;  no = nullptr;
    }
    // convert the paranthesis
    else if (final_exp[i] == '('){ res_exp[_i_] = ')';  ++_i_;  --i; }
    else if (final_exp[i] == ')'){ res_exp[_i_] = '(';  ++_i_;  --i; }
    // else :  other things put as it is
    else { res_exp[_i_] = final_exp[i];  ++_i_;  --i; }
  }
  
  delete []rev_exp;  rev_exp = nullptr;
  delete []final_exp;  final_exp = nullptr;
  return  res_exp;
}


// This function displays the 
// Prefix Notation of the input expression
void InFix :: showPrefixExp(){
  
  if (exp_validation == false){
    printf("\n DisplayError : input was not taken or validated to display ");
    return;
  }
  this->getPrefixExp(); // to convert into postfix
  unsigned short int exp_len = string(res_exp).length();
  
  printf("\n Prefix Expression  :  ");
  for (short int i = 0; i < exp_len; ++i){
    
    // digits should be printed without spaces
    if (isdigit(res_exp[i]) == true){ 
      printf("%c", res_exp[i]);
      // put a space at the end of constant operand
      if (not isdigit(res_exp[i + 1])){ printf(" "); }
    }
    else { printf("%c ", res_exp[i]); }
  }
}


// class "InFix" is the Implemented class for handling the Infix Expressions and converting the Stack Expressions form it's Infix Notation to it's Prefix and Postfix notations.
typedef  InFix  InfixExpression;

#include <iostream>

int main(){
  
  InFix  e;
  cout <<endl<<" Enter the Infix Exprrssion : ";
  e.input(cin);
  e.showInputExp();
  e.showPrefixExp();
  e.showPostfixExp();
  cin.get();
  return 0;
}


#endif // _INFIXEXPRESSION_H_
