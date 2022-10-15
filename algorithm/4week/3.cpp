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
}

void strinsertion(int n){
    int i, j; string str; int level;
    for (i = 1; i < n; i++){
        str = word[i]; j = i; level=count[i];
        while (strcmp(word[j-1].c_str(), str.c_str()) > 0 && count[j-1] == level){
            word[j] = word[j-1];
            j--; 
            if(j==0) break;
        }
        word[j] = str;
    }
}

int main(){
    string str; const char* cha; char *tmp; int idx=0;

    ifstream fin;
    fin.open("algorithm\\4week\\datafile.txt");
    if(!fin.is_open()) {cout<<"Error, no such file"<<endl; return -1;} // ������ ���������� ������ �ʾ��� ��� �����޽��� ��°��Բ� ����

    while (getline(fin, str)){                   // fin�� �ִ� ���� str�� ����
        cha = str.c_str();
    
        tmp = strtok((char*)cha, " \t\n\v\f\r!\"#$%&'()*+,-./:;<=>?@[\\]^_'{|}~"); // cha�� ������ �ܾ�� �и��Ͽ� tmp�� ����
        while (tmp != NULL){                
            int i;
            for(i=0;i<idx;i++){
                if(word[i]==tmp) {count[i]++; break;}   // �ߺ��ܾ ���� ���, �󵵼�++�ϰ� �ݺ��� ��������
            }
            // for���� �� ���Ұ� ������ word�� tmp�� �ƴϴ� == �ߺ��ܾ ����.
            if(i==idx && word[i-1]!=tmp){string s(tmp); word[idx]=s; count[idx++]++;}
            tmp = strtok(NULL, " \t\n\v\f\r!\"#$%&'()*+,-./:;<=>?@[\\]^_'{|}~");
        }
    }
    insertion(idx); strinsertion(idx);
    for(int i=0;i<idx;i++) cout<<word[i]<<" : "<<count[i]<<endl;
    fin.close();
}