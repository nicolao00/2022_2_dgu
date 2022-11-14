#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 100; // 버켓의 크기
int locctr, stLoc, proglength;      // location counter, 시작 locctr, 프로그램 길이
ifstream fsrc; ofstream fintf;      // fsrc: SRCFILE , fint: INTFILE
ifstream fop; ofstream symtab;      // fop: Optab.txt , symtab: Symtab.txt

//String을 해쉬테이블의 key로 사용하므로 문자열의 아스키값을 다 더한값을 씀.
int hashFunction(string str){
    int key=0;
    for(int i=0;i<str.length();i++) key+=str[i];
    // 해쉬함수 만들기. 여기서는 단순히 key를 버켓 길이로 나눈 나머지로 함수를 만듦.
    return key%BUCKET_SIZE;
}

// 노드 구조체 선언
struct node {
    string label;       // 해시 함수에 사용될 키(라벨)
    int address;        // symbol의 주소
    int flag;           // 오류 flag (정상이면 0)
    struct node* next; // 다음 노드를 가르키는 포인터
};

// 버켓 구조체 선언
struct bucket{
    struct node* head;  // 버켓 가장 앞에 있는 노드의 포인터
    int count;          // 버켓에 들어있는 노드의 개수
};

// 새로운 노드의 생성자 역할 (초기화 담당)
struct node* createNode(string label, int address, int flag){
    struct node* newNode = new node();
    newNode->label = label; newNode->address = address;
    newNode->flag = flag; newNode->next = NULL;
    return newNode;
}

// 해시테이블에 값을 추가하는 함수
void add(string label, int address, int flag){
    struct node* newNode = createNode(label, address, flag);
    int hashIndex = hashFunction(label);

    // 해시테이블[키값]의 노드가 아무것도 없을 때
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; // head로 지정
    }
    // 버켓에 다른 노드가 있을 경우 한칸씩 밀고 내가 헤드가 된다(실제로는 포인터만 바꿔줌)
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

// label을 키로 변환해서 찾고자하는 노드 탐색후 노드 반환
struct node* find_node(string label){
    int hashIndex = hashFunction(label);
    struct node* node = hashTable[hashIndex].head;
    struct node* temp= NULL;

    while (node != NULL){
        if (node->label == label){
            temp=node;
            break;
        }     
        node = node->next;
    }
    return temp;
}

//만든 symtab을 symtab.txt파일에 쓰는 함수
void make_symtab(){
    for (int i = 0; i < BUCKET_SIZE; i++){
        if (hashTable[i].count == 0) continue;
        struct node *node = hashTable[i].head;
        while (node != NULL){
            symtab <<left<<setw(8)<< node->label<<setw(6)<< hex << node->address <<setw(2)<< node->flag << endl;
            // Symtab : label 0 / address 8 / flag 14 인덱스부터 시작
            node = node->next;
        }
    } 
}

// search OPTAB for OPCODE 하는 과정 (리턴값은 Locctr에 더할 값)
int search_op(string str, string operand){
    string opstr; int result=0;

    fop.close(); fop.open("Optab.txt");
    while(getline(fop, opstr)){
        if(str=="word") { result = 3; break;}
        else if(str=="resw") { result = 3 * stoi(operand); break;}
        else if(str=="resb") { result = stoi(operand); break;}
        else if(str=="byte") { result = operand.length()-3; break;}
        else if(opstr.find(str) != string::npos) { result = 3; break;}
    }
    return result;
}



