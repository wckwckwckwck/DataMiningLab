#include<iostream>
#include<vector>
using namespace std;
#include<algorithm>

bool isSubVector(vector<int> v1,vector<int> v2){
    int s1=v1.size();
    int s2=v2.size();
    // if(s1>=s2){
    //     vector<int> tmp=v1;
    //     v1=v2;
    //     v2=tmp;
    // };
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    int i=0;int j=0;
    while(i<s1 && j<s2){
        if(v1[i]==v2[j]) {i++;j++;}
        else if(v1[i]> v2[j]) j++;
        else if(v1[i] <v2[j]) break;
    }
    bool res=(i==s1);
    return res;
}
#include<time.h>
int main(){
    vector<int> p1={3,7};
    vector<int>p2={1,2,3,5,7,9};
    clock_t t1=clock();
     
    for(int i=0;i<1e3;i++){
        cout<<isSubVector(p1,p2);
    }
    clock_t t2=clock();
    cout<<t2-t1<<endl;
    system("pause");

}