#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 500; // 버켓의 총 길이
ifstream fin; ofstream fout; int locctr; // fin:SRCFILE / fout: INTFILE
ifstream fop; ofstream symtab; 

//String을 해쉬테이블의 key로 사용하므로 문자열의 아스키값을 다 더한값을 씀.
int make_key(string str){
    int key=0;
    for(int i=0;i<str.length();i++) key+=str[i];
    return key;
}

// 노드 구조체 선언
struct node {
    string label;       // 해시 함수에 사용될 키(라벨)
    int address;        // symbol의 주소
    int flag;           // 오류 flag
    struct node* next; // 다음 노드를 가르키는 포인터
};

// 버켓 구조체 선언
struct bucket{
    struct node* head;  // 버켓 가장 앞에 있는 노드의 포인터
    int count;          // 버켓에 들어있는 노드의 개수
};

// 해쉬테이블 삽입될 때 새로 노드를 생성해주는 함수(초기화)
struct node* createNode(string label, int address, int flag){
    struct node* newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    
    newNode->label = label;
    newNode->address = address;
    newNode->flag = flag;
    newNode->next = NULL;

    return newNode;
}

// 해쉬함수 만들기. 여기서는 단순히 key를 버켓 길이로 나눈 나머지로 함수를 만듦.
int hashFunction(int key){
    return key%BUCKET_SIZE;
}

// 새로 키 추가하는 함수
void add(string label, int address, int flag){
    // 어느 버켓에 추가할지 인덱스를 계산
    int hashIndex = hashFunction(make_key(label));
    
    struct node* newNode = createNode(label, address, flag);
    // 계산한 인덱스의 버켓에 아무 노드도 없을 경우
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; // head를 교체
    }
    // 버켓에 다른 노드가 있을 경우 한칸씩 밀고 내가 헤드가 된다(실제로는 포인터만 바꿔줌)
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

// 키를 주고 존재하면 flag=1로 처리
void fixFlag(string label){
    int hashIndex = hashFunction(make_key(label));
    struct node* node = hashTable[hashIndex].head;
    int flag = 0;
    while (node != NULL){
        if (node->label == label){
            node->flag=1;
            break;
        }
        node = node->next;
    }
}
// 키값에 해당하는 노드가 존재하는지 탐색
int is_exist(string label){
    int hashIndex = hashFunction(make_key(label));
    struct node* node = hashTable[hashIndex].head;
    int flag = 0;
    while (node != NULL){
        if (node->label == label){
            flag=1;
            break;
        }
        node = node->next;
    }
    if(flag==1) return 1; // 값을 찾았다면
    else return 0;
}

// 키로 노드를 찾아서 symtab에 넣어주는 함수
void search(string label){
    int hashIndex = hashFunction(make_key(label));
    struct node* node = hashTable[hashIndex].head;
    while (node != NULL){
        if (node->label == label){
            symtab << node->label <<"    "<< hex<< node->address<<"    " << node->flag<<endl;
            break;
        }
        node = node->next;
    }
}

// search OPTAB for OPCODE 하는 과정 (리턴값은 Locctr에 더할 값)
int search_op(string str, string operand){
    ifstream opin("Optab.txt"); 
    string opstr; int result=0;
    while(getline(opin, opstr)){
        if(str=="word") { result = 3; break;}
        else if(str=="resw") { result = 3 * stoi(operand); break;}
        else if(str=="resb") { result = stoi(operand); break;}
        else if(str=="byte") { result = operand.length()-3; break;}
        else if(opstr.find(str) != string::npos) { result = 3; break;}
    } 
    opin.close(); return result;    // optab에서 opcode를 못찾았을때 0 반환
}

int main(int argc, char *argv[]){
    if (argc == 3){
        fin.open(argv[1]); fout.open(argv[2]); 
        fop.open("Optab.txt"); symtab.open("Symtab.txt");
        hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
        locctr=0; string srcStr, label, opcode, oper;

        if (!fin.is_open() || !fout.is_open() || !fop.is_open() || !symtab.is_open()){
            cout << "Error, no such file" << endl;
            return -1;
        }

        getline(fin, srcStr);
        if(srcStr.find("start") != string::npos){
            string oper = srcStr.substr(17, 18);
            locctr=stoi(oper, nullptr, 16);

            string line = srcStr.substr(0,35);
            fout << line.append(oper)<<endl;
            getline(fin, srcStr);
        }   // else 처리 안해도 어차피 loc 초기값 0

        while (srcStr.find("end") == string::npos){
            label = srcStr.substr(0, srcStr.find(' '));  // label 영역 : 1-8 byte
            opcode = srcStr.substr(9, srcStr.find(' ',9)-9); // Operation code 영역 : 10-15 byte
            oper = srcStr.substr(17, srcStr.find(' ',17)-17); // Operand 영역 : 18-35 byte

            if(srcStr[0]!='.'){ // if this is not a comment line then 
                if(label.empty()) 
                    fixFlag(label);
                else { 
                    add(label, locctr, 0); 
                    search(label);                 
                }
                int search_result = search_op(opcode, oper); // search OPTAB for OPCODE
                if (search_result==0) fixFlag(label);
                locctr += search_result;
            }

            fout << srcStr.substr(0,35)<<hex<<locctr<<endl; //write immdiate file

            getline(fin, srcStr);   //read next input line
        }
        fin.close(); fout.close(); fop.close(); symtab.close();
    }
    else fout << "argc not enough!!" << endl;
}