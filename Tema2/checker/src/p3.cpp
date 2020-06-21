#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

const int kNmax = 100005;
const int kInf = 0x3f3f3f3f;


/*
* SOURCE: My own solution to task-1 lab-9
*/
class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    int source = 1;
    int destination;
    double energy;
    vector<pair<int, double> > adj[kNmax];
    vector<bool> paths;
    vector<int> parent;

    void read_input() {
        ifstream fin("p3.in");
        fin >> n >> m >> energy;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back(make_pair(y, w));
        }
        destination = n;
        fin.close();
    }

    vector<double> get_result() {
        vector<double> d(n + 1, 0.00);
        for (int i = 0; i < n + 1; ++i) {
            paths.push_back(false);
            parent.push_back(-1);
        }

        int cNode;

        priority_queue<int, vector<int>> pq;
        d[source] = (double)energy;
        pq.emplace(source);

        while (!pq.empty()) {
            cNode = pq.top();
            paths[cNode] = true;
            pq.pop();
            for (pair<int, double> next : adj[cNode]) {
                double e = (double)(1.00 - (double)(next.second / 100.00));
                if (d[next.first] < e * d[cNode]) {
                    d[next.first] = (double)e * d[cNode];
                    parent[next.first] = cNode;
                    pq.emplace(next.first);
                }
            }
        }

        return d;
    }

    void print_output(vector<double> result) {
        ofstream fout("p3.out");
        fout << setprecision(13) << result[destination];
        fout << "\n";
        int node = destination;
        vector<int> p;
        while (parent[node] != -1) {
            p.push_back(node);
            node = parent[node];
        }
        p.push_back(1);
        for (int i = p.size() - 1; i >= 0; --i) {
            fout << p[i] << " ";
        }
        fout << "\n";
        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
