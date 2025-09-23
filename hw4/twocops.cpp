#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
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

Point find_point_location(int t, int k, vector<int> distance_sum, vector<Point> point_lst, vector<Segment> segments){
    int diff, x, y, segment_idx, idx = 0;

    while(distance_sum[idx] < t) idx++;
    // the difference form the actual distance
    diff = distance_sum[idx] - t;
    //index (idx + 1) point + diff*direcion = robot location.
    segment_idx = idx;
    idx++;

    if (idx >= k) idx = 0; //exception
    x = point_lst[idx].x + diff*(segments[segment_idx].direction.x);
    y = point_lst[idx].y + diff*(segments[segment_idx].direction.y);
    return {x,y};
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
    //twocops
    /* logic
        Assume that when c1 and c2 collide,
        they continue moving without changing direction.
        Compute c1 position the same way as in the robocop case,
        and compute c2 position using the path difference relative to c1.
        Finally, count the number of collisions between c1 and c2.
        if it is odd, output the two points with their positions swapped
        if it is even, output them as is.
    */
    int c1c2_original_diff = distance_sum[k/2 -2];
    int total_distance = distance_sum[k-1];
    int t;
    cin >> t;
    t %= total_distance;
    /*
      2*t = c1c2_original_diff*n1 + total_distance*n2 + a
      final_diff is final difference between c1 and c2.
      the number of collisions = n1+n2.
    */
    int n1=0, n2=0, a = 2*t, final_diff;
    //no collision
    if (c1c2_original_diff > 2*t) {
        final_diff = c1c2_original_diff - a;
    }
    else { //occur collision
        n1 = 1;
        n2 = (2*t - c1c2_original_diff*n1)/total_distance;
        a = (2*t - c1c2_original_diff*n1)%total_distance;
        final_diff = (total_distance - a)%total_distance;
    }

    int is_swap = (n1+n2)%2;

    Point c1 = find_point_location(t, k, distance_sum, point_lst, segments);
    Point c2 = find_point_location((t + final_diff) % total_distance, k, distance_sum, point_lst, segments);


    if (is_swap){
        swap(c1.x, c2.x);
        swap(c1.y, c2.y);
    }
    cout << c1.x << " " << c1.y << endl;
    cout << c2.x << " " << c2.y << endl;
}
