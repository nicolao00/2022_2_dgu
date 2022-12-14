#include <iostream>
#define Nmax 100
using namespace std;

// 점 이름, 좌표, 기준점과 이루는 각도
struct point { char c; int x, y; float angle;};
// 선분을 이룰 두 점
struct line { struct point p1, p2; };
// 다각형의 꼭짓점
struct point polygon[Nmax]; 
int comp, angleCnt; // 각의 비교횟수, 수평각 계산 횟수

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
        // 오른쪽, 왼쪽 자식중 더 큰 자식을 Son에 넣음
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

// 기준점과 다각형의 꼭짓점의 각도를 계산해서 반환하는 함수
float ComputeAngle(struct point p1, struct point p2){ 
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x; ax = abs(dx);
    dy = p2.y - p1.y; ay = abs(dy);
    t = (ax+ay == 0) ? 0 : (float) dy/(ax+ay); ++angleCnt;
    if (dx < 0) {
        t = 2-t;
    }
    else if (dy < 0) { 
        t = 4+t;
    }
    return t*90.0;
}

int main(){
    int size; cin>>size; int minX=100, minY=100; int standIdx=0; comp=0; angleCnt=0;
    for(int i=0;i<size;i++){
        cin >> polygon[i].c >> polygon[i].x >> polygon[i].y;
        // 기준점을 정하는 과정 (y가 제일 작거나, y가 같은 경우 x가 최소인 점을 선정)
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
    cout<<endl<<angleCnt<<endl;
    cout<<comp<<endl;
}