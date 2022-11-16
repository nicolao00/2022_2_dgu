#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    //프로그램 실행시 rdbuff의 정의가 저장된 파일과 &indev와 &bufadr부분을 치환할 문자열 2개 입력받음
    if(argc==4){
        ifstream reb; reb.open(argv[1]);
        if(!reb.is_open()) {
            cout<<"File open Error\n";
            return -1;
        }
        // indev을 치환할 문자열 저장, bufadr을 치환할 문자열 저장.
        string indev=argv[2]; string bufadr=argv[3]; string rebStr;

        // rebuf.txt에서 문자열 한줄씩 읽어옴
        while(getline(reb, rebStr)){ 
            // &indev 부분을 받아온 indev로 변환하여 출력
            if(rebStr.find("&indev") != string::npos) 
                rebStr.replace(rebStr.find("&indev"), 6, indev); 

            // &bufadr 부분을 받아온 bufadr 변환하여 출력
            if(rebStr.find("&bufadr") != string::npos)
                rebStr.replace(rebStr.find("&bufadr"), 7, bufadr); 
                
            // macro 선언부와 mend 종료 부분은 출력에서 제외
            if(rebStr.find("macro") ==string::npos && rebStr.find("mend") == string::npos)
                cout<<rebStr<<endl;
        }
    }
    else cout<<"arg error!\n";
}