#include <iostream>
#include <stack>
#include <chrono>
using namespace std;

ostream& operator<<(ostream &ost, stack<int> stk){
    cout <<"[ ";
    while (!stk.empty()){
        cout << stk.top() <<' ';
        stk.pop();
    }
    cout <<']';
    return ost;
}

int count = 0;
void TOH(short int n, stack<int> &a, stack<int> &b, stack<int> &c){
    
    count += 1;
    cout <<'\n'<< count <<"no. of times func called\n"<< a << b << c;
    
    if (n > 0){
        TOH(n - 1, a, c, b);
        
        if (!a.empty()){
            c.push(a.top());
            a.pop();
        }
        TOH(n - 1, b, a, c);
    }
    return;
}

int main(){
    stack<int>  a, b, c;
    a.push(0);
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    a.push(5);
    a.push(6);
    
    auto cur_time = chrono :: system_clock :: to_time_t(chrono :: system_clock :: now());
    cout <<endl<< ctime(&cur_time);
    
    TOH(a.size(), a, b, c);
    
    auto cur_time2 = chrono :: system_clock :: to_time_t(chrono :: system_clock :: now());
    cout <<endl<< ctime(&cur_time2);
    return 0;
}
