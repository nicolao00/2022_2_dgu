#include <iostream>
using namespace std;
struct treeNode { char info; struct treeNode *l, *r; }; 
treeNode *x, *z, *temp;                     // z: 피연산자일 경우 node->l,r가 가리키는 값
typedef treeNode* itemType;          

char findChar;

class Stack{
    public:
        Stack(int max=100) { stack=new itemType[max]; p=0; };
        //lab1 참조
        // ~Stack() {
        //     for(int i=0;i<50;i++){
        //         x=pop(); delete x->l; delete x->r;
        //         while(x->l){
        //             temp=x->l;
        //         }
        //         delete x;           // 이거되나근데????????????????????????
        //     }
        // } 

        inline void push(itemType v) { stack[p++] = v; }
        inline itemType pop() {
            if(!empty()) return stack[--p];
            else return NULL;
        } 
        inline int empty() { return !p; }

    private:
       itemType *stack;
       int p;
};

class Queue{
    private:
    itemType *queue;
    int head, tail, size,                   nowLv;

    public:
    Queue(int max=100) {queue=new itemType[max]; head=tail=0; size=100;         nowLv=1;};
    void put(itemType v);
    itemType get();
    int empty();
    void upLv() {nowLv++;} ///////////
    void getLv() {cout<<nowLv+1<<endl;}
};

Queue queue(100);

void Queue::put(itemType v){ 
    queue[tail++] = v; 
    if (tail > size) tail = 0; 
} 

itemType Queue::get(){ 
    itemType t = queue[head++]; 
    if (head > size) head = 0; 
    return t; 
} 

int Queue::empty() { return head == tail; }

void traverse(struct treeNode *t) {
    queue.put(t); 
    
    int idx=1, bothOp=0;      // 트리의 첫노드는 무조건 연산자라 idx 1로 시작, bothOp=자식노드가 모두 Op냐?
    while (!queue.empty()){ 
        t = queue.get(); idx--;
        if (t->l != z) {
            if(t->l->info == findChar) {queue.getLv(); return;}
            queue.put(t->l); 
        }
        if (t->r != z) {
            if(t->r->info == findChar) {queue.getLv(); return;}
            queue.put(t->r); 
        }
        if (t->l != z && t->r != z) bothOp++;   // 자식이 두개면 피연산자란 말이니 bothOp++함. 그래서 bothOp가 2가되면 부모가 모두 연산자란 말.
        if(idx==0) {
            queue.upLv();
            if(bothOp==2) idx=2+bothOp;      // 트리의 노드는 무조건 2개인데 자식노드 둘다 연산자였을 경우는 +2개
            else idx=2;
            bothOp=0;
        }
    } cout<<"Not Found"<<endl;
}

int main(){
    char c;
    Stack stack(50);
    z = new treeNode;
    z->l = z; z->r = z;
    while ((c = cin.get()) != '\n')
    {
        while (c == ' ') cin.get(c);
        x = new treeNode;
        x->info = c;
        x->l = z; x->r = z;                     // 피연산자일 경우 l,r이 z를 가르킴
        if (c == '+' || c == '*' || c == '-'){
            x->r = stack.pop();
            x->l = stack.pop();
        } stack.push(x);
    } 
    findChar=cin.get();
    traverse(stack.pop());          // 이거 걍 다 만들어져있으니까 traverse만 수정하면됨.
    cout << endl;
    return 0;
}