#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<sstream>

#include<algorithm>
#include<set>
using namespace std;

typedef map<int,int> mii;
typedef map<vector<int>,int> mvi;
typedef vector<int> vi;

map<int,int> mdata;
set<vector<string>> svidata;
mvi dv;
map<string,int> ldata;
void readfile(){
    int i=0;
    ifstream dfile("t1.dat");
    int a;
    string tmp;
    vector<int> vstor;
    while(getline(dfile,tmp)){
        stringstream ss(tmp);
        string str_tmp;
        while(ss>>str_tmp){
            if(ldata[str_tmp]==0){
                ldata[str_tmp]=1;
            }
            else(ldata[str_tmp]++);
        }
    }

    
    
}

int main(){
    cout<<"hello Wrold"<<endl;
    readfile();
    system("pause");
}

bool sortStringAppearTime(string a,string b){
    return (ldata[a]>ldata[b]);
}