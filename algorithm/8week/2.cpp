#include <iostream>
#define MAX_SIZE 10
#define MAX_VALUE 100
using namespace std;

int D[MAX_SIZE][MAX_SIZE];
char stack[MAX_VALUE]={0,}; int top=0;

int min(int del, int ins, int chg){
	if(del<=ins && del<=chg) return del;
	else if(ins<=del && ins<=chg) return ins;
	else if(chg<=ins && chg<=del) return chg;
}

int EditDist(int n, string X, int m, string Y, int ins, int del, int chg) {
	// n : X의 길이, m : Y의 길이, ins : 삽입비용, del : 삭제비용, chg : 변경비용
	D[0][0] = 0; int c;

	for (int i = 1; i < n + 1; i++)
		D[i][0] = D[i - 1][0] + del;	//첫 열의 초기화
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// 첫 행의 초기화

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
		     c = (X[i-1] == Y[j-1]) ? 0 : chg;
		     D[i][j] = min(D[i - 1][j] + del, D[i][j - 1] + ins, D[i - 1][j - 1] + c);
		}
	}
	return D[n][m];
}

// 편집거리의 최소비용 구하는 경로를 찾는 함수
void traceCost(int n, string X, int m, string Y, int ins, int del, int chg) {
    if((n==0 && m==0) || n < 0 || m < 0) return; // 재귀 종료
	int o = (D[n][m] == D[n - 1][m - 1]) ? D[n - 1][m - 1] : MAX_VALUE;       
    // 대각선에 있는 두 값이 같으면 변경이 필요없는 연산, 다를 경우는 변경(C) 케이스를 선택하도록한 구문
    
    int d = D[n - 1][m]; int i = D[n][m - 1]; int c = D[n - 1][m - 1]; 
	if(n-1<0) o=d=c=MAX_VALUE; if(m-1<0) o=i=c=MAX_VALUE;	// 인덱스 범위 넘어 갈때 예외처리
    // 그 전 노드의 값을 비교하여 최소인 것 선택하고 배열에 알파벳을 삽입 (그리디 알고리즘 느낌으로 주변에서 가장 작은 값쪽으로 역추적함)
    if(o<=i && o<=d && o <= c) { stack[top++] = 'O'; n-=1; m-=1; }
    else if(c<=i && c<=d && c <= o) { stack[top++] = 'C'; n-=1; m-=1; }
    else if(d<=i && d<=c && d <= o) { stack[top++] = 'D'; n-=1; }
	else if(i<=d && i<=c && i <= o) { stack[top++] = 'I'; m-=1; }
    
    traceCost(n, X, m, Y, ins, del, chg); // DP배열의 인덱스를 배열의 인덱스를 하나 줄이고 다시 호출
}

int main(){
	cout<<"초기 문자열을 입력하시오 : "; string org; cin>>org;
	cout<<"목표 문자열을 입력하시오 : "; string goal; cin>>goal;

	EditDist(org.length(), org, goal.length(), goal, 1, 1, 2);
	cout<<"편집거리 테이블"<<endl;
	for(int i=0;i<=org.length();i++){
		for(int j=0;j<=goal.length();j++)
			cout<<D[i][j]<<' ';
		cout<<endl;
	} 
    
	cout<<"\n최소비용 경로 : ";
    traceCost(org.length(), org, goal.length(), goal, 1, 1, 2);
    for(int i=top-1;i>=0;i--) cout<<stack[i]<<' '; cout<<endl;
}