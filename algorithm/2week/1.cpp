#include <iostream>
using namespace std;

struct treeNode { char info; struct treeNode *l, *r; }; 
treeNode *x, *z;                     // z: 피연산자일 경우 treeNode->l,r가 가리키는 값
typedef treeNode* itemType;          

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

// 노드의 값을 출력하는 함수
void visit(struct treeNode *t) { 
    cout << t->info << " ";
}

//중위 순회 방식이니 왼쪽 자식 -> 중간(부모노드) -> 오른쪽 자식 순으로 값 출력함.
void traverse(struct treeNode *t){ 
    if (t != z){
       traverse(t->l); 
       visit(t);
       traverse(t->r); 
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
        x->l = z; x->r = z;                     // 입력값이 피연산자일 경우 l,r이 z를 가르킴
        if (c == '+' || c == '*' || c == '-'){
            x->r = stack.pop();
            x->l = stack.pop();
        } stack.push(x);
    }
    traverse(stack.pop());
    cout << endl;
    return 0;
}