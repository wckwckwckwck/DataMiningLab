#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include<vector>
#include<map>
#include<list>
#include<map>
#include<fstream>
#include<algorithm>
map<int,int> mdata;

typedef map<int,int> mii;
typedef map<vector<int>,int> mvi;
const int MAX_SIZE= 1e4;



mvi dv;
int min_sup=6;
//读取文件 



bool isSubVector(vector<int> v1,vector<int> v2){
    int s1=v1.size();
    int s2=v2.size();
    // if(s1>=s2){
    //     vector<int> tmp=v1;
    //     v1=v2;
    //     v2=tmp;
    // };
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.begin());
    int i=0;int j=0;
    while(i<s1 && j<s2){
        if(v1[i]==v2[j]) {i++;j++;}
        else if(v1[i]<v2[j]) i++;
        else if(v1[i]>v2[j]) break;
    }
    bool res=(i==s1);
    return res;
}


void readfile(){
    int i=0;
    ifstream dfile("T1014D1K.dat");
    int a;
    string tmp;
    vector<int> vstor;
    while(getline(dfile,tmp)){//每次读取一行 
        vstor.clear();
        std::stringstream ss(tmp);
        while(ss){
            ss>>a;
            vstor.push_back(a);
            
            int ta;
            stringstream st;
            st<<a;
            st>>ta;
            if(mdata[ta]==0){
                mdata[ta]=1; //如果没有该字符，数值设为1
            }
            else{mdata[ta]++;}
        }
        dv[vstor]=1;
        // cout<<tmp<<endl;

    }
    // dfile>>a;
    // cout<<a<<endl;
}


int findVectorInMap(vector<int> v_data,mvi m_data){
    int sum=0;
    for(mvi::iterator mviit=m_data.begin();mviit!=m_data.end();mviit++){
        if(isSubVector(v_data,mviit->first)) sum++;
    }
    return sum;    
}

// 从一项集生成二项集
map<vector<int>,int> apriori(map<int,int> m_data,int min_sup){
    int count=1;
    map<int,int> t_data=m_data;
    map<vector<int>,int> res_data;
    for(map<int,int>::iterator it1=t_data.begin();it1!=t_data.end();it1++){
        map<int,int>::iterator it2=it1;
        for(it2++;it2!=t_data.end();it2++){
            vector<int> tmp_vec={it1->first,it2->first};
            if(res_data.count(tmp_vec)>0) continue;
            int appeartime=findVectorInMap(tmp_vec,dv);
            if(appeartime>=min_sup) {
                // cout<<min_sup<<endl;
                res_data[tmp_vec]=appeartime;
            }
            else continue;
        }
    }
    return res_data;
}






//输入mii类型，过滤其中支持度
void apriorifilter(mii &t1,int minsup,bool doOutput){
    for (mii::iterator it=t1.begin();it!=t1.end();){
        mii::iterator it2;
        bool is_begin=(it==t1.begin());
        if(!is_begin){
         it2=it;
         it2--;
         }
        if(it->second<minsup) {
        t1.erase(it);
        if(is_begin){
            it=t1.begin();
        }
        else{
        it=it2++;}
        }
        it++;
    }
    if(doOutput){
        string s="Apriori_minsup_"+std::to_string(minsup)+".txt";
        std::ofstream outfile(s);
        for (mii::iterator it=t1.begin();it!=t1.end();it++){
            outfile<<"one set:{"<<it->first<<"} appear "<<it->second<<"Times"<<endl;
            cout<<"one set:{"<<it->first<<"} appear "<<it->second<<"Times"<<endl;
    
        }
    }
       
}

void apriorifilter(mvi &t1,int minsup,bool doOutput)
{
     for (mvi::iterator it=t1.begin();it!=t1.end();){
        mvi::iterator it2;
        bool is_begin=(it==t1.begin());
        if(!is_begin){
         it2=it;
         it2--;
         }
        if(it->second<minsup) {
        t1.erase(it);
        if(is_begin){
            it=t1.begin();
        }
        else{
        it=it2++;}
        }
        it++;
    }
    // if(doOutput){
    //     string s="Apriori_minsup_"+std::to_string(minsup)+".txt";
    //     std::ofstream outfile(s);
    //     for (mvi::iterator it=t1.begin();it!=t1.end();it++){
    //         outfile<<"one set:{"<<it->first<<"} appear "<<it->second<<"Times"<<endl;
    //         cout<<"one set:{"<<it->first<<"} appear "<<it->second<<"Times";
    
    //     }
    // }
}

//重载输出符，可以输出mvi
ostream & operator<< (ostream & os ,map<vector<int>,int> ts){

    int chuxian;
    for(mvi::iterator it=ts.begin();it!=ts.end();it++ ){
        os<<"Busy{"<<" ";
        vector<int> t=it->first;
        for(auto itv:t){
            os<<itv<<" ";
        }
        chuxian=ts.begin()->second;

        os<<"}time:"<<chuxian<<endl;
    }
}


//输入mvi，输出其中元素 
void printmap(mvi ts){
    for(mvi::iterator it=ts.begin();it!=ts.end();it++ ){
        cout<<"Frequent item set:{"<<" ";
        vector<int> t=it->first;
        for(auto itv:t){
            cout<<itv<<" ";
        }
        int chuxian=it->second;

    cout<<"},Appear tiime:"<<chuxian<<endl;
    }
}

void printVector(vector<int> vi){
    for(vector<int>::iterator it=vi.begin();it!=vi.end();it++){
        cout<<*it;
    }
}


//测试map函数
void maptest(){
    mvi t1;
    vector<int> v1={1,2,3};
    vector<int> v2={1,2,3,4};
    t1[v1]=2;
    t1[v2]=3;
}

int main(){

    readfile();
    const int min_sup=8;
    // cout<<res<<endl;
    apriorifilter(mdata,min_sup,true);//过滤数据集中是否非频繁，然后输出
    map<vector<int>,int> res=apriori(mdata,min_sup);//生成二项集 
    // cout<<res<<endl;
    printmap(res);
    // apriorifilter(mdata,8,false);
    // cout<<t1;

    system("pause");

}

