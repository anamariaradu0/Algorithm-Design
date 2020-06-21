#include <bits/stdc++.h>
using namespace std;

const int kNmax = 2e5 + 10;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    vector<pair<int, int>> adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        fin.close();
    }

    static bool sort_pairs(const pair<int,int> &t1, const pair<int,int> &t2) {
        return (t1.second < t2.second);
    }

    int get_result() {
        /*
        TODO: Calculati costul minim al unui arbore de acoperire
        folosind algoritmul lui Prim.
        */
        int cost = 0;
        vector<int> d(n + 1);
        vector<int> p(n + 1);
        vector<int> v(n + 1);

        for (int i = 1; i <= n; ++i) {
            d[i] = kNmax;
            p[i] = 0;
            v[i] = false;
        }

        d[1] = true;

        auto compare = [](pair<int,int> &a, pair<int,int> &b) { return a.second > b.second; };
        priority_queue<pair<int,int>, vector<pair<int, int>>, decltype(compare)> pq(compare);

        for (pair<int, int> e : adj[1]) {
            pq.emplace(e);
        }

        pair<int, int> e;
        while (!pq.empty()) {
            e = pq.top();
            pq.pop();

            if (!v[e.first]) {
                cost += e.second;
                v[e.first] = true;

                for (pair<int, int> e2 : adj[e.first]) {
                    if (e2.second < d[e2.first]) {
                        d[e2.first] = e2.second;
                        p[e2.first] = e.first;
                        pq.emplace(e2);
                    }
                }
            }
        }

        return cost - d[1];
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
