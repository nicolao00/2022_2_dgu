#include <iostream>
#include <ctime>
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
typedef int itemType;
typedef int infoType;
using namespace std;
itemType *A; double comp; double makeComp;

void sort(itemType **a, int n){
    int i, j; itemType v, v2;
    for (i = 1; i < n; i++) {
       v = a[i][0]; v2 = a[i][1]; j = i; 
       while (j>0 && a[j-1][0] > v) { a[j][0] = a[j-1][0]; a[j][1] = a[j-1][1]; j--; }
       a[j][0] = v; a[j][1]=v2;
    }
    for(int i=0;i<n;i++) A[i]=a[i][1];
}

typedef struct Node{
    int value;
    int flag;   // flag�� 1�̸� ������ ��� ����ִ°�(hashtable �����ڿ��� �Ҵ��� ��������)
    Node *next;
} Node;


class Hashtable{
    Node *link;
    int M;

public:
    Hashtable(int M){
        link = new Node[M]; // �����Ҵ�� ���ÿ� �ʱ�ȭ
        for(int i=0;i<M;i++){
            link[i].flag=-1; link[i].next=NULL;
        }
        this->M = M;
    }
    ~Hashtable() { delete[] link; }
    
    int function(int value) { return value % M; }

    int pushNode(int value) {
        int key = function(value);
        Node *exNode=NULL, *curNode = &link[key]; //&link[key] �ص��ǳ�?
        // ���̸� �̹� table[key]�� ��� ����
        if (link[key].flag == 0){
            while(curNode){
                exNode=curNode;
                curNode=curNode->next;
            } 
            Node *newNode = new Node();
            newNode->value=value; newNode->next=NULL;
            exNode->next=newNode;
        }
        else {
            link[key].value=value; 
            link[key].flag=0;
            link[key].next = NULL;
        }
    }

    int searchNode(int value){
        int key=function(value);
        Node *curNode= &link[key];
        while(curNode->flag == 0 && curNode){
            if(++comp && curNode->value==value) return curNode->value;
            else curNode=curNode->next;
        }
        cout<<"no search Node"; return -1;
    }
};

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
            high = (++makeComp && k < y->key) ? y->l : y->r;  
            if (++makeComp && k < high->key) { low = high->l; high->l = low->r; low->r = high; } 
            else { low = high->r; high->r = low->l; low->l = high; } 
            if (++makeComp && k < y->key) y->l = low; else y->r = low; 
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
        x = (++makeComp && k < x->key) ? x->l :  x->r;  // ���
        if (x->l->tag && x->r->tag) split(k); 
    } 
    x = new node(k, info, red, z, z); 
    if (++makeComp && k < p->key) p->l = x; else p->r = x;  // ���
    split(k); head->r->tag = black; 
} 

void RBT::split(itemType k) { 
    x->tag = red; x->l->tag = black; x->r->tag = black; 
    if (p->tag) { 
        g->tag = red; 
        if (++makeComp && k<g->key != k<p->key) p = rotate(k, g); 
        x = rotate(k, gg); 
        x->tag = black; 
    } 
}  

infoType RBT::RBTsearch(itemType k) {    
    // Red-Black Tree�� ���� Ž�� ��� ����
    struct node *x = head->r;
     z->key = k;  // �Ʒ� �ݺ����� ������ ����� ����
     // ã������ ��(v)�� x�� ���� �� �߻�  => ++comp
     while (++comp && k != x->key)  x = (k < x->key) ? x->l : x->r;
     return x->Info;
}

int main(){
    int N; cin>>N;
    A = new itemType[N];
    itemType *temp = new itemType[N]; itemType **tmp = new itemType*[N];   //tmp : B�� �����ϱ� ���� ����������
    srand((unsigned)time(NULL));

    for(int i=0;i<N;i++){
        tmp[i]=new int[2];
        tmp[i][0]=1+rand()%N;
        tmp[i][1]=i+1;
    }
    
    sort(tmp, N); 
    for(int i=0; i<N; i++) delete[] tmp[i];
    delete[] tmp;

    RBT T3(N+1);
    for(int i=0;i<N;i++) T3.RBTinsert(A[i],0.1);
    cout<<"( T3�� ���� �� ��� �� Ƚ��) "<<makeComp/N<<endl; makeComp=0;

    Hashtable Ht1(11);
    for(int i=0;i<N;i++) Ht1.pushNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 11�� ����� ���� �� ��� �� Ƚ��) "<<makeComp/N<<endl; makeComp=0;

    Hashtable Ht2(101);
    for(int i=0;i<N;i++) Ht2.pushNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 101�� ����� ���� �� ��� �� Ƚ��) "<<makeComp/N<<endl; makeComp=0;

    Hashtable Ht3(1009);
    for(int i=0;i<N;i++) Ht3.pushNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 1009�� ����� ���� �� ��� �� Ƚ��) "<<makeComp/N<<endl; makeComp=0;


    for(int i=0;i<N;i++) T3.RBTsearch(A[i]);
    cout<<endl<<"( T3�� ��� �� Ƚ��) "<<comp/N<<endl; comp=0;

    for(int i=0;i<N;i++) Ht1.searchNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 11�� ����� ��� �� Ƚ��) "<<comp/N<<endl; comp=0;

    for(int i=0;i<N;i++) Ht2.searchNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 101�� ����� ��� �� Ƚ��) "<<comp/N<<endl; comp=0;

    for(int i=0;i<N;i++) Ht3.searchNode(A[i]);
    cout<<"( Hash Table ũ�Ⱑ 1009�� ����� ��� �� Ƚ��) "<<comp/N<<endl; comp=0;
}