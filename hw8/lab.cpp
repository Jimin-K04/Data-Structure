#include <bits/stdc++.h>

using namespace std;

class Student{
    string name;
    vector<int> score_list;
    vector<int> lab_metrics;

public:
    Student() : lab_metrics(5,0) {}

    void set_name(string n) {name = move(n);}
    string get_name() const {return name;}
    int get_metric(int idx) const {return lab_metrics[idx-1];}

    void push_score_list(int k){
        score_list.resize(k);
        for (auto& s : score_list) cin >> s;
    }
    void calc_metrics(){
        lab_metrics[0] = count_if(score_list.begin(), score_list.end(),[](int s){return s != 0;});
        score_list.erase(remove(score_list.begin(), score_list.end(), 0), score_list.end());
        if (score_list.empty()) return; // if vector is empty all metrics are 0..
        lab_metrics[1] = accumulate(score_list.begin(), score_list.end(), 0);
        auto [it_min, it_max] = minmax_element(score_list.begin(), score_list.end());
        lab_metrics[2] = *it_min;
        lab_metrics[3] = *it_max;
        lab_metrics[4] = count_if(score_list.begin(), score_list.end(),[](int s){return s == 100;});
    }
};

int main()
{
    int N, k;
    cin >> N >> k;

    vector<int> priority(5);
    for(auto& x : priority) cin >> x;

    vector<Student> students(N);

    string name;
    for (Student& s : students){
        cin >> name;
        s.set_name(name);
        s.push_score_list(k);
        s.calc_metrics();
    }

    sort(students.begin(), students.end(), [&](const Student& s1, const Student& s2){
            for (int idx : priority){
                if (s1.get_metric(idx) != s2.get_metric(idx)) return s1.get_metric(idx) > s2.get_metric(idx);
            }
            return s1.get_name() > s2.get_name();
         });

    for (Student& s : students) cout << s.get_name() << endl;

}
