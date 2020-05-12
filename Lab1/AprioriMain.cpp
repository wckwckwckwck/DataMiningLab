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
#include<time.h>
#include<windows.h>
typedef map<int,int> mii;
typedef map<vector<int>,int> mvi;
typedef vector<int> vi;
const int MAX_SIZE= 1e4;



mvi dv;
int min_sup=6;

SYSTEMTIME sys;
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
        sort(vstor.begin(),vstor.end());//排序好后插入 
        dv[vstor]=1;
        // cout<<tmp<<endl;

    }
    // dfile>>a;
    // cout<<a<<endl;
}

bool isSubVector(vector<int> v1,vector<int> v2){
    int s1=v1.size();
    int s2=v2.size();
    // if(s1>=s2){
    //     vector<int> tmp=v1;
    //     v1=v2;
    //     v2=tmp;
    // };
    sort(v1.begin(),v1.end());
    // sort(v2.begin(),v2.end());
    int i=0;int j=0;
    while(i<s1 && j<s2){
        if(v1[i]==v2[j]) {i++;j++;}
        else if(v1[i]> v2[j]) j++;
        else if(v1[i] <v2[j]) break;
    }
    bool res=(i==s1);
    return res;
}

vi vectormerge(vi v1,vi v2){
    int s1=v1.size();
    int s2=v2.size();
    if(s1>=s2){
        vector<int> tmp=v1;
        v1=v2;
        v2=tmp;
    };
    for(auto v1it:v1){
        if(std::find(v2.begin(),v2.end(),v1it)==v2.end())
            v2.push_back(v1it);

    }
    sort(v1.begin(),v1.begin());
    return v2;
}

// int findVectorInMap(vector<int> v_data,mvi m_data){
//     int sum=0;
//     for(mvi::iterator mviit=m_data.begin();mviit!=m_data.end();mviit++){
//         if(isSubVector(v_data,mviit->first)) sum++;
//     }
//     return sum;    
// }

//重载一个快捷搜索，搜索到大于支持度就停下
int findVectorInMap(vector<int> v_data,mvi m_data,int min_sup){
    int sum=0;
    GetLocalTime(&sys);
    cout<<"fuc start"<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<endl; 

    // for(mvi::iterator mviit=m_data.begin();mviit!=m_data.end();mviit++)
    for(auto mviit:m_data)
    {
    cout<<"funcend"<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<endl; 

        return sum;

        // clock_t t1=clock();
    // cout<<"begintime"<<t1;
        // if(isSubVector(v_data,mviit->first)) sum++;
        
        // sort(v_data.begin(),v_data.end());
        
        // bool isin=includes(mviit->first.begin(),mviit->first.end(),v_data.begin(),v_data.end());
        bool isin=true;
        if(isin) sum++;
        // cout<<"per time"<<1000*(t2-t1)<<" ";
        if(sum>=min_sup)  {
            return sum;
    }
    }
    // cout<<";end time: "<<t2<<"  "<<endl;

    return sum;    
}

// 从一项集生成二项集
map<vector<int>,int> apriori(map<int,int> m_data,int min_sup){
    int count=1;
    map<int,int> t_data=m_data;
    map<vector<int>,int> res_data;
    for(map<int,int>::iterator it1=t_data.begin();it1!=t_data.end();it1++){
        map<int,int>::iterator it2=it1;
        clock_t t1=clock();
        for(it2++;it2!=t_data.end();it2++){
            vector<int> tmp_vec={it1->first,it2->first};
            if(res_data.count(tmp_vec)>0) continue;
            clock_t t3=clock();
            // cout<<it2->first<<"beforfind "<<t3-t1<<endl;
           GetLocalTime(&sys);
    cout<<"beforetime "<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<endl; 
           
            int appeartime=findVectorInMap(tmp_vec,dv,min_sup); //判断生成的新二项集出现次数 
    cout<<"aftertime "<<sys.wMinute<<" "<<sys.wSecond<<" "<<sys.wMilliseconds<<" "<<endl; 

            // int appeartime=10;
            // clock_t t4=clock();
            // cout<<it2->first<<"afterfind: "<<t4-t1<<endl;

            if(appeartime>=min_sup) {                    //大于置信度，则放入Map
                res_data[tmp_vec]=appeartime;
            }
            else continue;
        }
        clock_t t2=clock();
        cout<<it1->first<<" "<<t2-t1<<endl;
    }
    return res_data;
}

