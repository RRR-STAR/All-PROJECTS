
/**
 * @package    : OS NUMERIC ALGORITHMS
 * @headerfile : FCFS.H++
 * @namespace  : FCFS {}
 * @class      : FCFS::Process
 * 
 * This File contains all the functionalities for handling the 
 * FCFS [First Come First Serve] algorithm.
 * 
 * @details : First Come First Serve algorithm Solver
 */


#ifndef __FCFS__ALGO__
#define __FCFS__ALGO__


#include <iostream>
using namespace std;


namespace FCFS {
  
  class Process {
    
    bool completeFlag;
    short int processNum; 
    double arrivalTime, burstTime, completionTime, waitingTime, turnAroundTime;
    
    public :
    
    Process(short int p_num, double At, double Bt){ 
      this->processNum = p_num;
      this->arrivalTime = At;
      this->burstTime = Bt;
      this->completionTime = 0;
      this->waitingTime = 0;
      this->turnAroundTime = 0;
      this->completeFlag = false;
      /*cout <<"\n Process P["<< processNum <<"] Created";*/ 
    }
    ~Process(){ /*cout <<"\n Process P["<< processNum <<"] Destroyed";*/ }
    
    void assignResults(double Ct){
      completionTime = Ct;
      turnAroundTime = completionTime - arrivalTime;
      waitingTime = turnAroundTime - burstTime;
      completeFlag = true;
    }
    inline int retPNUM(){   return  processNum; }
    inline double retAT(){  return  arrivalTime; }
    inline double retBT(){  return  burstTime; }
    inline double retWT(){  return  waitingTime; }
    inline double retTAT(){ return  turnAroundTime; }
    inline bool retFLAG(){  return  completeFlag; }
    
    void showAllValues(){
      cout <<"\n\t P["<< processNum <<"]\t";
      cout << arrivalTime <<"\t";
      cout << burstTime <<"\t";
      cout << completionTime <<"\t";
      cout << turnAroundTime <<"\t";
      cout << waitingTime <<"\t";
      cout << completeFlag;
    }
  };
  
  void Main(){  repeat :
    
    short int n; // total no. of processes
    double at, bt, cpu_cycle = 0, avg_bt = 0, avg_tat = 0, avg_wt = 0;
    
    cout <<"\n\n\t No. of Processes :  ";  cin >> n;
    Process  *P[n], *tempPtr = nullptr;
    
    for (short int i = 0; i < n; ++i){
      cout <<'\n';
      cout <<"\t Enter "<< i+1 <<" Process Arrival Time : ";  cin >> at;
      cout <<"\t Enter "<< i+1 <<" Process Burst Time   : ";  cin >> bt;
      
      P[i] = new Process(i+1, at, bt);
    }
    
    // Sorting the arrival Processes through bubble sort(oprtimized)
    for (short int i = 0; i < n; ++i){
      
      bool already_sorted = true;
      for (short int j = 0; j < n-i-1; ++j){
        
        if (P[j]->retAT() > P[j + 1]->retAT()){
          already_sorted = false;
          
          tempPtr = P[j];
          P[j] = P[j + 1];
          P[j + 1] = tempPtr;
          tempPtr = nullptr;
        }
      }
      if (already_sorted == true){ 
        break; // if no swapping done then processes are already sorted
      }
    }
    // Execute the Sorted Processes one by one
    cout <<"\n\n\t\t GRANT CHART > \n";
    for (short int i = 0; i < n; ++i){
      
      // if no processes arrived in this cpu cycle 
      if (P[i]->retAT() > cpu_cycle){
        cpu_cycle = P[i]->retAT();
      }
      cpu_cycle += P[i]->retBT();
      P[i]->assignResults(cpu_cycle);
      cout <<"\n\t\t P"<< P[i]->retPNUM() <<'\t'<< cpu_cycle;
    }
    cout <<"\n\n";
    cout <<"\n\t P[N]\tAt\tBt\tCt\tTat\tWt\tCflag";
    cout <<"\n\t ----\t--\t--\t--\t---\t--\t-----";
    
    for (short int i = 0; i < n; ++i){
      
      avg_bt += P[i]->retBT();
      avg_tat += P[i]->retTAT();  
      avg_wt += P[i]->retWT();
      P[i]->showAllValues();
      
      delete P[i]; // deleting all dynamic memories
      P[i] = nullptr; // prevent from being dangling ptr
    }
    
    cout <<"\n\n\t Throughput = "<< avg_bt/n;
    cout <<"\n\t Avarage Turn Around Time = "<< avg_tat/n; 
    cout <<"\n\t Avarage Waiting Time = "<< avg_wt/n;
    cout <<"\n\n\t Want to calculate FCFS Again ? \n\t Press 'A' ...  ";
    cin.get();
    if (cin.get() == 'A')  goto repeat;
    return;
  }
}

#endif //  __FCFS__ALGO__