#include <bits/stdc++.h>
using namespace std;

const int kNmax = 100005;

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

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void APUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[], int time) {
		time += 1;
		int children = 0;
		visited[u] = true;
		disc[u] = time;
		low[u] = time;
		for (int i : adj[u]) { 
			int v = i;
			if (!visited[v]) { 
				children++; 
				parent[v] = u; 
				APUtil(v, visited, disc, low, parent, ap, time);
				low[u]  = min(low[u], low[v]);
				if (parent[u] == -1 && children > 1) 
				ap[u] = true;
				if (parent[u] != -1 && low[v] >= disc[u]) 
				ap[u] = true; 
			}

			else if (v != parent[u]) 
				low[u]  = min(low[u], disc[v]); 
		} 
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/
		bool *visited = new bool[n + 1]; 
		int *disc = new int[n + 1]; 
		int *low = new int[n + 1]; 
		int *parent = new int[n + 1]; 
		bool *ap = new bool[n + 1];
		vector<int> sol;

		for (int i = 1; i <= n; i++) { 
			parent[i] = -1; 
			visited[i] = false; 
			ap[i] = false; 
		}

		int time = 1;
		for (int i = 1; i <= n; i++) 
			if (visited[i] == false) 
				APUtil(i, visited, disc, low, parent, ap, time);
		
		for (int i = 1; i <= n; i++) 
			if (ap[i] == true) 
				sol.push_back(i);

		return sol;
	}

	void print_output(const vector<int>& result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
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
