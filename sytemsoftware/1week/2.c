#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM 100


int main(){
    char a[MAX_NUM]={0, }; int *num; int len=0;
    scanf("%s", a); 
    
    while(a[len]!='\0') len++;      // 입력한 값의 길이
    if(len%2 == 1){printf("half-byte len is odd.\n"); return -1;} // 홀수개의 하프바이트일 경우 오류처리

    num = (int *)malloc(sizeof(int) * (len / 2)); // num 배열에 문자 스트링을 숫자로 변환후 값을 저장할 크기만큼 메모리 할당
    if(num == NULL) {printf("null Error"); return -1;}  // 널가드
    for(int i=0; i<len/2; i++) num[i]=0;

    int flag=0, idx=0;      // flag: 자릿수 옮기기 플래그 (flag = 1이면 16진수니까 기존값*16해서 자릿수 올림) / idx : 변환한 값을 저장할 int배열의 인덱스 
    for(int i=0;i<len;i++){
        if(flag==1) { num[idx]*=16; flag=0; }       
        else flag++;
        
        if('0'<=a[i] && a[i]<='9') num[idx] += (a[i]-'0');
        else if('A'<=a[i] && a[i] <= 'F') num[idx] += (a[i]-'A'+10);
        else { printf("\nError value\n"); return -1; }      // 잘못된 값들어가 있을 경우 오류 메세제 출력과 동시에 프로그램 종료

        if(flag==0) idx++;
    }
    for(int i=0;i<len/2;i++) printf("%x ", num[i]); printf("\n");
}