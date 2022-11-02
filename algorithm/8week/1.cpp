#include <iostream>
#define MAX_SIZE 10
using namespace std;

int D[MAX_SIZE][MAX_SIZE];

int min(int del, int ins, int chg){
	if(del<=ins && del<=chg) return del;
	else if(ins<=del && ins<=chg) return ins;
	else if(chg<=ins && chg<=del) return chg;
}

int EditDist(int n, string X, int m, string Y, int ins, int del, int chg) {
	// n : X�� ����, m : Y�� ����, ins : ���Ժ��, del : �������, chg : ������
	D[0][0] = 0;
	int c;

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

int main(){
	cout<<"�ʱ� ���ڿ��� �Է��Ͻÿ� : "; 
	string org; cin>>org;
	cout<<"��ǥ ���ڿ��� �Է��Ͻÿ� : "; 
	string goal; cin>>goal;
	int minCost=EditDist(org.length(), org, goal.length(), goal, 1, 1, 2);

	cout<<"�����Ÿ� ���̺�"<<endl;
	for(int i=0;i<=org.length();i++){
		for(int j=0;j<=goal.length();j++)
			cout<<D[i][j]<<' ';
		cout<<endl;
	}
	cout<<"\n�ּ�������� : "<<minCost<<endl;
}