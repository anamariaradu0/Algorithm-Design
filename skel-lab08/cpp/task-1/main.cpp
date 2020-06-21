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
	vector<int> adj_trans[kNmax];
	vector<int> partial_sol;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj_trans[y].push_back(x);
		}
		fin.close();
	}

	void aux_conex(vector<vector<int>> &sol, int u, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &isInStack, int &time) {
		time += 1;
		disc[u] = time;
		low[u] = time;
		st.push(u); 
		isInStack[u] = true; 
	
		for (int i : adj[u]) { 
			int v = i;
	
			if (disc[v] == -1) { 
				aux_conex(sol, v, disc, low, st, isInStack, time);
				low[u]  = min(low[u], low[v]); 
			} else if (isInStack[v] == true) {
				low[u]  = min(low[u], disc[v]); 
			}
				
		}	 

		int w = 0;
		if (low[u] == disc[u]) {
			vector<int> partial_sol;
			while (st.top() != u) { 
				w = st.top(); 
				partial_sol.push_back(w);
				isInStack[w] = false; 
				st.pop(); 
			}
			w = st.top(); 
			partial_sol.push_back(w);
			isInStack[w] = false; 
			st.pop(); 
			sol.push_back(partial_sol);
		}
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.

		Atentie: graful transpus este stocat in adjt.
		*/
		vector<vector<int>> sol;
		vector<int> disc(n + 1);
		vector<int> low(n + 1);
		vector<bool> isInStack(n + 1);
		stack<int> s;

		for (int i = 1; i <= n; ++i) {
			disc[i] = -1;
			low[i] = -1;
			isInStack[i] = false;
		}

		int time = 1;
		for (int i = 1; i <= n; ++i) {
			if (disc[i] == -1) {
				aux_conex(sol, i, disc, low, s, isInStack, time);
			}
		}
		
		return sol;
	}

	void print_output(const vector<vector<int>>& result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
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
