/*
Full sorting is unnecessary
tracking only each row’s minimum element suffices.(Waitingroom[i][0])
Upon the arrival of a new number, iterate over the rows’ minimums.

0. If nothing exists yet, insert it. → start.

1. When a row is encountered whose 0th (first) element is greater than the new number:
    -Insert the new number into the preceding row.
    -If no preceding row exists (only row 0 exists), replace the first element of that row with the new number.
    -If no such row is found, insert the new number into the last row.

Check that row’s length. If it equals 2k, sort the row and move the second half
(from the middle element to the end) to form the next row.
    If it is not 2k, no action is needed.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void input(int number, int k, vector<vector<int>>& Waitroom) {
    if (Waitroom.empty()) {
        Waitroom.push_back({ number }); //if vector is empty..
        return;
    }

    int row_cnt = Waitroom.size();
    int idx = 0;
    while (idx < row_cnt && Waitroom[idx][0] < number) idx++;
    if (idx == 0) Waitroom[0].insert(Waitroom[0].begin(), number);
    else if (idx == row_cnt) {
        Waitroom[idx - 1].push_back(number); // 마지막에 원소 추가
        idx--;
    }
    else {
        idx--;
        Waitroom[idx].push_back(number);
    }

    if (Waitroom[idx].size() == 2 * k) {
        sort(Waitroom[idx].begin(), Waitroom[idx].end());

        Waitroom.insert(Waitroom.begin() + idx + 1, vector<int>(Waitroom[idx].begin() + k, Waitroom[idx].end()));
        Waitroom[idx].resize(Waitroom[idx].size() - k);
    }

}

void output(int number, vector<vector<int>>& Waitroom) {
    for (auto& row : Waitroom) {
        if (row.empty()) continue;
        if (row[0] == number) sort(row.begin(), row.end());
        row.erase(remove(row.begin(), row.end(), number), row.end());
    }

    Waitroom.erase(remove_if(Waitroom.begin(), Waitroom.end(),
                             [](const vector<int>& row){ return row.empty(); }),
                   Waitroom.end());
}

int main()
{
    vector<vector<int>> Waitroom;
    int N, k, number;
    cin >> N >> k;

    string s;
    for (int i = 0; i < N; i++) {
        cin >> s >> number;

        if (s == "+") {
            input(number, k, Waitroom);
        }
        else {
            output(number, Waitroom);
        }
    }

    for (auto& row : Waitroom) {
        cout << row[0] << endl;
    }
}

