
/**
 * @package  : OS NUMERIC ALGORITHMS
 * @file     : Main.C++ (main.cpp)
 * @mainpage : Application File
 * 
 * @details  : Main File to be Execute 
 */


#include "RR.hpp"
#include "SJF.hpp"
#include "FCFS.hpp"
#include "PRIORITY.hpp"


main(){  repeat : // a 'goto' command for run the program again
  
  system("cls");
  cout <<"\n\t--------------------------------------------------------";
  cout <<"\n\t|        Welcome to OS Process Sheduling Solver        |";
  cout <<"\n\t--------------------------------------------------------";
  
  cout <<"\n"<< R"(
        Details for Selecting a prticular OS Sheduling Algorithm
        type...
  
          FCFS : For selecting FIRST COME FIRST SERVE Algorithm
          SJF  : For selecting SHORTEST JOB FIRST Algorithm
          RR   : For selecting ROUND ROBIN Algorithm
          PR   : For selecting PRIORITY(non-premetive) Algorithm
  )";
  
  string *userInput = new string();
  cout <<"\n\t Enter your choise ::  ";  cin >> *userInput;
  
  if (*userInput == "FCFS" or *userInput == "fcfs" or *userInput == "Fcfs"){
    system("cls");
    cout <<"\n\t----------------------------------";
    cout <<"\n\t|     First Come First Serve     |";
    cout <<"\n\t----------------------------------";
    FCFS::Main();
  }
  else if (*userInput == "SJF" or *userInput == "sjf" or *userInput == "Sjf"){
    system("cls");
    cout <<"\n\t------------------------------";
    cout <<"\n\t|     Shortest Job First     |";
    cout <<"\n\t------------------------------";
    SJF::Main();
  }
  else if (*userInput == "RR" or *userInput == "rr" or *userInput == "Rr"){
    // system("cls");
    cout <<"\n\t-----------------------";
    cout <<"\n\t|     Round Robin     |";
    cout <<"\n\t-----------------------";
    RR::Main();
  }
  else if (*userInput == "PR" or *userInput == "pr" or *userInput == "Pr"){
    system("cls");
    cout <<"\n\t-----------------------------------";
    cout <<"\n\t|     Priority(non-premetive)     |";
    cout <<"\n\t-----------------------------------";
    PRIORITY::Main();
  }
  else {
    cout <<"\n Please Choose a proper OS Sheduling Algorithm,\n from the mentioned List.\n";
  }
  delete userInput;  userInput = nullptr;
  cin.get();
  cout <<"\n\t Press 'A' for run the pg. again ...  ";
  if (cin.get() == 'A'){ goto repeat; }
  return 0;
}
