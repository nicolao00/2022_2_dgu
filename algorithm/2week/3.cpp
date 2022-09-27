#include <iostream>
using namespace std;
struct treeNode { char info; struct treeNode *l, *r; }; 
treeNode *x, *z;                     // z: 피연산자일 경우 node->l,r가 가리키는 값
typedef treeNode* itemType;          

char findChar;          // 찾고자 하는 피연산자(입력값)

class Stack{
    public:
        Stack(int max=100) { stack=new itemType[max]; p=0; };
        ~Stack(){ delete stack; }

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
    int head, tail, size, nowLv; // nowLv: 현재 트리의 레벨 

    public:
    Queue(int max=100) {queue=new itemType[max]; head=tail=0; size=100; nowLv=1;};
    void put(itemType v);
    itemType get();
    int empty();
    void upLv() {nowLv++;}      // 트리의 레벨 +1
    void getLv() {cout << nowLv + 1 << endl;}     // 트리 레벨 반환 (자식노드가 찾는 값과 일치하는지 찾는 용도로 쓰이니 LV+1 해서 출력)
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
    
    //idx: 해당 레벨의 노드 개수 (올바른 트리의 첫노드는 연산자로 시작하기 때문에 idx 1로 시작)
    int idx=1, nextidx=0;      //nextidx: 다음 레벨의 큐 개수를 카운트하는 변수
    while (!queue.empty()){ 
        t = queue.get(); idx--;
        if (t->l != z) {
            if(t->l->info == findChar) {queue.getLv(); return;}
            queue.put(t->l); nextidx++; // 다음 레벨의 노드를 큐에 put했으니 nextidx++
        }
        if (t->r != z) {
            if(t->r->info == findChar) {queue.getLv(); return;}
            queue.put(t->r); nextidx++;
        }

        if(idx==0) {    //idx == 0 이란건 해당 레벨은 모두 순회한 것. 
            queue.upLv();
            idx = nextidx;
            nextidx=0;
        }
    } cout<<"Not Found"<<endl;  // 찾는 값을 못찾으면 출력
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
    if(findChar<'A'|| findChar>'Z') return 0;   // 찾는 값이 영문 대문자가 아닐 경우 종료
    traverse(stack.pop());      
    cout << endl;
    return 0;
}