// sparse tabel algorithm
#include <bits/stdc++.h>
using namespace std;

class Table {
    vector<vector<double>> min_table;
    vector<vector<double>> max_table;

public:
    Table(vector<vector<double>> mt, vector<vector<double>> Mt) : min_table{ move(mt) }, max_table{ move(Mt) } {}

    double search_min(int s, int e) {
        int row = log2(e - s + 1);
        return min(min_table[row][s], min_table[row][e + 1 - (1 << row)]);
    }

    double search_max(int s, int e) {
        int row = log2(e - s + 1);
        return max(max_table[row][s], max_table[row][e + 1 - (1 << row)]);
    }

};

void read_file(vector<double>& p, vector<int>& t) {
    ifstream iFile("Pitcoin.txt");
    int tp;
    double price;
    iFile >> tp;
    while (iFile >> tp >> price) {
        p.push_back(price);
        t.push_back(tp);

    }
}


Table make_sparse_table(const vector<double>& p) {

    int col_size = p.size();
    int row_size = floor(log2(col_size)) + 1;

    vector<vector<double>> min_sparse_table, max_sparse_table;
    min_sparse_table.resize(row_size);
    min_sparse_table[0] = p;

    max_sparse_table.resize(row_size);
    max_sparse_table[0] = p;

    for (int i = 1; i < row_size; i++) {
        int len = col_size - (1 << i) + 1;
        min_sparse_table[i].resize(len); // ith row length
        max_sparse_table[i].resize(len);
        for (int j = 0; j < col_size - (1 << i) + 1; j++) {
            min_sparse_table[i][j] = min(min_sparse_table[i - 1][j], min_sparse_table[i - 1][j + (1 << (i - 1))]);
            max_sparse_table[i][j] = max(max_sparse_table[i - 1][j], max_sparse_table[i - 1][j + (1 << (i - 1))]);
        }
    }
    return Table{ move(min_sparse_table), move(max_sparse_table) };
}

int find_time_index(int t, const vector<int>& times) {
    auto it = upper_bound(times.begin(), times.end(), t);
    return int(--it - times.begin());
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<double> pitcoin;
    vector<int> times;

    read_file(pitcoin, times);

    Table t = make_sparse_table(pitcoin);

    //stdin
    int M, tB, tE;
    cin >> M;

    for (int i = 0; i < M; i++) {
        cin >> tB >> tE;
        tB = find_time_index(tB, times); // time -> index
        tE = find_time_index(tE, times);
        cout << fixed << setprecision(3);
        cout << t.search_min(tB, tE) << " " << t.search_max(tB, tE) << endl;
    }
}
