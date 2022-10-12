#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 10000
using namespace std;

string word[MAX]; int count[MAX];

void insertion(int n){
    int i, j; int v; string str;
    for (i = 1; i < n; i++){
        v = count[i]; str = word[i]; j = i;
        while ((count[j - 1] < v)){ 
            count[j] = count[j - 1]; 
            word[j] = word[j-1];
            j--; 
            if(j==0) break;
        }
        count[j] = v; word[j] = str;
    }
} // 레벨에 따라 asci 정렬하는 코드 짜야함 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int main(){
    string str; const char* cha; char *tmp; int idx=0;

    ifstream fin;
    fin.open("algorithm\\4week\\datafile.txt");
    if(!fin.is_open()) {cout<<"Error, no such file"<<endl; return -1;} // 파일이 정상적으로 열리지 않았을 경우 오류메시지 출력과함께 종료

    while (getline(fin, str)){                   // fin에 있는 내용 str에 저장
        cha = str.c_str();
        tmp = strtok((char*)cha, " /t/n!\"#$%&'()*+,-./:;<=>?@[\\]^_'{|}~"); // cha의 내용을 단어로 분리하여 tmp에 저장
        while (tmp != NULL){                
            int i;
            for(i=0;i<idx;i++){
                if(word[i]==tmp) {count[i]++; break;}   // 중복단어가 있을 경우, 빈도수++하고 반복문 빠져나감
            }
            // for문을 다 돌았고 마지막 word가 tmp가 아니다 == 중복단어가 없다.
            if(i==idx && word[i-1]!=tmp){string s(tmp); word[idx]=s; count[idx++]++;}
            tmp = strtok(NULL, " /t/n!\"#$%&'()*+,-./:;<=>?@[\\]^_'{|}~");
        }
    }
    for(int i=0;i<idx;i++) cout<<word[i]<<" : "<<count[i]<<endl;
    cout<<endl<<endl<<"SORT"<<endl<<endl;
    insertion(idx);
    for(int i=0;i<idx;i++) cout<<word[i]<<" : "<<count[i]<<endl;
    fin.close();
}