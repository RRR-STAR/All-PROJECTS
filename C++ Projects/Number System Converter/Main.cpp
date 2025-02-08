
#include <iostream>
#include <conio.h>
#include "NumberSystem.h++"
using namespace std;


main(){
  repeat :  system("cls");  flush(cout);
  
  cout <<"\n\t--------------------------------------------------------";
  cout <<"\n\t|           Welcome to Number System Converter         |";
  cout <<"\n\t--------------------------------------------------------";
  
  NumberSystem *n = new NumberSystem();
  
  n->input();
  
  cout <<endl<<" Eqivalent Binary Value      : "<< n->getBinary();
  cout <<endl<<" Eqivalent Octal Value       : "<< n->getOctal();
  cout <<endl<<" Eqivalent Decimal Value     : "<< n->getDecimal();
  cout <<endl<<" Eqivalent HexaDecimal Value : "<< n->getHexaDecimal();
  
  delete n;   n = nullptr;
  
  cout <<"\n\n Want to repeat ?  Press [A] ...  ";
  if (getche() == 'A'){ goto repeat; }
  
  return 0;
}
