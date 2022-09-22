#include <iostream>
#include <cmath>
using namespace std;

//사용자 정의형 itemType 를 double로 설정.
typedef double itemType;
class Stack2
{
    public:
    // 생성자: 사용할 node 포인터들을 모두 널포인터로 초기화.
       Stack2(){head=z=temp=NULL;}
       //소멸자: stack에서 top의 역할인 z부터 시작하여 head까지 delete해준다.
       ~Stack2(){
        while(z){
            if(z==head) break;
            temp=z->next;
            delete z;
            z=temp;
        }
        delete head;
       }

      // Push함수: 새로운 node를 생성하여 temp에 저장한다. Temp->next에 top에 해당하는 z를 넣고,
      // key값에는 매개변수로 받은 v를 저장한뒤 z에 temp를 넣는다. 
      // 이 과정에서 head가 비어있는 경우에 head에 z를 넣어준다.
       void push(itemType v){
        temp=new node; temp->next=z; temp->key=v; 
        z=temp; 
        if(empty()) head=z;
       }

      //  Pop 함수: temp에 z를 저장한뒤 반환할 key 값을 res변수에 저장해둔다.
      //  만약 z가 헤드가 아닐 경우에 z=z->next를 해주어 z값이 top역할을 유지할 수 있도록 해준다.
      //  그 후 temp를 delete 해준 후 res 값을 반환한다.
       itemType pop(){
        temp=z; itemType res = z->key;
        if(z!=head) z=z->next; 
        delete temp;
        return res;
       }

       // head가 비어있을 경우 0 차있을경우 1반환
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

    // 2번문제와 달리 소수도 처리해야하기때문에 소수점 부분만 따로 처리하는 과정
    if(c == '.'){
      cin.get(c);
      while (c >= '0' && c <= '9'){
        extra = 10 * extra + (c - '0'); //extra는 위쪽 x와 같은 역할
        length++; cin.get(c);           //length는 10제곱할 때 쓰이는 지수 역할
      } x += (extra/pow(10,length));
    }
    acc.push(x);
  }
  x = acc.pop();
  cout << floor(x*100)/100 << '\n'; // 출력값은 소수점 둘째자리까지 출력해야해서 둘째자리 이후는 버림
}
