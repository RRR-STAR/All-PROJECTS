
#include <iostream>
#include <conio.h>
#include "NumberSystem.hpp"
using namespace std;


main(){
  repeat :  system("cls");  flush(cout);
  
  cout <<"\n\t--------------------------------------------------------";
  cout <<"\n\t|           Welcome to Number System Converter         |";
  cout <<"\n\t--------------------------------------------------------";
  cout <<"\n\n";
  
  NumberSystem *n = new NumberSystem();
  
  n->input();
  
  cout <<endl<<"\t Eqivalent Binary Value      : "<< n->getBinary();
  cout <<endl<<"\t Eqivalent Octal Value       : "<< n->getOctal();
  cout <<endl<<"\t Eqivalent Decimal Value     : "<< n->getDecimal();
  cout <<endl<<"\t Eqivalent HexaDecimal Value : "<< n->getHexaDecimal();
  
  delete n;   n = nullptr;
  
  cout <<"\n\n\t Want to repeat ?  Press [A] ...  ";
  if (getche() == 'A'){ goto repeat; }
  
  return 0;
}
