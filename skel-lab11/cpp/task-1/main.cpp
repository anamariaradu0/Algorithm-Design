#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int kNmax = 1005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
    int C[kNmax][kNmax];
	vector<string> visited;
	vector<int> parent;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
            C[x][y] += z;
		}

		for (int i = 0; i < n + 1; ++i) {
			visited.push_back("white");
			parent.push_back(-1);
		}
		fin.close();
	}

	string bfs() {
		vector<int> d(n + 1);
		// Consider isolated vertices first.
		for (int i = 1; i <= n; ++i) {
			d[i] = -1;
			visited[i] = "white";
		}
		int source = 1;
		// Initialisations
		d[source] = 0;
		visited[source] = "grey";
		queue<int> q;
		q.push(source);
		while (!q.empty()) {
			int top = q.front();

			if (top != n) {
				for (int i = 0; i < adj[top].size(); ++i) {
					if (visited[adj[top][i]] == "white" && C[top][adj[top][i]]) {
						d[adj[top][i]] = d[top] + 1;
						visited[adj[top][i]] = "grey";
						parent[adj[top][i]] = top;
						q.push(adj[top][i]);
					}
				}
			}

			visited[top] = "black";
			q.pop();
		}

		return visited[n];
	}

	int get_result() {
		int flow = 0;
		int cFlow = 0;
		

		while (bfs() != "white") {
			for (int cNode : adj[n]) {
				cFlow = INT32_MAX;
				parent[n] = cNode;

				// From destination until source, going through the "children"
				for (int crtNode = n; crtNode != 1; crtNode = parent[crtNode]) {
					cFlow = min(cFlow, C[parent[crtNode]][crtNode]);
				}

				if (cFlow) {
					for (int crtNode = n; crtNode != 1; crtNode = parent[crtNode]) {
						C[parent[crtNode]][crtNode] -= cFlow;
						C[crtNode][parent[crtNode]] += cFlow;
					}
				}
				flow += cFlow;
			}
		}
		return flow;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
