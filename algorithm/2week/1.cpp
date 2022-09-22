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

void visit(struct treeNode *t) { 
    cout << t->info << " ";
} 
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
        x->l = z; x->r = z;                     // 피연산자일 경우 l,r이 z를 가르킴
        if (c == '+' || c == '*' || c == '-'){
            x->r = stack.pop();
            x->l = stack.pop();
        } stack.push(x);
    }
    traverse(stack.pop());
    cout << endl;
    return 0;
}