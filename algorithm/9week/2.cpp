#include <iostream>
#define Nmax 100
using namespace std;

struct point { char c; int x, y; float angle;};
struct line { struct point p1, p2; };
struct point polygon[Nmax]; 
int comp, angleCnt, size;

void swap(int i, int j){
    point temp = polygon[i];
    polygon[i] = polygon[j];
    polygon[j] = temp;
}

void MakeHeap(int Root, int LastNode){
    int Parent, LeftSon, RightSon, Son;
    point RootValue;
    Parent = Root;
    RootValue = polygon[Root];
    LeftSon = 2 * Parent + 1;
    RightSon = LeftSon + 1;
    while (LeftSon <= LastNode) {
        if (RightSon <= LastNode && ++comp && polygon[LeftSon].angle < polygon[RightSon].angle)
            Son = RightSon;         
        else
            Son = LeftSon;
        // ������, ���� �ڽ��� �� ū �ڽ��� Son�� ����
        if (++comp && RootValue.angle < polygon[Son].angle) {
            polygon[Parent] = polygon[Son];
            Parent = Son;
            LeftSon = Parent * 2 + 1;
            RightSon = LeftSon + 1;
        }
        else break;
    }
    polygon[Parent] = RootValue;
}

void heapsort(int N){
    int i;
    for (i = N / 2; i >= 0; i--) MakeHeap(i, N - 1);
    for (i = N - 1; i >= 1; i--) {
        swap(0, i);
        MakeHeap(0, i - 1);
    }
}

float ComputeAngle(struct point p1, struct point p2){ 
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x; ax = abs(dx);
    dy = p2.y - p1.y; ay = abs(dy);
    t = (ax+ay == 0) ? 0 : (float) dy/(ax+ay); ++angleCnt;
    if (dx < 0) {
        t = 2-t;
        ++angleCnt;
    } 
     else if (dy < 0) {
        t = 4+t;
        ++angleCnt;
    }
    
    return t*90.0;
}


bool isInside(int x, int y){
    //crosses�� ��q�� ������ �������� �ٰ������� ������ ����
    int crosses = 0;
    for(int i = 0 ; i < size ; i++){
        int j = (i+1)%size;
        //�� B�� ���� (p[i], p[j])�� y��ǥ ���̿� ����
        if((polygon[i].y > y) != (polygon[j].y > y) ){
            //atX�� �� B�� ������ ���򼱰� ���� (p[i], p[j])�� ����
            double atX = (polygon[j].x- polygon[i].x)*(y-polygon[i].y)/(polygon[j].y-polygon[i].y)+polygon[i].x; //https://bowbowbow.tistory.com/24
            //atX�� ������ ���������� ������ ������ ������ ������ ������Ų��.
            if(x < atX)
                crosses++;
        }
    }
    return crosses % 2 > 0;
}

int main(){
    int minX=100, minY=100; int standIdx=0; comp=0; angleCnt=0; int x,y; 
    cin>>size>>x>>y; 
    for(int i=0;i<size;i++){
        cin >> polygon[i].c >> polygon[i].x >> polygon[i].y;
        if(minY > polygon[i].y || (minY == polygon[i].y && minX > polygon[i].x)){
            minY=polygon[i].y; minX=polygon[i].x; standIdx=i;
        }
    }

    for(int i=0;i<size;i++){
        polygon[i].angle=ComputeAngle(polygon[standIdx],polygon[i]);
    }

    heapsort(size);
    cout<<"�ٰ����� ��������� ���� : ";
    for(int i=0;i<size;i++) {
        cout<<polygon[i].c;
        if(i!=size-1) cout<<'-';
    }
    cout<<endl<<isInside(x,y)<<endl;
}
/*
8 3 5 
A 3 4
B 1 2
C 2 5
D 2 6
E 9 3
F 5 3
G 6 4
H 8 7
*/