/*
    circle class 를 만들어 본다.
    직선 함수의 class 도 만들어 본다.
    일단은..
*/
#include <iostream>
#include <vector>
using namespace std;

class Circle{
    int _x, _y, _r;
public:
    //constructor
    Circle() : _x(0), _y(0), _r(0) {}
    Circle(int x, int y, int r) : _x{x}, _y{y}, _r{r} {}
};

class linear_func{
    int a,b; // 직선이 지나는 점
    double k; // 기울기
public:

    //constructor
    // 점 두개가 주어진 경우
    linear_func(int x1, int y1, int x2, int y2) : a{x1}, b{y1} {
        k = (double)(y1-y2)/(x1-x2);
    }
    // 점 하나와 기울기가 주어진 경우
    linear_func(int x1, int y1, int l) : a{x1}, b{y1}, k{l} {}

    // x 값에 해당하는 함수 값을 호출하는 함수.
    double f(int x) const{
        return k*(x - a) + b;
    }
};

int main()
{
    int x,y,r;
    vector<Circle> circles(3);

    for (auto& c : circles){
        cin >> x >> y >> r;
        c = Circle(x,y,r);
    }

    sort(circles.begin(), circles.end(), [](const auto& a, const auto& b){
            return a.x < b.x; //x 값 기준 정렬.
         });
}
