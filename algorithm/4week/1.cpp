#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int N; int comp[2], change[2], idx;  // comp: 비교횟수 저장하는 배열(idx=0: A 1: B), change: 자료이동 횟수
itemType *B; 

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

// 스왑함수 호출될때마다 3번의 자료이동 발생
inline void swap(itemType a[], int i, int j) 
  { itemType  t = a[i]; a[i] = a[j]; a[j] = t; change[idx]+=3; } 
  
int partition(itemType a[], int l, int r) { 
    int i, j; itemType v; 
    if (r > l) { 
       v = a[l]; i = l; j = r+1;
       for (;;) { 
          while (++i <= r && ++comp[idx] && a[i] < v) ; // 비교연산 발생 맨앞조건 확인해볼것!!
          while (--j > l && ++comp[idx] && a[j] > v) ; // 비교연산 발생 맨앞조건 확인해볼것!!
          if (i >= j) break; 
             swap(a, i, j); 
       } 
       swap(a, j, l); 
    }
    return j;
}

void quicksort(itemType a[], int l, int r) { 
    int  j; 
    if (r > l) {
       j = partition(a, l, r);
       quicksort(a, l, j-1); 
       quicksort(a, j+1, r); 
    } 
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

    quicksort(A, 0, N-1); idx++; quicksort(B, 0, N-1);
    
    cout<<"SortedData A: ";
    for(int i=0;i<20;i++){cout<<A[i]<<' ';} cout<<endl;
    cout<<"SortedData B: ";
    for(int i=0;i<20;i++){cout<<B[i]<<' ';} cout<<endl;
    cout<<"Compare_Cnt_A " <<comp[0]<< ", DataMove_Cnt_A "<<change[0]<<endl;
    cout<<"Compare_Cnt_B " <<comp[1]<< ", DataMove_Cnt_B "<<change[1]<<endl;
}