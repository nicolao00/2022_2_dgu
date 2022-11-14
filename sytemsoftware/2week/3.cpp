#include <iostream>
#include <fstream>
using namespace std;

int change(string code){
    unsigned char *cArr;
    int len=code.length();

    cArr = new unsigned char(len / 2); // num 배열에 문자 스트링을 숫자로 변환후 값을 저장할 크기만큼 메모리 할당
    if(cArr == NULL) {printf("null Error"); return -1;}  // 널가드

    int flag=0, idx=0;      // flag: 자릿수 옮기기 플래그 (flag = 1이면 16진수니까 쉬프트연산해서 자릿수 올림) / idx : 변환한 값을 저장할 int배열의 인덱스 
    for(int i=0;i<len;i++){
        if(flag==1) { cArr[idx] << 4; flag=0; }       
        else flag++;
        
        if('0'<= code[i] && code[i]<='9') cArr[idx] = cArr[idx]<<4 | (code[i]-48);
        else if('A'<=code[i] && code[i] <= 'F') cArr[idx] = cArr[idx]<<4 | (code[i]-55);
        else { printf("\nError value\n"); return -1; }      // 잘못된 값들어가 있을 경우 오류 메세제 출력과 동시에 프로그램 종료

        if(flag==0) idx++;
    }
    //for(int i=0;i<len/2;i++) printf("%02x ", cArr[i]); printf("\n");
    unsigned char ten=240, one=15;
    for(int i=0;i<len/2;i++) {
        unsigned char temp = ten & cArr[i];
        temp = temp >> 4;
        printf("%d ", temp);
        temp = one & cArr[i];
        printf("%d ", temp);
    }
    printf("\n");
    delete[] cArr;
    return len;
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
                CODES=str.substr(9,50); 
                cout<<"CODES: "<<CODES<<endl;
            }
            else if(TAG=="M" || TAG=="E"){
                ADDR=str.substr(1,6); if(TAG=="M") OTHERS=str.substr(9,51);
            }
            if(!CODES.empty()){
                if(change(CODES)==-1) return 0;
            }
        }
    }
}