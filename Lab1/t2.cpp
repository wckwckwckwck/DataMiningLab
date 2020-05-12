#include<map>
#include<iostream>
#include<time.h>
using namespace std;
#include<map>
#include<vector>
#include<windows.h>
int main(){
     SYSTEMTIME sys;
    GetLocalTime( &sys );
    map<vector<int>,int> m1;
    for (int i=0;i<1000;i++){
        vector<int> p1={i,i+1,i+2};
        m1[p1]=i;
    }
    clock_t t1=clock();
    cout<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "; 

    for(auto t:m1){
        // cout<<t.second<<endl;
    }
    clock_t t2=clock();
    cout<<"Time = "<<t2-t1<<endl;
    cout<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "; 
   
    system("pause");
}