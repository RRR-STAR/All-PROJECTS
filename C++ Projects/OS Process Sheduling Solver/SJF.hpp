
/**
 * @package    : OS NUMERIC ALGORITHMS
 * @headerfile : SJF.H++
 * @namespace  : SJF {}
 * @class      : SJF::Process
 * 
 * This File contains all the functionalities for handling the 
 * SJF [Shortest Job First] algorithm.
 * 
 * @details : Shortest Job First algorithm Solver
 */


#ifndef __SJF__ALGO__
#define __SJF__ALGO__


#include <iostream>
using namespace std;


namespace SJF {
  
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
    inline short retPNUM(){ return  processNum; }
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
    
    short int n, x, completed_processes = 0;
    double at, bt, least_at, cpu_cycle = 0, avg_bt = 0, avg_tat = 0, avg_wt = 0;
    
    cout <<"\n\n\t No. of Processes :  ";  cin >> n;
    Process *P[n], *ready_queue[n], *running_p = nullptr;
    
    for (short int i = 0; i < n; ++i){
      cout <<"\n";
      cout <<"\t Enter "<< i+1 <<" Process Arrival Time : ";  cin >> at;
      cout <<"\t Enter "<< i+1 <<" Process Burst Time   : ";  cin >> bt;
      
      P[i] = new Process(i+1, at, bt);
    }
    // finding the Smallest arrival time process
    least_at = P[0]->retAT();
    for (short int i = 1; i < n; ++i){
      
      if (least_at > P[i]->retAT()){
        least_at = P[i]->retAT();
      }
    }
    // intilize the cpu cycle to the samllest arrival time
    cpu_cycle = least_at;
    cout <<"\n\n\t\t GRANT CHART >\n";
    
    while (completed_processes != n){
      
      x = 0;
      // put all the Arrived Processes in a Queue
      for (short int j = 0; j < n; ++j){
        
        if (P[j]->retAT() <= cpu_cycle  and  P[j]->retFLAG() == false){
          ready_queue[x] = P[j];  ++x;
        }
      }
      // if no new process arrived
      if (x == 0){ ++cpu_cycle;  continue; }
      
      // finding the smallest burst time from arrived processes
      running_p = ready_queue[0];
      for (short int j = 1; j < x; ++j){
        
        if (ready_queue[j]->retBT() < running_p->retBT()){
          running_p = ready_queue[j];
        }
      }
      // execute the Samllest burstTime process
      cpu_cycle += running_p->retBT();
      running_p->assignResults(cpu_cycle);
      
      ++completed_processes;
      cout <<"\n\t\t P"<< running_p->retPNUM() <<'\t'<< cpu_cycle;
      running_p = nullptr;
    }
    cout <<"\n\n";
    cout <<"\n\t P[N]\tAt\tBt\tCt\tTat\tWt\tCflag";
    cout <<"\n\t ----\t--\t--\t--\t---\t--\t-----";
    
    for (short int i = 0; i < n; ++i){
      
      avg_bt += P[i]->retBT();
      avg_tat += P[i]->retTAT();  
      avg_wt += P[i]->retWT();
      P[i]->showAllValues();
      
      delete P[i]; // delete all the array
      P[i] = ready_queue[i] = nullptr; // prevent from being dangling ptr
    }
    cout <<"\n\n\t Throughput = "<< avg_bt/n;
    cout <<"\n\t Avarage Turn Around Time = "<< avg_tat/n;
    cout <<"\n\t Avarage Waiting Time = "<< avg_wt/n;
    
    cout <<"\n\n\t Want to calculate SJF Again ? \n\t Press 'A' ...  ";
    cin.get();
    if (cin.get() == 'A')  goto repeat;
    return;
  }
}

#endif //  __SJF__ALGO__