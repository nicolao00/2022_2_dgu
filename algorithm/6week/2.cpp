#include <iostream>
#include <ctime>
#define infoNIL 0
#define itemMIN -1
typedef int itemType; 
typedef double infoType;

using namespace std;

int N; double comp=0;  // N: 자료의 크기 comp: 비교횟수 저장하는 변수
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
        void BSTdelete(itemType v);
};

void BST::BSTinsert(itemType v, infoType info) {
     struct node *p, *x;
     p = head; x = head->r;
     while (x != z) { p = x; x = (v < x->key) ? x->l : x->r; }
     x = new node(v, info, z, z);
     if (v < p->key) p->l = x; else p->r = x;
}

void BST::BSTdelete(itemType v) {
     // p: 삭제할 노드의 전 노드가 들어가있음, t: 삭제하려는 주소 저장, c: 
     struct node *x = head->r, *p, *t, *c;
     p=head;
     while (x!=z && ++comp && x->key !=v)  {
          p=x; 
          x = (v < x->key) ? x->l : x->r; 
     }
     if(x==z) return;           // 찾는 값이 없는 경우 종료
     else t=x;                  // x에는 삭제하려는 주소 있음

     if(t->r == z) x=t->l;      // 삭제하려는 주소의 오른쪽 자식이 비어 있으면 x=t->l
     else if(t->r->l == z) {    // 삭제하려는 주소의 오른쪽 자식 존재하고 그 왼쪽 자식이 비어있을때
          x=t->r; x->l = t->l; 
     }
     else {
          c=x->r; while(c->l->l !=z) c=c->l;
          x=c->l; c->l = x->r;
          x->l=t->l; x->r=t->r;
     }
     delete t; 
     if(++comp && v<p->key) p->l=x; else p->r=x;
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
    // A배열의 데이터를 순서대로 10개씩 불러들인뒤, 그중 한개를 랜덤하게 골라 삭제하는 과정
    for(int i=0;i<N/10;i++) T2.BSTdelete(A[i*10 + rand()%9]); 
    // 평균비교회수 = 자료탐색을 위한 키의 비교회수 합계 / 전체 자료수
    cout<<comp/((double)N/10)<<endl; 
}