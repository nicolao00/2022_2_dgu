#include <iostream>
#include <ctime>
#define infoNIL 0
#define itemMIN -1
typedef int itemType; 
typedef double infoType;

using namespace std;

int N; double comp=0;  // comp: 비교횟수 저장하는 배열
itemType *A; 

void sort(itemType **a, int n){
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) {
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; }
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) A[i]=a[i][1];
}

class BST {
    private:
        struct node { 
            itemType key; infoType info;
            struct node *l, *r;
            node(itemType k, infoType i, struct node *ll, struct node *rr)  // node 생성시 초기값 부여 가능
            { key = k; info = i; l = ll; r = rr; }; 
        }; 
    struct node *head, *z; // z : List의 끝을 대표하는 node pointer – NULL에 해당

    public:
        BST(int max) {
            z = new node( 0, infoNIL, 0, 0);            //infoNIL = 0
            head = new node(itemMIN, infoNIL, z, z);    //itemMIN = 1 infoNIL = 0 
        }
        ~BST(){}
        infoType BSTsearch(itemType v);
        void BSTinsert(itemType v, infoType info);
};

infoType BST::BSTsearch(itemType v) {
     struct node *x = head->r;
     z->key = v;  // 아래 반복문을 간결히 만들기 위함
     while (++comp && v != x->key)  x = (v < x->key) ? x->l : x->r;
     return x->info;
} 

void BST::BSTinsert(itemType v, infoType info) {
     struct node *p, *x;
     p = head; x = head->r;
     while (x != z) { p = x; x = (v < x->key) ? x->l : x->r; }
     x = new node(v, info, z, z);
     if (v < p->key) p->l = x; else p->r = x;
}

int main(){
    cin>>N;
    A = new itemType[N];
    itemType *temp = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
    srand((unsigned)time(NULL)); 
    BST T2(10000);

    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]=1+rand()%N;
        tmp[i][1]=i+1;
    } 
    
    sort(tmp, N); 
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;
    for(int i=0;i<N;i++) T2.BSTinsert(A[i], 0.1);

    for(int i=0;i<N;i++) T2.BSTsearch(A[i]);
    cout<<comp/N; 
}