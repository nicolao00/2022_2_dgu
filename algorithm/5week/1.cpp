#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int N; int comp[3], change[3], idx;  // comp: 비교횟수 저장하는 배열(idx==0:A/1:B/2:C), change: 자료이동 횟수
itemType *B; 

void sort(itemType **a, int n){
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) { 
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; } 
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) B[i]=a[i][1];
}

class MAKE_HEAP{
private:
    itemType *a;
    int N;
public:
    MAKE_HEAP(int max){
        a = new itemType[max];
        N = 0;
    }
    ~MAKE_HEAP() { delete a; }
    void swap(itemType a[], int i, int j) {
        int temp;
        temp = a[j];    change[idx]++;
        a[j] = a[i];    change[idx]++;
        a[i] = temp;    change[idx]++;
    }

    void MakeHeap(itemType a[], int Root, int LastNode){
        int Parent, LeftSon, RightSon, Son;
        itemType RootValue;
        Parent = Root;
        RootValue = a[Root];    change[idx]++;
        LeftSon = 2 * Parent + 1;               //왜 2*Parent아니고?
        RightSon = LeftSon + 1;
        while (LeftSon <= LastNode){    // 왜 등호를 안붙이면 이상하게 나올까
            // 마지막 노드가 오른쪽 자식보다 크거나 같고, 오른쪽 자식이 왼쪽 자식보다 커
            if (++comp[idx] && RightSon <= LastNode && a[LeftSon] < a[RightSon])
                Son = RightSon;
            else Son = LeftSon;
            //  부모값이 자식값보다 작다
            if (++comp[idx] && RootValue < a[Son]){
                a[Parent] = a[Son];     change[idx]++;
                Parent = Son;
                LeftSon = Parent * 2 + 1;
                RightSon = LeftSon + 1;
            }
            else break;
        }
        a[Parent] = RootValue;  change[idx]++;
    }

    void heapsort(itemType a[], int N){
        int i;
        for (i = N / 2; i >= 0; i--) MakeHeap(a, i, N - 1);     // >=0 이여야하는 이유 1이아니라
        for (i = N - 1; i >= 1; i--){
            swap(a, 0, i);
            MakeHeap(a, 0, i - 1);
        }
    }
};

int main(){
    cin>>N;
    itemType *A = new itemType[N]; B = new itemType[N]; 
    itemType *C = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
    srand((unsigned)time(NULL)); 

    MAKE_HEAP hp(30000);

    for(int i=N;i>0;i--) A[N-i]=i;
    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]= C[i] = (1+rand()%N);
        tmp[i][1]=i+1;
    } 
    
    sort(tmp, N); 
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;

    hp.heapsort(A, N); idx++; 
    hp.heapsort(B, N); idx++; 
    hp.heapsort(C, N);
    
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