#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int N; int comp[2], change[2], idx=0; 
itemType *B; 

void shellSort(itemType a[], int n) 
{ 
    int i, j, h; itemType v; 
    h = 1;  do h = 3*h +1; while (h < n); 
    do {
       h = h / 3;
       for (i = h; i < n; i++){ 
          v = a[i]; j = i; 
          while (comp[idx]++ == -1 || a[j-h] > v)  
          { a[j] = a[j-h]; change[idx]++; j -= h;  if (j <= h-1) break; } // h-1 생각해보기 아닌듯? h=1일떄가 있어서
          a[j] = v; if(j!=i)change[idx]++;  //if(j!=i) 있어야하는거 아닌가?
      } 
    } while (h > 1);
}

void sort(itemType **a, int n) 
{
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) { 
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; } 
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) B[i]=a[i][1];
}

int main(){
    cin>>N;
    itemType *A = new itemType[N]; B = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
    srand((unsigned)time(NULL)); 

    for(int i=N;i>0;i--) A[N-i]=i;
    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]=(1+rand()%N);
        tmp[i][1]=i+1;
    } 
    
    sort(tmp, N);
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;
    
    cout<<"Data A: ";
    for(int i=0;i<N;i++){cout<<A[i]<<' ';} cout<<endl;    
    
    cout<<"Data B: ";
    for(int i=0;i<N;i++){cout<<B[i]<<' ';} cout<<endl;
    shellSort(A, N); idx++; shellSort(B, N);
    
    cout<<"SortedData A: ";
    for(int i=0;i<N;i++){cout<<A[i]<<' ';} cout<<endl;
    cout<<"SortedData B: ";

    for(int i=0;i<N;i++){cout<<B[i]<<' ';} cout<<endl;
    cout<<"Compare_Cnt_A " <<comp[0]<< ", DataMove_Cnt_A "<<change[0]<<endl;
    cout<<"Compare_Cnt_B " <<comp[1]<< ", DataMove_Cnt_B "<<change[1]<<endl;
}