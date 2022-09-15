#include <iostream>
#include <cmath>
using namespace std;

typedef double itemType;
class Stack2
{
    public:
       Stack2(){head=z=temp=NULL;}
       ~Stack2(){
        while(z){
            if(z==head) break;
            temp=z->next;
            delete z;
            z=temp;
        }
        delete head;
       }

       void push(itemType v){
        temp=new node; temp->next=z;
        z=temp; z->key=v; 
        if(empty()) head=z;
       }

       itemType pop(){
        temp=z; itemType res = z->key;
        if(z!=head) z=z->next; 
        delete temp;
        return res;
       }

       int empty(){
        if(head) return 0;
        else return 1;
       }

    private:
       struct node 
         { itemType key; struct node *next; };
       struct node *head, *z, *temp;
};

int main()
{
  char c;
  Stack2 acc;
  double x,extra, length, a, b;
  while ((c = cin.get()) != '\n'){
    x = extra = length = 0;
    while (c == ' ')
      cin.get(c);
    if (c == '+')
      x = acc.pop() + acc.pop();
    if (c == '*')
      x = acc.pop() * acc.pop();
    if (c == '-'){ b = acc.pop(); a = acc.pop(); x = a - b;}
    if (c == '/'){ b = acc.pop(); a = acc.pop(); x = a / b;}
    while (c >= '0' && c <= '9'){
      x = 10 * x + (c - '0');
      cin.get(c);
    }
    if(c == '.'){
      cin.get(c);
      while (c >= '0' && c <= '9'){
        extra = 10 * extra + (c - '0');
        length++; cin.get(c);
      } x += (extra/pow(10,length));
    }
    acc.push(x);
  }
  x = acc.pop();
  cout << floor(x*100)/100 << '\n';
}
