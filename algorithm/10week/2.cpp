#include <iostream>
#include <cstring>
using namespace std;

int *SP; // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
const int q = 33554393;
const int d = 26;
char tA[100][100], pA[10][10];

void rksearch(char p[10][10], char a[100][100]){
    int dM = 1, h1 = 0, h2 = 0, m = 10, n = 100;
    int count = 0;

    for (int i = 1; i < m*m; i++)
        dM = (d * dM) % q;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            h1 = (h1*d + p[i][j]) % q;

    for (int i = 0; i < n - m + 1; i++)
        for (int j = 0; j < n - m + 1; j++)
        {
            for (int p1 = i; p1 < m + i; p1++)
                for (int p2 = j; p2 < m + j; p2++)
                    h2 = (h2*d + a[p2][p2]) % q;
            count++;
            if (h1 != h2) h2 = 0;
        }
    cout << count<<endl;
}

void brutesearch(char p[10][10], char a[100][100]){ // p : Pattern String, a : Text String
    int m = 10, n = 100;
    int flag = 1, count = 0;

    for (int i = 0; i < n - m + 1; i++) {
        for (int j = 0; j < n - m + 1; j++) {
            for (int k = 0, flag = 1; k < m && flag==1; k++) {
                for (int s = 0; s < m && flag==1; s++) {
                    count++;
                    if (p[k][s] != a[i + k][j + s])
                        flag = 0;
                }
            }
        }
    }
    cout << count<<endl;
}

int main(){
   for(int i=0; i<100; i++) memset(tA[i], 'A', sizeof(int)*100);
   for(int i=0; i<10; i++) memset(pA[i], 'A', sizeof(int)*10); pA[9][9]='B';
   brutesearch(pA, tA);
   rksearch(pA, tA);
}