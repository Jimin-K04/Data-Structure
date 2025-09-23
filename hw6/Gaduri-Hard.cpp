/*
    circle class �� ����� ����.
    ���� �Լ��� class �� ����� ����.
    �ϴ���..
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
    int a,b; // ������ ������ ��
    double k; // ����
public:

    //constructor
    // �� �ΰ��� �־��� ���
    linear_func(int x1, int y1, int x2, int y2) : a{x1}, b{y1} {
        k = (double)(y1-y2)/(x1-x2);
    }
    // �� �ϳ��� ���Ⱑ �־��� ���
    linear_func(int x1, int y1, int l) : a{x1}, b{y1}, k{l} {}

    // x ���� �ش��ϴ� �Լ� ���� ȣ���ϴ� �Լ�.
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
            return a.x < b.x; //x �� ���� ����.
         });
}
