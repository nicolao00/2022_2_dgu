#include <iostream>
#define MAX_SIZE 10
#define MAX_VALUE 10000
using namespace std;

int D[MAX_SIZE][MAX_SIZE];
char trace[5];

int min(int del, int ins, int chg){
	if(del<=ins && del<=chg) return del;
	else if(ins<=del && ins<=chg) return ins;
	else if(chg<=ins && chg<=del) return chg;
}

int EditDist(int n, string X, int m, string Y, int ins, int del, int chg) {
	// n : X�� ����, m : Y�� ����, ins : ���Ժ��, del : �������, chg : ������
	D[0][0] = 0; int c;

	for (int i = 1; i < n + 1; i++)
		D[i][0] = D[i - 1][0] + del;	//ù ���� �ʱ�ȭ
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// ù ���� �ʱ�ȭ

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
		     c = (X[i-1] == Y[j-1]) ? 0 : chg;
		     D[i][j] = min(D[i - 1][j] + del, D[i][j - 1] + ins, D[i - 1][j - 1] + c);
		}
	}
	return D[n][m];
}

// �����Ÿ��� �ּҺ�� ���ϴ� ��θ� ã�� �Լ�
void traceCost(int n, string X, int m, string Y, int ins, int del, int chg, int cnt) {
    if(cnt < 0 || (n==0 && m==0) || n < 0 || m < 0) return; // ��� ����
	int o = (D[n][m] == D[n - 1][m - 1]) ? D[n - 1][m - 1] : MAX_VALUE;       
    // �밢���� �ִ� �� ���� ������ ������ �ʿ���� ����, �ٸ� ���� ����(C) ���̽��� �����ϵ����� ����
    
    int d = D[n - 1][m]; int i = D[n][m - 1]; int c = D[n - 1][m - 1]; 
    // �� �� ����� ���� ���Ͽ� �ּ��� �� �����ϰ� �迭�� ���ĺ��� ����
    if(o<=i && o<=d && o <= c) { trace[cnt] = 'O'; n-=1; m-=1; }
    else if(c<=i && c<=d && c <= o) { trace[cnt] = 'C'; n-=1; m-=1; }
    else if(d<=i && d<=c && d <= o) { trace[cnt] = 'D'; n-=1; }
	else if(i<=d && i<=c && d <= o) { trace[cnt] = 'I'; m-=1; }
    
    traceCost(n, X, m, Y, ins, del, chg, cnt-1); // DP�迭�� �ε����� �迭�� �ε����� �ϳ� ���̰� �ٽ� ȣ��
}

int main(){
	cout<<"�ʱ� ���ڿ��� �Է��Ͻÿ� : "; string org; cin>>org;
	cout<<"��ǥ ���ڿ��� �Է��Ͻÿ� : "; string goal; cin>>goal;

	EditDist(org.length(), org, goal.length(), goal, 1, 1, 2);
	cout<<"�����Ÿ� ���̺�"<<endl;
	for(int i=0;i<=org.length();i++){
		for(int j=0;j<=goal.length();j++)
			cout<<D[i][j]<<' ';
		cout<<endl;
	} 
    
	cout<<"\n�ּҺ�� ��� : ";
    int len = (org.length()>=goal.length()) ? org.length() : goal.length();
    traceCost(org.length(), org, goal.length(), goal, 1, 1, 2, len-1);
    for(int i=0;i<len;i++) cout<<trace[i]<<' '; cout<<endl;
}