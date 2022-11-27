#include <iostream>
#include <cstring>
using namespace std;

int *SP; // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
const int q = 33554393;
const int d = 26;
char tA[100][100], pA[10][10];

int index(char c)
{
    if (c == ' ') return 0;
    return c - 'A' + 1;
}
void rksearch(char p[10][10], char a[100][100]){
    int dM = 1, h1 = 0, h2 = 0;
    int m = 10, n = 100;
    int count = 0;

    for (int i = 1; i < m*m; i++)
        dM = (d * dM) % q;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            h1 = (h1*d + index(p[i][j])) % q;

    for (int t1 = 0; t1 < n - m + 1; t1++)
        for (int t2 = 0; t2 < n - m + 1; t2++)
        {
            for (int p1 = t1; p1 < m + t1; p1++)
                for (int p2 = t2; p2 < m + t2; p2++)
                    h2 = (h2*d + index(a[p2][p2])) % q;
            count++;

            if (h1 != h2)
                h2 = 0;
        }
    cout << count<<endl;
}

void brutesearch(char p[10][10], char a[100][100]){ // p : Pattern String, a : Text String
       int m = 10, n = 100;
    int flag = 1;
    int count = 0;

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

#include <iostream>
#include <cstring>
using namespace std;

int *SP; // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
const int q = 33554393;
const int d = 26;

void brutesearch(char *p, char *a){ // p : Pattern String, a : Text String
   int i, j, m = strlen(p), n = strlen(a); 
   int count=0, compcnt=0;  // Text String에 존재하는 Pattern String의 개수, 문자열 비교횟수
   for (i = 0; i <= n - m; i++){
      for (j = 0; j < m; j++){
         if (++compcnt && a[i + j] != p[j]) break;
      }
      if (j == m){
         cout<<i<<' '; count++;
      }
   }
   for(count;count<2;count++) cout<<"-1 ";
   cout<<compcnt;
}

int initSP(char *p)
{
   int i, j, m = strlen(p); int compcnt=0;
   SP[0] = -1;
   for (i = 1, j = -1; i <= m - 1; i++) {
      while ((j >= 0) && (p[j + 1] != p[i]))
         j = SP[j];
      if (++compcnt && p[j + 1] == p[i])
         j++;
      SP[i] = j;
   }
   return compcnt;
}

void kmpsearch(char *p, char *a){
   int i, j, m = strlen(p), n = strlen(a);
   int count=0, compcnt=0;
   compcnt+=initSP(p);
   for (i = 0, j = -1; i <= n - 1; i++){
      while ((j >= 0) && ++compcnt && (p[j + 1] != a[i]))
         j = SP[j];
      if (p[j + 1] == a[i])
         j++;
      if (j == m - 1) {
         cout << i-j << " "; count++;// 결과값 출력
         j = SP[j];
      }
   } 
   for(count;count<2;count++) cout<<"-1 ";
   cout<<compcnt;
}

void rksearch(char *p, char *a){
   int i, j, dM = 1, h1 = 0, h2 = 0, flag, count=0, compcnt=0;
   int m = strlen(p), n = strlen(a);
   
   for (i = 1; i < m; i++)
      dM = (d * dM) % q;
   
   for (i = 0; i < m; i++){
      h1 = (h1 * d + p[i]) % q;
      h2 = (h2 * d + a[i]) % q;
   }
   
   for (i = 0; i < n - m + 1; i++){
      ++compcnt;
      if (h1 == h2){
         flag = 1;
         for (j = i; j < m; j++)
         ++compcnt;
            if (a[j] != p[j - i]) {
               flag = 0;
               break;
            }
      }
      if (flag) // 결과값 출력
         cout << i << " "; count++;
         flag = 0;
         if (j < n - m){
            h2 = (h2 - a[i] * dM) % q;
            if(h2 < 0) h2 = h2%q + q;
            h2 = (h2 * d + a[i + m]) % q;
         }
   }
   for(count;count<2;count++) cout<<"-1 ";
   cout<<compcnt;
}

int main(){
   string textStr, patterStr;
   getline(cin,textStr);
   getline(cin,patterStr);

   SP=new int[patterStr.length()];
   char *tA=new char[textStr.length()];
   char *pA=new char[patterStr.length()];
   for(int i=0;i<textStr.length();i++) tA[i]=textStr[i];
   for(int i=0;i<patterStr.length();i++) pA[i]=patterStr[i];
   brutesearch(pA, tA); cout<<" Brute-Force."<<endl;
   kmpsearch(pA, tA); cout<<" KMP."<<endl;
   rksearch(pA, tA); cout<<" Rabin-Karp."<<endl;
}