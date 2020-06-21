#include <bits/stdc++.h>
using namespace std;

const int kNmax = 50005;
const int kInf = 0x3f3f3f3f;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    int m;
    int source;
    vector<pair<int, int> > adj[kNmax];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m >> source;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back(make_pair(y, w));
        }
        fin.close();
    }

    vector<int> get_result() {
        /*
        TODO: Gasiti distantele minime de la nodul source la celelalte noduri
        folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
            d[node] = costul minim / lungimea minima a unui drum de la source la nodul
        node;
            d[source] = 0;
            d[node] = -1, daca nu se poate ajunge de la source la node.

        Atentie:
        O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
            adj[x][i].first = nodul adiacent lui x,
            adj[x][i].second = costul.

        In cazul in care exista ciclu de cost negativ, returnati un vector gol:
            return vector<int>();
        */
        bool cycle = false;

        queue<int> q;
        vector<int> usedNodesCounter(n + 1, 0);
        vector<int>d(n + 1, kInf);
        vector<int>p(n + 1, -1);
        int cNode;

        p[source] = 0;
        d[source] = 0;

        q.push(source);

        while (!q.empty()) {
            cNode = q.front();
            q.pop();

            ++usedNodesCounter[cNode];
            if (usedNodesCounter[cNode] == n) {
                cycle = true;
                break;
            }
            for (pair<int, int> e : adj[cNode]) {
                if (d[e.first] >= d[cNode] + e.second) {
                    p[e.first] = cNode;
                    d[e.first] = d[cNode] + e.second;
                    q.push(e.first);
                }
            }
        }

        if (cycle) {
            vector<int> emptyVector;
            return emptyVector;
        }

        return d;
    }

    void print_output(vector<int> result) {
        ofstream fout("out");
        if (result.size() == 0) {
            fout << "Ciclu negativ!\n";
        } else {
            for (int i = 1; i <= n; i++) {
                fout << result[i] << ' ';
            }
            fout << '\n';
        }
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
