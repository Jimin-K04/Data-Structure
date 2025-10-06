#include <bits/stdc++.h>
using namespace std;

struct Person { string GARD_CODE; int ID, COTE_SCORE;
    bool operator<(const Person& b) const {
        if (COTE_SCORE != b.COTE_SCORE) return COTE_SCORE > b.COTE_SCORE;
        return ID > b.ID;
    }
};

struct KeyRow { string gard; int sz; long long sum;
    bool operator<(const KeyRow& b) const {
       return sz!=b.sz ? sz>b.sz : (sum!=b.sum ? sum>b.sum : gard<b.gard);
    }
};
unordered_map<string, vector<Person>> p_list;

unordered_map<string, long long> total_score;

void push_data(Person p) {
    total_score[p.GARD_CODE] += p.COTE_SCORE;
    auto& s = p_list[p.GARD_CODE];
    auto insert_pos = lower_bound(s.begin(), s.end(), p);

    s.insert(insert_pos, move(p));
}

void pop_data(int s, int e, int k) {
    vector<KeyRow> canu;
    canu.reserve(p_list.size());

    for (auto &kr : p_list){
        int sz = kr.second.size();
        if (sz >= k) canu.push_back({kr.first, sz, total_score[kr.first]});
    }

    if (canu.empty()) return;

    sort(canu.begin(), canu.end());
    int c_e = canu.size(), q = 0, skip = s, need = e-s+1, cnt;

    auto p_list_copy = p_list;
    bool printed = false;

    while (skip > 0) {
        cnt = 0;
        for (int i = 0; i < c_e; ++i)
            if (p_list_copy[canu[i].gard].size() > q) ++cnt;
        if (!cnt) break;
        if (skip >= cnt) { skip -= cnt; ++q; }
        else break;
    }

    for (; need > 0; q++){
        int any = 0;
        for (int i = 0; i < c_e; ++i)
            if (p_list_copy[canu[i].gard].size() > q) { any = 1; break; }
        if (!any) break;

        for (int r = 0; r < c_e && need > 0; r++){
            string key = canu[r].gard;
            auto &vec = p_list_copy[key];
            if (vec.size() <= q) continue;

            if (skip > 0) { --skip; continue; }
            int target = vec[q].ID;
            cout << target << ' ';
            printed = true;
            --need;

            auto &orig = p_list[key];
            auto it = find_if(orig.begin(), orig.end(), [&](const Person &x){return x.ID == target;});
            total_score[key] -= it->COTE_SCORE;
            orig.erase(it);
        }
    }
     if (printed) cout << '\n';
}
int main()
{
    int N, k, score, id, start, end;
    cin >> N >> k;

    string cmp;
    while (N--) {
        cin >> cmp;

        if (cmp == "POP") {
            cin >> start >> end;
            pop_data(--start, --end, k);
        }
        else {
            cin >> id >> score;
            push_data({ cmp, id, score });
        }
    }
}

