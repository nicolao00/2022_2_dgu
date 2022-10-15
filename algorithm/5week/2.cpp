#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int N; int comp[3], change[3], idx;  // comp: 비교횟수 저장하는 배열(idx==0:A/1:B/2:C), change: 자료이동 횟수
itemType *A, *B, *C; 

void sort(itemType **a, int n){
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) { 
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; } 
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) B[i]=a[i][1];
}
// a: 정렬 안된 배열 / b: 정렬된 배열이 저장될 곳 / n: A의 원소개수 / k: a의 최대값
void CountSort(itemType *a, itemType *b, int n, int k) {
    itemType *N = new itemType[k + 1]; // N: 숫자별로 횟수 적는칸
    int i, j;
    for (i = 1; i <= k; i++) N[i] = 0;
    for (i = 0; i < n; i++) N[a[i]] = N[a[i]] + 1;
    for (i = 2; i <= k; i++) N[i] = N[i] + N[i - 1];
    for (j = n - 1; j >= 0; j--){
        b[N[a[j]]] = a[j];       change[idx]++;
        N[a[j]] = N[a[j]] - 1;
    }
    for (int i = 0; i < n; i++) a[i] = b[i];
    delete[] N;
}

int main(){
    cin>>N;
    A = new itemType[N]; B = new itemType[N]; C = new itemType[N]; 
    itemType *temp = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
    srand((unsigned)time(NULL)); 

    for(int i=N;i>0;i--) A[N-i]=i;
    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]= C[i] = (1+rand()%N);
        tmp[i][1]=i+1;
    } 
    
    sort(tmp, N); 
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;

    int max=0;
    for(int i=0;i<N;i++){
        if(max < C[i]) max=C[i];
    }

    CountSort(A, temp, N, N); idx++;
    CountSort(B, temp, N, N); idx++;
    CountSort(C, temp, N, max);
    
    cout<<"SortedData A: ";
    for(int i=1;i<=20;i++){cout<<A[i]<<' ';} cout<<endl;
    cout<<"SortedData B: ";
    for(int i=1;i<=20;i++){cout<<B[i]<<' ';} cout<<endl;
    cout<<"SortedData C: ";
    for(int i=1;i<=20;i++){cout<<C[i]<<' ';} cout<<endl;
    cout<<"Compare_Cnt_A " <<comp[0]<< ", DataMove_Cnt_A "<<change[0]<<endl;
    cout<<"Compare_Cnt_B " <<comp[1]<< ", DataMove_Cnt_B "<<change[1]<<endl;
    cout<<"Compare_Cnt_C " <<comp[2]<< ", DataMove_Cnt_C "<<change[2]<<endl;
}