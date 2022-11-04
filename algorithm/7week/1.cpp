#include <iostream>
#include <ctime>
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
typedef int itemType;
typedef int infoType;
using namespace std;
itemType *A; double comp; double makeComp; int idx=0;


void sort(itemType **a, int n){
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) {
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; }
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) A[i]=a[i][1];
}

class RBT {
    private:
        struct node {
            itemType key, tag; 
            infoType Info; 
            struct node *l, *r; 
            node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) { 
                key = k; Info = i; tag = t; l = ll; r = rr; 
            }
        };
        struct node *head, *tail, *x, *p, *g, *gg, *z;
        struct node *rotate(itemType k, struct node *y) { 
            struct node *high, *low; 
            high = (++makeComp && k < y->key) ? y->l : y->r; // 트리 구축시 키 비교 발생 
            if (++makeComp && k < high->key) { low = high->l; high->l = low->r; low->r = high; } // 트리 구축시 키 비교 발생 
            else { low = high->r; high->r = low->l; low->l = high; } 
            if (++makeComp && k < y->key) y->l = low; else y->r = low; // 트리 구축시 키 비교 발생 
            return low; 
        }

    public:
        RBT(int max) { 
            z = new node(0, infoNIL, black, 0, 0); 
            z->l = z; z->r = z; 
            head = new node(itemMIN, infoNIL, black, z, z); 
        }
        ~RBT(){}
        infoType RBTsearch(itemType v);
        void RBTinsert(itemType v, infoType info);
        void split(itemType k);
};

void RBT::RBTinsert(itemType k, infoType info) { 
    x = head; p = head; g = head; 
    while (x != z) { 
       gg = g; g = p; p = x; 
        x = (++makeComp && k < x->key) ? x->l :  x->r;  // 트리 구축시 키 비교 발생 
        if (x->l->tag && x->r->tag) split(k); 
    } 
    x = new node(k, info, red, z, z); 
    if (++makeComp && k < p->key) p->l = x; else p->r = x;  // 트리 구축시 키 비교 발생 
    split(k); head->r->tag = black; 
} 

void RBT::split(itemType k) { 
    x->tag = red; x->l->tag = black; x->r->tag = black; 
    if (p->tag) { 
        g->tag = red; 
        if (++makeComp && k<g->key != k<p->key) p = rotate(k, g); // 트리 구축시 키 비교 발생 
        x = rotate(k, gg); 
        x->tag = black; 
    } 
}  

infoType RBT::RBTsearch(itemType k) {    
    // Red-Black Tree의 값을 탐색 기능 구현
    struct node *x = head->r;
     z->key = k;  // 아래 반복문을 간결히 만들기 위함
     // 찾으려는 값(k)와 x의 값을 비교 발생  => ++comp
     while (++comp && k != x->key)  x = (k < x->key) ? x->l : x->r;
     return x->Info;
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
        void traverse() { traverse(head->r); }
        void traverse(struct node *t) {
            if (t != z) {
                traverse(t->l);
                A[idx++]=t->key;    // 중위 순회하면서 배열을 재배치 시키는 구문
                traverse(t->r);
            }
        }
};

infoType BST::BSTsearch(itemType v) {
     struct node *x = head->r;
     z->key = v;  // 아래 반복문을 간결히 만들기 위함
     // 찾으려는 값(v)와 x의 값을 비교 발생  => ++comp
     while (++comp && v != x->key)  x = (v < x->key) ? x->l : x->r;
     return x->info;
} 

void BST::BSTinsert(itemType v, infoType info) {
     struct node *p, *x;
     p = head; x = head->r;
     while (x != z) { p = x; x = (++makeComp && v < x->key) ? x->l : x->r; }
     x = new node(v, info, z, z);
     if (++makeComp && v < p->key) p->l = x; else p->r = x;
}


int main(){
    int N; cin>>N;
    A = new itemType[N];
    itemType *temp = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B를 생성하기 위한 이중포인터
    srand((unsigned)time(NULL));

    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]=1+rand()%N;
        tmp[i][1]=i+1;
    }
    
    sort(tmp, N); 
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;

    BST T1(N+1);
    for(int i=0;i<N;i++) T1.BSTinsert(A[i], 0.1);
    cout<<" make compare count\n";
    cout<<"T1: "<<makeComp/N<<endl; makeComp=0;
    T1.traverse(); // 중위 순회하면서 배열을 재배치 시키는 함수 호출

    BST T2(N+1);
    for(int i=0;i<N;i++) T2.BSTinsert(A[i],0.1);
    cout<<"T2: "<<makeComp/N<<endl; makeComp=0;

    RBT T3(N+1);
    for(int i=0;i<N;i++) T3.RBTinsert(A[i],0.1);
    cout<<"T3: "<<makeComp/N<<endl; makeComp=0;

    cout<<"\n serach compare count\n";
    for(int i=0;i<N;i++) T1.BSTsearch(A[i]);
    cout<<"T1: "<<comp/N<<endl; comp=0;
    for(int i=0;i<N;i++) T2.BSTsearch(A[i]);
    cout<<"T2: "<<comp/N<<endl; comp=0;
    for(int i=0;i<N;i++) T3.RBTsearch(A[i]);    
    cout<<"T3: "<<comp/N<<endl; comp=0;
}