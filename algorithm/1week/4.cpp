#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main(){
    int n,m; cin>>n>>m;
    vector<int> A,B,plus,mix;
    srand((unsigned int)time(NULL));
    for(int i=0;i<n;i++) A.push_back(rand()%50);
    for(int i=0;i<m;i++) B.push_back(rand()%50);

    for(int i=0;i<m;i++) plus.push_back(B[i]);
    for(int i=0;i<n;i++){
        int flag = 1;
        for(int j=0;j<m;j++){
            if(A[i]==B[j]) { mix.push_back(A[i]); flag=0; }
        } if(flag) plus.push_back(A[i]);
    }

    sort(A.begin(),A.end()); sort(B.begin(),B.end()); 
    sort(plus.begin(),plus.end()); sort(mix.begin(),mix.end());

    cout<<"집합 A - ";
    for(int i=0;i<n;i++){
        if(i!=0) cout<<", ";
        cout<<A[i];
    }
    cout<<endl<<"집합 B - ";
    for(int i=0;i<m;i++){
        if(i!=0) cout<<", ";
        cout<<B[i];
    }
    if(plus.size()==0) cout<<"합집합은 없습니다.";
    else {
        cout<<endl<<"합집합 - ";
        for(int i=0;i<plus.size();i++) {
            if(i!=0) cout<<", ";
            cout<<plus[i];
        }
    }cout<<endl;
    if(mix.size()==0) cout<<"교집합은 없습니다."<<endl;
    else{
        cout<<"교집합 - ";
        for(int i=0;i<mix.size();i++){
            if(i!=0) cout<<", ";
            cout<<mix[i]<<' ';
        }
    }cout<<endl;
}