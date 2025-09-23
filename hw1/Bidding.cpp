#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<string, int>> arr;

    for (int i = 0; i < N; i++){
        string name;
        int price;
        cin >> name >> price;

        arr.emplace_back(name, price);
    }

    sort(arr.begin(), arr.end(), [](const auto& a, const auto& b){
            return a.second > b.second;
         });

    int top_idx=0;
    int cur_idx=1;

    while(cur_idx < N){
        while(arr[top_idx].second == arr[cur_idx].second) cur_idx++;
        if (cur_idx >= N) {
                cout << "NONE";
                return 0;
        }
        else if (top_idx +1 == cur_idx) {
                cout << arr[top_idx].first;
                return 0;
        }
        top_idx = cur_idx;
        cur_idx++;
    }
    cout << arr[top_idx].first;
    return 0;
}
