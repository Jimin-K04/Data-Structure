#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point{
    int x,y;
};

struct Segment{
    int distance;
    Point direction;
};

int dist_cal(Point a, Point b){
    return hypotl(a.x-b.x, a.y-b.y);
}
//check direction
Point compare_point(Point a, Point b){
    if (a.x < b.x) return {-1,0};
    if (a.x > b.x) return {1,0};
    if (a.y < b.y) return {0,-1};
    if (a.y > b.y) return {0,1};
    return {0,0};
}

int main()
{
    int k, x, y;
    cin >> k;

    int i;
    vector<Point> point_lst;
    for (i= 0; i < k; i++){
        cin >> x >> y;
        point_lst.push_back({x,y});
    }

    //segment -> distance and direction
    int distance;
    vector<Segment> segments;
    for (i = 1; i < k; i++){
        distance = dist_cal(point_lst[i], point_lst[i-1]);
        segments.push_back({distance, compare_point(point_lst[i-1], point_lst[i])});
    }
    //process the final segment separately
    distance = dist_cal(point_lst[0], point_lst[k-1]);
    segments.push_back({distance, compare_point(point_lst[k-1], point_lst[0])});

    //prefix sum
    vector<int> distance_sum(k);
    distance_sum[0] = segments[0].distance;
    for(i = 1; i < k; i++){
        distance_sum[i] = distance_sum[i-1] + segments[i].distance;
    }
    //t: time point
    int t, idx, diff, robot_x, robot_y, segment_idx;

    for(i = 0; i < 5; i++){
        idx = 0;
        cin >> t;
        t %= distance_sum[k-1]; //total_distance

        while(distance_sum[idx] < t) idx++;
        // the difference form the actual distance
        diff = distance_sum[idx] - t;
        //index (idx + 1) point + diff* direcion -> robot location.
        segment_idx = idx;
        idx++;
        if (idx >= k) idx = 0; //exception
        robot_x = point_lst[idx].x + diff*(segments[segment_idx].direction.x);
        robot_y = point_lst[idx].y + diff*(segments[segment_idx].direction.y);
        cout << robot_x << " " << robot_y << endl;
    }
}