void pass1(){
    locctr = 0;
    string srcStr, label, opcode, oper, comment;    // srcStr: SRCFILE에서 읽어온 한 줄을 저장
    getline(fsrc, srcStr);
    if (srcStr.find("start") != string::npos){
        string oper = srcStr.substr(17, srcStr.find(' ', 17) - 17);
        stLoc = locctr = stoi(oper, nullptr, 16);
        fintf <<left<<setw(6)<< oper<<srcStr.substr(0, 35)<< endl;
        getline(fsrc, srcStr);
    }

    while (srcStr.find("end") == string::npos){
        label = srcStr.substr(0, srcStr.find(' '));          // label 영역 : 1-8 byte
        opcode = srcStr.substr(9, srcStr.find(' ', 9) - 9);  // Operation code 영역 : 10-15 byte
        oper = srcStr.substr(17, srcStr.find(' ', 17) - 17); // Operand 영역 : 18-35 byte
        comment = srcStr.substr(35, srcStr.find(' ', 31));   // Comment 영역 : 36-66 byte
        
        struct node *temp = NULL;                            // 찾고자하는 노드 주소 저장할때 쓰일 변수
        int search_result;
        if (srcStr[0] != '.'){           // if this is not a comment line then
            if (!label.empty()) {        // if there is a symbol in the LABEL field then
                temp = find_node(label); // search SYMTAB for LABEL
                if (temp) temp->flag = 1;      // duplicate symbol
                else add(label, locctr, 0); // else insert (LABEL, LOCCTR) into SYMTAB
            }
            // search OPTAB for OPCODE
            search_result = search_op(opcode, oper);
            if (search_result == 0) find_node(label);
            locctr += search_result;
        }
        fintf <<left<<setw(6)<< hex << locctr-search_result << srcStr.substr(0, 65) << endl; 
        // write immdiate file / intfile에 쓰기전에 명령어 길이만큼 주소를 추가했으므로 추가한 명령어 길이만큼 빼줌
        getline(fsrc, srcStr);          // read next input line
    }
    comment = srcStr.substr(35, srcStr.find(' ', 31));
    opcode = srcStr.substr(9, srcStr.find(' ', 9) - 9);
    oper = srcStr.substr(17, srcStr.find(' ', 17) - 17);
    fintf<<left<<setw(15)<<' '<<setw(8)<<opcode<<setw(18)<<oper<<comment<<endl;  // write last line to intermediate file
    proglength = locctr - stLoc;            // save (LOCCTR – starting address) as program length

    make_symtab();
}


//주어진 opcode가 optab에 있는지 탐색
int exist_op(string opcode){
    string opstr; int result=0;
    fop.close(); fop.open("Optab.txt");
    while(getline(fop, opstr)){
        if(opstr.find(opcode) != string::npos) {
            result=1;
            break;
        }
    }
    return result;    
}

// 10진수를 16진법으로 구성된 string으로 표현
string hexToStr(int num, int length) {
   int temp; string result, word;
   for (int i = 0; i < length; i++) {
      temp = num % 16;
      if (temp >= 10) word = char('a' + temp - 10);
      else word = char('0' + temp);
      result = word+result;
      num /= 16;
   }
   return result;
}


