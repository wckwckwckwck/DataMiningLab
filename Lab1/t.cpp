#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

#include<map>

#include<vector>
typedef vector<int> vi;
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
int main(){
    vector<int> v1,v2;
	v1.push_back(3);v1.push_back(2);v1.push_back(1);
	v2.push_back(1);v2.push_back(2);
	cout<<isSubVector(v1,v2)<<endl;
	vector<int> v3,v4;
	v3.push_back(3);v3.push_back(1);v3.push_back(2);
	v4.push_back(1);v4.push_back(4);v4.push_back(4);
	cout<<isSubVector(v3,v4)<<endl;
	vector<int> v5,v6;
	v5.push_back(3);v5.push_back(1);v5.push_back(2);v5.push_back(3);
	v6.push_back(1);v6.push_back(2);
	cout<<isSubVector(v5,v6)<<endl;
    v1=vectormerge(v1,v4);
    system("pause");
	return 0;

}