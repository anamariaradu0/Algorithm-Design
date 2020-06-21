#include <bits/stdc++.h>
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
    int source, destination;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("p2.in");
        fin >> n >> m >> source >> destination;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back(make_pair(y, w));
        }
        fin.close();
    }

    vector<int> get_result() {
        // TopSort to make it more efficient
        vector<int> topsort;
		vector<int> in_degree(n + 1, 0);
		queue<int> q;

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < (int)adj[i].size(); ++j) {
				++in_degree[adj[i][j].first];
			}
		}

		for (int i = 1; i <= n; ++i) {
			if (in_degree[i] == 0) {
				q.push(i);
			}
		}

		while (!q.empty()) {
			int top = q.front();
			q.pop();
			topsort.push_back(top);

			for (int i = 0; i < (int)adj[top].size(); ++i) {
				if (--in_degree[adj[top][i].first] == 0) {
					q.push(adj[top][i].first);
				}
			}
		}

        vector<int> d(n + 1, kInf);
        d[source] = 0;

        // Looking for distances in TopSort
        for (int i : topsort) {
            for (int j = 0; j < (int)adj[i].size(); ++j) {
                if (d[adj[i][j].first] == kInf ||
                        d[adj[i][j].first] > adj[i][j].second + d[i]) {
                    d[adj[i][j].first] = adj[i][j].second + d[i];
                }
            }
        }

        return d;
    }

    void print_output(vector<int> result) {
        ofstream fout("p2.out");
        fout << result[destination];
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
