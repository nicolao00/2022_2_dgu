#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;
typedef struct node *node_pointer; 
typedef struct node {
      itemType value; 
      node_pointer next;
};
node_pointer TABLE[10], x, z, temp;

int N; int comp[3], change[3], idx;  // comp: 비교횟수 저장하는 배열(idx==0:A/1:B/2:C), change: 자료이동 횟수
itemType *A, *B, *C; 

void radixSort(itemType *a, int n) {
      int i,j, cnt, radix, radix_mod =10, cipher=0; 
      i=n; 
      while(i>0) { i=i/10; cipher++; } // cipher : 입력 데이터의 자리수 (ex. 450 -> 3)
      for(i=0; i<cipher; i++) {
            for(j=0; j<n; j++) {
                  cnt=0; radix = (a[j]%radix_mod)/(radix_mod/10); 
                          /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수
                         radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
                  temp = new node; temp->value = a[j]; temp->next = z;  change[idx]++;
                  if(TABLE[radix] == z) {       // table의 radix 인덱스에 값이 하나도 없을때
                          // z는 list의 끝을 확인하기 위한 노드 포인터 (NULL에 해당)
                        TABLE[radix]=temp;   
                  } else {
                        x=TABLE[radix]; 
                        while(x->next != z) {   // table의 radix 인덱스에 값이 있어서 맨 마지막 값으로 이동하는 과정
                              x=x->next;  
                        }
                        x->next=temp;      
                  }
            } // 여기까지가 버킷에 값들을 넣는 과정

            for(j=0; j<10; j++) {
                  if(TABLE[j]!=z) {
                        x=TABLE[j]; 
                        while(x!=z) {
                              a[cnt++] = x->value;      change[idx]++;
                              temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
                              x=x->next; 
                                             delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
                        }
                  }
                  TABLE[j]=z; 
            }
            radix_mod*=10; 
      }
}

void sort(itemType **a, int n){
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

    radixSort(A, N); idx++;
    radixSort(B, N); idx++;
    radixSort(C, N);
    
    cout<<"SortedData A: ";
    for(int i=0;i<20;i++){cout<<A[i]<<' ';} cout<<endl;
    cout<<"SortedData B: ";
    for(int i=0;i<20;i++){cout<<B[i]<<' ';} cout<<endl;
    cout<<"SortedData C: ";
    for(int i=0;i<20;i++){cout<<C[i]<<' ';} cout<<endl;
    cout<<"Compare_Cnt_A " <<comp[0]<< ", DataMove_Cnt_A "<<change[0]<<endl;
    cout<<"Compare_Cnt_B " <<comp[1]<< ", DataMove_Cnt_B "<<change[1]<<endl;
    cout<<"Compare_Cnt_C " <<comp[2]<< ", DataMove_Cnt_C "<<change[2]<<endl;
}