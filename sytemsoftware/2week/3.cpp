#include <iostream>
#include <fstream>
using namespace std;

int change(string code){
    char *cArr;
    int len=code.length();

    cArr = new char(len / 2); // num 배열에 문자 스트링을 숫자로 변환후 값을 저장할 크기만큼 메모리 할당
    if(cArr == NULL) {printf("null Error"); return -1;}  // 널가드

    int flag=0, idx=0;      // flag: 자릿수 옮기기 플래그 (flag = 1이면 16진수니까 기존값*16해서 자릿수 올림) / idx : 변환한 값을 저장할 int배열의 인덱스 
    for(int i=0;i<len;i++){
        if(flag==1) { cArr[idx]*=16; flag=0; }       
        else flag++;
        
        if('0'<= code[i] && code[i]<='9') cArr[idx] += (code[i]-'0');
        else if('A'<=code[i] && code[i] <= 'F') cArr[idx] += (code[i]-'A'+10);
        else { printf("\nError value\n"); return -1; }      // 잘못된 값들어가 있을 경우 오류 메세제 출력과 동시에 프로그램 종료

        if(flag==0) idx++;
    }
    for(int i=0;i<len/2;i++) printf("%x ", cArr[i]); printf("\n");
}

int main(int argc, char *argv[]){
    if (argc == 2){
        fstream fin("DEVF2");
        string str, TAG, PROGNAME, ADDR, SIZE, CODES, LENGTH, OTHERS;
        while(getline(fin, str)){
            TAG=str[0], PROGNAME.clear(), ADDR.clear(), SIZE.clear(), CODES.clear(), LENGTH.clear(), OTHERS.clear();
            if(TAG=="H"){
                PROGNAME=str.substr(1,6); ADDR=str.substr(7,6); 
                SIZE=str.substr(13,6);
            }
            else if(TAG=="T"){
                ADDR=str.substr(1,6); LENGTH=str.substr(7,2);
                CODES=str.substr(9,51); 
            }
            else if(TAG=="M" || TAG=="E"){
                ADDR=str.substr(1,6); OTHERS=str.substr(9,51);
            }
            if(!CODES.empty()){
                change(CODES);
            }
        }
    }
}