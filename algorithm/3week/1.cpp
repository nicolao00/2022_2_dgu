#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;

int n;
itemType **tmp = new itemType*[n];
void insertion(itemType a[],  int n) 
{ 
    int i, j; itemType v; 
    for (i = 2; i <= n; i++) { 
       v = a[i]; j = i; 
       while (a[j-1] > v) { a[j] = a[j-1]; j--; } 
       a[j] = v; 
    } 
}

void insertion(itemType a[],  int n) 
{ 
    int i, j; itemType v; 
    for (i = 2; i <= n; i++) { 
       v = a[i]; j = i; 
       while (a[j-1] > v) { a[j] = a[j-1]; j--; } 
       a[j] = v; 
    } 
}

int main(){
    cin>>n;
    itemType *A = new itemType[n]; itemType *B = new itemType[n]; 
    srand((unsigned)time(NULL)); 

    for(int i=n;i>0;i++) A[n-i]=i;
    for(int i=0;i<n;i++){
        tmp[i]=new int[2];
        tmp[i][0]=(1+rand()%n);
        tmp[i][1]=i+1;
    }
    insertion(A, n);
}


2 6 14 5 4 4 8 9 6
1 2 3 4 5  6 7 8 9

2 4 4 