/*
INTFILE 
locctr: 0 / label: 6 / opcode: 15 / oprand 23 / comment 41 인덱스부터 시작
*/
void pass2(){
    ofstream obj; ifstream intf;  // 오브젝트 파일, 인트파일
    obj.open("OBJECT"); intf.open("INTFILE");
    if (!obj.is_open() || !intf.is_open()){
        cout << "Error, no such file" << endl;
        return;
    }

    string intStr, loc, label, opcode, oper, comment, record, address, assemInst; 
    // record:옵젝파일에 저장할 내용 / address: oprand자리의 symbol 주소 / assemInt: record에 저장될 코드
    getline(intf, intStr);              // read first input line
    string startLabel = intStr.substr(6, intStr.find(' ', 6)-6);
    if (intStr.find("start") != string::npos) getline(intf, intStr);

    // write Header record to object program
    obj <<'H'<<left<<setw(6)<<startLabel <<right<<setw(6)<<setfill('0')<<hex<<stLoc<<setw(6)<<proglength<<endl;
    record.clear();                     //initialize first Text record

    string temp; string startLc=intStr.substr(0, intStr.find(' '));  // startLc: 새로운 text record line의 첫번째 record의 loccter
    while(intStr.find("end") == string::npos){
        loc = intStr.substr(0, intStr.find(' '));
        label = intStr.substr(6, intStr.find(' ', 6) - 6);
        opcode = intStr.substr(15, intStr.find(' ', 15) - 15);
        oper = intStr.substr(23, intStr.find(' ', 23) - 23);
        assemInst.clear(); address.clear();
        int resflag=0;                   // 현재 명령어가 resw,resb이면 1 아니면
        
        if (intStr[0] != '.'){           // this is not a comment
            if (exist_op(opcode)){       // if found then (search OPTAB for OPCODE)
                if (!oper.empty()){      // if there is a symbol in OPERAND field
                    // exaddr,x같은 경우 ,앞에 exaddr만 잘라서 symtab에 검색
                    if (oper.find(',')!=string::npos)
                        oper = oper.substr(0, oper.find(','));

                    //search SYMTAB for OPERAND
                    struct node *a = find_node(oper); // symtab에 해당 operand의 symbol이 있으면 그 노드 반환
                    if (a) { // 16진수 정수로 표현된 주소값 4자리를 16진법로 표기된 문자열로 바꿔서 address에 저장
                        int num=a->address, hexnum=16*16*16;
                        for(int i=1;i<=4;i++){
                            int hexn=num/hexnum; char hexc;
                            if(hexn<=9) hexc = hexn + '0';
                            else hexc = hexn-10+'a';
                            address+=hexc;
                            num%=hexnum;
                            hexnum/=16;                            
                        }
                    }
                    else{   
                        address = "0000";               // store 0 as operand address
                        cout << "undefined symbol\n";   // set error flag
                        return;
                    }
                }
                else address = "0000";

                // assemble the object code instruction
                string opstr;
                fop.close(); fop.open("Optab.txt");
                while (getline(fop, opstr)){
                    if(opstr.find(opcode)!=string::npos){
                        assemInst=opstr.substr(opstr.find(',')+1, 2); // optab의 opcode값 저장
                        break;
                    }
                }
                assemInst.append(address);
            }

            else if(opcode=="byte" || opcode == "word"){
                if (opcode == "word"){      // convert constant to object code (빈자리를 0으로 채워 6자리로 맞추는 과정 포함)
                    int dec = stoi(oper);
                    assemInst = hexToStr(dec, oper.length());
                    for(int i=assemInst.length(); assemInst.length()<6; i++) assemInst="0"+assemInst;
                }

                else{ // oper에 해당하는 문자열을 16진법으로 표기된 문자로 출력
                    if(oper[0]=='c'){
                        for(int i=2; i<oper.length()-1; i++){
                            int hexb=oper[i];
                            int temp=hexb,len=1;
                            while(temp/10){
                                temp%=10;
                                len++;
                            }
                            string str=hexToStr(hexb,len);
                            assemInst=assemInst+str;
                        }
                    }

                    else if(oper[0]=='x'){ //16진법으로 표기된 oper의 내용들을 assemInt에 저장
                        for(int i=2; i<oper.length()-1; i++)
                            assemInst=assemInst+oper[i];
                    }

                    else { // c,x없이 그냥 쓰는 경우 (10진수)
                        for (int i = 0; i < oper.length(); i++) {
                            assemInst = assemInst+oper[i];
                        }
                    }
                }
            }
            else if(opcode=="resb" || opcode=="resw") resflag=1;
        }
        if(resflag || record.length()+assemInst.length() > 60){ //if object code will not fit into the current Text record
            // write Text record to object program
            obj<<'T'<<setfill('0')<<setw(6)<<startLc<<setw(2)<<hex<<record.length()/2<<record<<endl;
            record.clear();         //initialize first Text record
        }
        if(!resflag && record.length()==0) startLc = loc;// 현재 읽은 opcode가 resw,resb가 아닌 명령어고 새로운 record 라인일 경우
        record.append(assemInst);   // add object code to Text record
        getline(intf, intStr);      // read next input line 
    }
    // write End record to object program
    obj<<'E'<<setfill('0')<<setw(6)<<stLoc;
    fop.close(); obj.close(); intf.close();
}

int main(int argc, char *argv[]){ // 입력파일 : 소스파일(SRCFILE), Optab.txt
    if (argc == 3){
        fsrc.open(argv[1]); fop.open(argv[2]); fintf.open("INTFILE"); symtab.open("Symtab.txt");
        hashTable = new bucket[BUCKET_SIZE];
        memset(hashTable, 0, sizeof(struct node));
        
        if (!fsrc.is_open() || !fintf.is_open() || !fop.is_open() || !symtab.is_open()){
            cout << "Error, no such file" << endl;
            return -1;
        }
        pass1();
        pass2();

        fsrc.close(); fintf.close(); symtab.close(); fop.close();
    }
    else cout << "argc not enough!!" << endl;
}