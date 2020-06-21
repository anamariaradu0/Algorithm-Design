#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

typedef struct {
	int start;
	int end;
} interval;

/*
* The pairs of intervals are sorted in ascending order of their start and,
* if equal, in descending order of their end.
*/
struct {
	bool operator() (interval interval1, interval interval2) const {
		if (interval1.start < interval2.start) {
			return true;
		}

		if (interval1.start > interval2.start) {
			return false;
		}

		if (interval1.start == interval2.start) {
			if (interval1.end < interval2.end) {
				return false;
			} else if (interval1.end > interval2.end) {
				return true;
			}
		}

		return false;
	}
} operate;

class Task {
 public:
	void solve() {
		read_input();
        compute_solution();
		print_output();
	}

 private:
	int n;
	vector<interval> pairs;
	int solution;

	void read_input() {
		ifstream fin("gard.in");
		fin >> n;
		for (int i = 0; i < n; ++i) {
			int start, end;
			fin >> start >> end;
			interval pair{start, end};
			pairs.push_back(pair);
		}
		fin.close();
	}

	/*
	* After sorting, the first interval is set for comparison.
	* It is changed when the ending point of an interval becomes greater
	* than the ending point of cmp.
	*/
    void compute_solution() {
		sort(pairs.begin(), pairs.end(), operate);

		vector<int> cmp;
		cmp.push_back(pairs[0].start);
		cmp.push_back(pairs[0].end);

		for (int i = 1; i < n; ++i) {
			if (pairs[i].start >= cmp[0] && pairs[i].end <= cmp[1]) {
				++solution;
			} else if (pairs[i].end > cmp[1]) {
				cmp[0] = pairs[i].start;
				cmp[1] = pairs[i].end;
			}
		}
    }

	void print_output() {
		ofstream fout("gard.out");
		fout << solution;
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