mvi apriori(mvi m_data,int min_sup){
    mvi t_data=m_data;
    mvi databack;
     for(mvi::iterator it1=t_data.begin();it1!=t_data.end();it1++){
        mvi::iterator it2=it1;

        int visize=it2->first.size();
        for(it2++;it2!=t_data.end();it2++){
            
            vi vi_tmp=vectormerge(it1->first,it2->first);
            if(vi_tmp.size()!=visize+1) continue;
            else {
                int appearTime=findVectorInMap(vi_tmp,dv,min_sup);
                if(appearTime>=min_sup){
                    databack[vi_tmp]=appearTime;
                }
                else continue;
            }
        }
        cout<<"Courrent progress:size="<<visize<<" num="<<it1->first.front()<<endl;
    }
    return databack;
}

//返回目标map里面，vector长度，map长度
pair<int,int> checkMapSize(mvi mvidata){
    if(mvidata.empty()) return make_pair(0,0);
    int a=mvidata.begin()->first.size();
    int b=mvidata.size();
    cout<<"Current map vector-size:"<<a<<" ,map-size:"<<b<<endl;
    return std::make_pair(a, b);
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

//剪枝，判断vector是否所有自己都在Ln-1中
bool vectorCompare(vi t1,mvi tcompare){
    for(vi::iterator it=t1.begin();it!=t1.end();it++){
        vi t2;
        for(auto itv:t1){
            if(itv==*it) {}
            else {
                t2.push_back(itv);
            }
        }
        if(findVectorInMap(t2,tcompare,1)==0) return false;
    }
    return true;
}

void printVector(vector<int> vi){
    for(vector<int>::iterator it=vi.begin();it!=vi.end();it++){
        cout<<*it;
    }
}

bool apriorifilter(mvi &t1,mvi tcompare){
    for(mvi::iterator it=t1.begin();it!=t1.end();){
        if(vectorCompare(it->first,tcompare)==false) //判断，若当前集合，自己不在Ln-1中
        {   
            mvi::iterator it2=it;
            if(it==t1.begin()){
                t1.erase(it);
                it=t1.begin();
            }
            else{
                it2--;
                t1.erase(it);
                it=it2++;
            }
        }
        it++;
    }
    return true;
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




//测试map函数
void maptest(){
    mvi t1;
    vector<int> v1={1,2,3};
    vector<int> v2={1,2,3,4};
    t1[v1]=2;
    t1[v2]=3;
}

void writeMap(mvi t1,int min_sup){
    pair<int,int> mapsize=checkMapSize(t1);
    string s="Ap_minsup_vsize_msize"+std::to_string(min_sup)+"_"+std::to_string(mapsize.first)+"_"+std::to_string(mapsize.second)+".txt";
    std::ofstream outfile(s);
    for(mvi::iterator it=t1.begin();it!=t1.end();it++){
        vi vitmp=it->first;
        outfile<<"FruquentSet:{";
        for(auto viit:vitmp){
            outfile<<viit<<" ";
        }
        outfile<<"} AppearTime:"<<it->second<<endl;
    }
        
}





int main(){
    readfile();
    const int min_sup=8;
    // cout<<res<<endl;
    apriorifilter(mdata,min_sup,true);//过滤数据集中是否非频繁，然后输出
    map<vector<int>,int> res=apriori(mdata,min_sup);//生成二项集 
    // cout<<res<<endl;
    printmap(res);
    writeMap(res,min_sup);
    // apriorifilter(mdata,8,false);
    // cout<<t1;
    pair<int,int> data=checkMapSize(res);
    while(data.first!=0 && data.second!=0){
        int min_sup2=8;
        mvi res_process;
        res_process=apriori(res,min_sup2);
        apriorifilter(res_process,res);
        data=checkMapSize(res_process);
        printmap(res_process);
        writeMap(res_process,min_sup);
        res=res_process;
    }
    cout<<"over"<<endl;
    system("pause");

}

