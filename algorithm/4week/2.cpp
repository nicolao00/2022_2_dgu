#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int N; int comp[2], change[2], idx;  // comp: 비교횟수 저장하는 배열(idx=0: A 1: B), change: 자료이동 횟수
itemType *B, *sorted; 

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

void merge(itemType a[], int l, int mid, int r) {
      int i,j,k,n; 
      i=l; j=mid+1; k=l; 
      while (i<=mid && j<=r) { 
            if (comp[idx]++ == -1 || a[i] <= a[j]) {
                  sorted[k++] = a[i++]; change[idx]++;
             } else { 
                   sorted[k++] = a[j++]; change[idx]++;
            } 
       } 
       if (i>mid) 
            for (n=j; n<=r; n++){ sorted[k++] = a[n]; change[idx]++;}
       else 
            for (n=i; n<=mid; n++){ sorted[k++] = a[n]; change[idx]++;}
       for (n=l; n<=r; n++) { a[n] = sorted[n]; change[idx]++;}
}

void mergesort(itemType a[], int l, int r) { 
       int mid; 
       if (l < r) { 
             mid = ( l + r)/2; 
             mergesort(a, l, mid);
             mergesort(a, mid+1, r);
             merge(a, l, mid, r); 
       } 
}

int main(){
    cin>>N;
    itemType *A = new itemType[N]; B = new itemType[N]; sorted=new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
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

    mergesort(A, 0, N-1); idx++; mergesort(B, 0, N-1);
    
    cout<<"SortedData A: ";
    for(int i=0;i<20;i++){cout<<A[i]<<' ';} cout<<endl;
    cout<<"SortedData B: ";
    for(int i=0;i<20;i++){cout<<B[i]<<' ';} cout<<endl;
    cout<<"Compare_Cnt_A " <<comp[0]<< ", DataMove_Cnt_A "<<change[0]<<endl;
    cout<<"Compare_Cnt_B " <<comp[1]<< ", DataMove_Cnt_B "<<change[1]<<endl;
}