#include <iostream>
using namespace std;
struct treeNode { char info; struct treeNode *l, *r; }; 
treeNode *x, *z, *temp;                     // z: 피연산자일 경우 node->l,r가 가리키는 값
typedef treeNode* itemType;          

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
    int head, tail, size;

    public:
    Queue(int max=100) {queue=new itemType[max]; head=tail=0; size=100; };
    void put(itemType v);
    itemType get();
    int empty();
};

Queue queue(100);

void visit(struct treeNode *t) { cout << t->info << " ";} 

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

void traverse(struct treeNode *t) 
{ 
    queue.put(t); 
    while (!queue.empty()) 
    { 
        t = queue.get(); visit(t); 
        if (t->l != z) queue.put(t->l); 
        if (t->r != z) queue.put(t->r); 
    } 
}

int main()
{
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
    traverse(stack.pop());          // 이거 걍 다 만들어져있으니까 traverse만 수정하면됨.
    cout << endl;
    return 0;
}
