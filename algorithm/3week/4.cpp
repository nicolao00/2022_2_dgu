#include <iostream>
#include <ctime>
using namespace std;

typedef int itemType;
int weight[3], idx=0; 

void insertion(itemType a[],  int n) 
{ 
    int i, j; itemType v;
    for (i = 1; i < n; i++) {
       v = a[i]; j = i;
       while (j>0 && a[j-1] > v) { a[j] = a[j-1]; weight[idx] += a[j-1]; j--;}
       a[j] = v; if(i!=j) weight[idx] += 2*v;
     } 
}

void shellSort(itemType a[], int n) 
{ 
    int i, j, h; itemType v; 
    h = 1;  do h = 3*h +1; while (h < n); 
    do {
       h = h / 3;
       for (i = h; i < n; i++){ 
          v = a[i]; j = i; 
          while (a[j-h] > v)  
          { a[j] = a[j-h]; weight[idx] += a[j-h]; j -= h;  if (j <= h-1) break; }
          a[j] = v;  weight[idx] += 2*v;
      } 
    } while (h > 1);
}

int Bubble(int sorted, itemType *a, int n) 
{
   int temp;
   if ( *(a-1) > *a) {         
       temp = *a;  weight[idx]+= 2 * *a;
       *a=*(a-1);  weight[idx]+=*(a-1);
       *(a-1) = temp; 
       sorted = false; 
   }
   return sorted;
}

void bubbleSort(itemType a[], int n) 
{ 
    int i, Sorted; 
    Sorted = false; 
    while ( !Sorted ) {
       Sorted = true;
       for ( i=1; i<n; i++ )
          Sorted = Bubble( Sorted, &a[i], n );
    }
}
int main(){
    int N; cin>>N;
    itemType *A = new itemType[N];

    for(int i=N;i>0;i--) A[N-i]=i;
    insertion(A, N); idx++;
    for(int i=N;i>0;i--) A[N-i]=i;
    bubbleSort(A, N); idx++;
    for(int i=N;i>0;i--) A[N-i]=i;
    shellSort(A, N); 
    cout<<"Insertion Sort : "<<weight[0]<<endl;
    cout<<"Bubble Sort : "<<weight[1]<<endl;
    cout<<"Shell Sort : "<<weight[2]<<endl;
    
}