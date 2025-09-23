#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Pt{
    double x, y, r;
};

double distance_pt(Pt a, Pt b){
    return hypot(a.x - b.x, a.y-b.y);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    Pt p1{x1, y1, r1};
    Pt p2{x2, y2, r2};
    vector<Pt> points = {p1, p2} ;
    sort(points.begin(), points.end(), [](const Pt& a, const Pt& b){
            return a.r < b.r;
         });
    // d is center-to-center distance, l is tangent length
    double d = distance_pt(p1, p2);
    double l = sqrt(d*d - (r2-r1)*(r2-r1));

    r2 = points[1].r;
    r1 = points[0].r;

    double perimeter, area, cos_value, theta;
    double pi = M_PI;

    cos_value = (r2 - r1)/d;
    cos_value = clamp(cos_value, -1.0, 1.0);
    theta = acos(cos_value);

    perimeter = 2*l + r2*(2*pi-2*theta) + r1*2*theta;
    area = (r2+r1)*l + r2*r2*(pi-theta) + r1*r1*theta;

    cout << static_cast<int>(area) << " " << static_cast<int>(perimeter);
}
