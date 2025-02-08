
/**
 * @package    : OS NUMERIC ALGORITHMS
 * @headerfile : RR.H++
 * @namespace  : RR {}
 * @class      : RR::Process
 * 
 * This File contains all the functionalities for handling the 
 * RR [Round Robin] algorithm.
 * 
 * @details : Round Robin algorithm Solver
 */


#ifndef __RR__ALGO__
#define __RR__ALGO__


#include <iostream>
#include <queue>
using namespace std;


namespace RR {
  
  class Process {
    
    bool arrivalFlag, completeFlag, responseFlag;
    short int processNum;
    double arrivalTime, burstTime, tempPtrBurstTime,
    completionTime, turnAroundTime, waitingTime, responseTime;
    
    public :
    
    Process(short int p_num, double At, double Bt){ 
      this->processNum = p_num; 
      this->arrivalTime = At; 
      this->burstTime = Bt; 
      this->tempPtrBurstTime = Bt; 
      this->completionTime = 0; 
      this->turnAroundTime = 0; 
      this->waitingTime = 0;
      this->responseTime = 0;
      this->arrivalFlag = false; 
      this->completeFlag = false; 
      this->responseFlag = false; 
      /*cout <<"\n Process P["<< processNum <<"] Created";*/ 
    }
    ~Process(){ /*cout <<"\n Process P["<< processNum <<"] Destroyed";*/ }
    
    void assignResults(double Ct){
      completionTime = Ct;
      turnAroundTime = completionTime - arrivalTime;
      waitingTime = turnAroundTime - burstTime; 
      completeFlag = true;
    }
    void showAllValues(){
      cout <<"\n P["<< processNum <<"]\t";
      cout << arrivalTime <<"\t";
      cout << burstTime <<"\t";
      cout << completionTime <<"\t";
      cout << turnAroundTime <<"\t";
      cout << waitingTime <<"\t";
      cout << responseTime <<"\t";
      cout << completeFlag;
    }
    inline short retPNUM(){ return  processNum; }
    inline bool retCFLAG(){ return  completeFlag; }
    inline bool retAFLAG(){ return  arrivalFlag; }
    inline bool retRFLAG(){ return  responseFlag; }
    inline double retAT(){  return  arrivalTime; }
    inline double retBT(){  return  burstTime; }
    inline double retTAT(){ return  turnAroundTime; }
    inline double retWT(){  return  waitingTime; }
    inline double retRT(){  return  responseTime; }
    
    inline void setAFLAG(bool B){ arrivalFlag = B; }
    inline void setRFLAG(bool B){ responseFlag = B; }
    inline void setRT(double cpuFirstResponse){ 
      responseTime = cpuFirstResponse - arrivalTime; 
    }
    inline void reduceTempBt(double timeQuantum){ 
      tempPtrBurstTime -= timeQuantum;
    }
    inline double retTempBt(){ 
      if (tempPtrBurstTime < 0) return 0;
      else return tempPtrBurstTime;
    }
  };
  
  void Main(){  repeat :
    
    short int n, completed_processes = 0, 
    arrived_processes = 0, beforeloop_arrived_processes = 0;
    
    double at, bt, time_q, cpu_cycle = 0, 
    avg_bt = 0, avg_tat = 0, avg_wt = 0, avg_rt = 0;
    
    cout <<"\n\n No. of Processes :  ";  cin >> n;
    cout <<"\n Enter the Time Quantam : ";  cin >> time_q;
    if (time_q == 0){ cout <<"\n Time Quantum can't be Zero !";  return; }
    
    Process *P[n], *tempPtr = nullptr;
    queue<Process *> ready_queue;
    
    for (int i = 0; i < n; ++i){
      cout <<'\n';
      cout <<" Enter "<< i+1 <<" Process Arrival Time : ";  cin >> at;
      cout <<" Enter "<< i+1 <<" Process Burst Time   : ";  cin >> bt;
      
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
    // Intilize the cpu_cycle with the least Arrival Time
    cpu_cycle += P[0]->retAT();
    
    ready_queue.push(P[0]); //put the first processes into the queue
    P[0]->setAFLAG(true); // change first Processes Arrival flag to true
    ++arrived_processes; // first process Arrived in Queue
    
    cout <<"\n\n\tGRANT CHART >\n";
    while (completed_processes != n){
      
      // if queue is empty then accessing front() makes error !
      if (not ready_queue.empty()){
        
        // set the Response Time first
        if (ready_queue.front()->retRFLAG() == false){
          ready_queue.front()->setRT(cpu_cycle);
          ready_queue.front()->setRFLAG(true); 
        }
        // set the cpy cycle according to less time
        if (time_q > ready_queue.front()->retTempBt()){
          cpu_cycle += ready_queue.front()->retTempBt();
        }
        else { cpu_cycle += time_q; }
        
        // decrese Burst Time by time Quantam
        ready_queue.front()->reduceTempBt(time_q); 
      }
      
      // check how many new Processes are Arrived 
      // when all Processes are Arrived then this block doesn't execute more
      if (arrived_processes < n){
        no_new_process_arrived_then :
        
        beforeloop_arrived_processes = arrived_processes;
        for (short int j = 1; j < n; ++j){// j = 1 bcz 1st process already arrived
          
          if (P[j]->retAT() <= cpu_cycle  and  P[j]->retAFLAG() == false){
            ready_queue.push(P[j]); // put the Arrived Processes into a Queue
            P[j]->setAFLAG(true); // change the Arrival flag to true
            ++arrived_processes;
          }
        }
      }
      // if no new Processes are arrived
      if (beforeloop_arrived_processes == arrived_processes  and  ready_queue.empty()){
        ++cpu_cycle;  goto no_new_process_arrived_then;
      }
      
      //checking if that Process not over then put it in the Queue again
      if (ready_queue.front()->retTempBt() > 0  and  ready_queue.front()->retCFLAG() == false){
        ready_queue.push(ready_queue.front());
      }
      
      //checking if that Process is finished , then calculate it 
      else if (ready_queue.front()->retTempBt() == 0  and  ready_queue.front()->retCFLAG() == false){
        ready_queue.front()->assignResults(cpu_cycle);
        ++completed_processes;
      }
      
      cout <<"\n\t P"<< ready_queue.front()->retPNUM() <<'\t'<< cpu_cycle;
      ready_queue.pop(); // for selecting the next element into the queue
    }
    cout <<"\n\n";
    cout <<"\n P[N]\tAt\tBt\tCt\tTat\tWt\tRt\tflag";
    cout <<"\n ----\t--\t--\t--\t---\t--\t--\t----";
    
    for (short int i = 0; i < n; ++i){
      
      avg_bt += P[i]->retBT();
      avg_tat += P[i]->retTAT();
      avg_wt += P[i]->retWT();
      avg_rt += P[i]->retRT();
      P[i]->showAllValues();
      
      delete P[i];  P[i] = nullptr;
    }
    cout <<"\n\n Throughput = "<< avg_bt/n;
    cout <<"\n Avarage Turn Around Time = "<< avg_tat/n;
    cout <<"\n Avarage Waiting Time = "<< avg_wt/n;
    cout <<"\n Avarage Response Time = "<< avg_rt/n;
    
    cout <<"\n\n Want to calculate RR again ? \n Press 'A' ...  ";
    cin.get();
    if (cin.get() == 'A')  goto repeat;
    return;
  }
}

#endif //  __RR__ALGO__