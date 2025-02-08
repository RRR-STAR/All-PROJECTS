
/**
 * @package    : OS NUMERIC ALGORITHMS
 * @headerfile : PRIORITY.H++
 * @namespace  : PRIORITY {}
 * @class      : PRIORITY::Process
 * 
 * This File contains all the functionalities for handling the 
 * PRIORITY [Priority (non-premetive) version] algorithm.
 * 
 * @details : Priority algorithm Solver
 */


#ifndef __PRIORITY__ALGO__
#define __PRIORITY__ALGO__


#include <iostream>
using namespace std;


namespace PRIORITY {
  
  class Process {
    
    bool completeFlag;
    short int processNum, priority;
    double arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime;
    
    public :
    
    Process(short int p_num, double At, double Bt, short int Pr){ 
      this->processNum = p_num;
      this->arrivalTime = At;
      this->burstTime = Bt;
      this->priority = Pr;
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
    inline short retPR(){   return  priority; }
    inline short retPNUM(){ return  processNum; }
    inline double retAT(){  return  arrivalTime; }
    inline double retBT(){  return  burstTime; }
    inline double retTAT(){ return  turnAroundTime; }
    inline double retWT(){  return  waitingTime; }
    inline bool retFLAG(){  return  completeFlag; }
    
    void showAllValues(){
      cout <<"\n P["<< processNum <<"]\t";
      cout << arrivalTime <<"\t";
      cout << burstTime <<"\t";
      cout << priority <<"\t";
      cout << completionTime <<"\t";
      cout << turnAroundTime <<"\t";
      cout << waitingTime <<"\t";
      cout << completeFlag;
    }
  };
  
  void Main(){  repeat :
    
    short int n, pr, x, completed_processes = 0;
    double at, bt, least_at = 0, cpu_cycle = 0, avg_bt = 0, avg_tat = 0, avg_wt = 0;
    
    cout <<"\n\n No. of Processes :  ";  cin >> n;
    Process *P[n], *ready_queue[n], *running_p = nullptr;
    
    for (int i = 0 ; i < n ; ++i){
      cout <<'\n';
      cout <<" Enter "<< i+1 <<" Process Arrival Time : ";  cin >> at;
      cout <<" Enter "<< i+1 <<" Process Burst Time   : ";  cin >> bt;
      cout <<" Enter "<< i+1 <<" Process Priority     : ";  cin >> pr;
      
      P[i] = new Process(i+1, at, bt, pr);
    }
    
    // finding the Smallest Arrival Time
    least_at = P[0]->retAT();
    for (short int i = 1; i < n; ++i){
      
      if (P[i]->retAT() < least_at){
        least_at = P[i]->retAT();
      }
    }
    // Intilize the cpu_cycle to the Samllest arrivalTime
    cpu_cycle += least_at;
    cout <<"\n\n\tGRANT CHART >\n";
    
    while (completed_processes != n){
      
      x = 0;
      // put all the Arrived Processes in a Queue
      for (short int j = 0; j < n; ++j){
        
        if (P[j]->retAT() <= cpu_cycle  and  P[j]->retFLAG() == false){
          ready_queue[x] = P[j];  ++x;
        }
      }
      // if no new process arrived in queue then,
      if (x == 0){ ++cpu_cycle;  continue; }
      
      // finding the higher priority process from the ready queue
      running_p = ready_queue[0];
      for (short int j = 1; j < x; ++j){
        
        if (ready_queue[j]->retPR() > running_p->retPR()){
          running_p = ready_queue[j];
        }
      }
      // Execute the higher priority Process
      cpu_cycle += running_p->retBT();
      running_p->assignResults(cpu_cycle);
      
      ++completed_processes;
      cout <<"\n\t P"<< running_p->retPNUM() <<'\t'<< cpu_cycle;
      running_p = nullptr;
    }
    cout <<"\n\n";
    cout <<"\n P[N]\tAt\tBt\tPr\tCt\tTat\tWt\tCflag";
    cout <<"\n ----\t--\t--\t--\t---\t--\t--\t-----";
    
    for (short int i = 0; i < n; ++i){
      
      avg_bt += P[i]->retBT();
      avg_tat += P[i]->retTAT();  
      avg_wt += P[i]->retWT();
      P[i]->showAllValues();
      
      delete P[i]; // deleting the dynamic memory
      P[i] = ready_queue[i] = nullptr;
    }
    cout <<"\n\n Throughput = "<< avg_bt/n;
    cout <<"\n Avarage Turn Around Time = "<< avg_tat/n;
    cout <<"\n Avarage Waiting Time = "<< avg_wt/n;
    
    cout <<"\n\n Want to calculate PRIORITY Again ? \n Press 'A' ...  ";
    cin.get();
    if (cin.get() == 'A')  goto repeat;
    return;
  }
}

#endif //  __PRIORITY__ALGO__