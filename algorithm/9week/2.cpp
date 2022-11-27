#include <iostream>
#define Nmax 100
using namespace std;

struct point { char c; int x, y; float angle;};
struct line { struct point p1, p2; };
struct point polygon[Nmax]; 
int size;

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
        if (RightSon <= LastNode &&polygon[LeftSon].angle < polygon[RightSon].angle)
            Son = RightSon;         
        else
            Son = LeftSon;
        // 오른쪽, 왼쪽 자식중 더 큰 자식을 Son에 넣음
        if (RootValue.angle < polygon[Son].angle) {
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
    t = (ax+ay == 0) ? 0 : (float) dy/(ax+ay); 
    if (dx < 0) {
        t = 2-t;
    } 
     else if (dy < 0) {
        t = 4+t;
    }
    
    return t*90.0;
}

bool isInside(int x, int y){ // x,y는 기준점의 좌표
    //cnt는 기준선의 반직선과 다각형과의 교점의 개수
    int cnt = 0;
    for(int i = 0; i < size; i++){
        int j = (i+1)%size; // i가 마지막 점일때 시작점과 비교하기 위해서 %size함
        // 기준점이 polyon[i],poly[i+1]의 y좌표 사이에 있음
        if((polygon[i].y > y) != (polygon[j].y > y)){
            // crosX는 기준점을 지나는 수평선과 선분 polyon[i],poly[i+1]의 교점
            double crosX = (polygon[j].x- polygon[i].x)*(y-polygon[i].y)/(polygon[j].y-polygon[i].y)+polygon[i].x; 
            // crosX가 기준점보다 크면 오른쪽 반직선과 교차하므로 교점의 개수를 증가함
            if(x < crosX) cnt++;
        }
    }
    return cnt % 2 > 0;
}

int main(){
    int minX=100, minY=100; int standIdx=0; int x,y; 
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
    cout<<"다각형이 만들어지는 순서 : ";
    for(int i=0;i<size;i++) {
        cout<<polygon[i].c;
        if(i!=size-1) cout<<'-';
    }
    cout<<endl<<isInside(x,y)<<endl;
}