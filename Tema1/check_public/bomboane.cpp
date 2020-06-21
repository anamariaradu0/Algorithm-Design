#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long uint64;

typedef struct {
	uint64 start;
	uint64 end;
} interval;

class Task {
 public:
	void solve() {
		read_input();
		print_output(compute_solution());
	}

 private:
	unsigned int n, m;
	vector<interval> intervals;

	// [(m+1), n] matrix
	uint64 **matrix;

	void read_input() {
		ifstream fin("bomboane.in");
		fin >> n >> m;
		uint64 start, end;

		for (unsigned int i = 0; i < n; ++i) {
			fin >> start >> end;
			interval interval{start, end};
			intervals.push_back(interval);
		}

		fin.close();
	}

	/*
	* The solution is generated using dynamic programming. More on
	* how it's done in README.
	*/
    uint64 compute_solution() {
		m += 1;
		matrix = new uint64*[m]();
		for (unsigned int i = 0; i < m; ++i) {
			matrix[i] = new uint64[n]();
		}

		// Initialize first column of matrix so that we can compute the next rows.
		for (unsigned int i = intervals[0].start; i <= intervals[0].end; ++i) {
			if (i < m) {
				matrix[i][0] = 1;
			}
		}

		for (unsigned int current_col = 1; current_col < n; ++current_col) {
			for (unsigned int line = 0; line < m; ++line) {
				uint64 candy_sum = 0;

				// Inspect the elements of the previous column and acount possibilities.
				for (unsigned int prev_line = 0; prev_line <= line; ++prev_line) {
					if (line - prev_line >= intervals[current_col].start &&
					line - prev_line <= intervals[current_col].end) {
						candy_sum += (matrix[prev_line][current_col - 1] % 1000000007);
					}
				}

				// Add possibilities to the respective place in matrix.
				matrix[line][current_col] += (candy_sum % 1000000007);
			}
		}

		// Result will be the very last element.
		return matrix[m - 1][n - 1];
    }

	void print_output(uint64 result) {
		ofstream fout("bomboane.out");
		fout << result % 1000000007;
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
