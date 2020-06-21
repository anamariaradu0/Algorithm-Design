#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long uint64;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int instructions, len;

	// Computing 2^(len - 1);
	uint64 first_case(uint64 base, uint64 power, uint64 mod) {
		uint64 res;
		switch (power) {
			case 0:
				return 1;
			case 1:
				return base;
			default:
				res = first_case(base, power / 2, mod);
				res = (1LL * (res * (res % mod))) % mod;
				if (power % 2 == 1) {
					res = (1LL * (res * (base % mod))) % mod;
				}
		}

		return res;
	}

	// Recurively computing the solution for the second case
	int second_case() {
		unsigned int total = 0;
		unsigned int prev10 = 1;
		unsigned int curr10 = 0;
		unsigned int prev50 = 1;
		unsigned int curr50 = 0;
		unsigned int prev100 = 1;
		unsigned int curr100 = 0;
		unsigned int prev200 = 1;
		unsigned int curr200 = 0;
		unsigned int prev500 = 1;
		unsigned int curr500 = 0;

		// Naive case
		if (len == 1) {
			return 5;
		}

		/*
		* For each step, counting how many bancnotes of each kind there are
		* based on the previous step.
		*/
		for (int i = 0; i < len - 1; ++i) {
			curr10 = prev50 + prev100 + prev500;
			curr50 = prev10 + prev200;
			curr100 = prev10 + prev100 + prev200;
			curr200 = prev50 + prev500;
			curr500 = prev200;

			prev10 = curr10 % 1000000007;
			prev50 = curr50 % 1000000007;
			prev100 = curr100 % 1000000007;
			prev200 = curr200 % 1000000007;
			prev500 = curr500 % 1000000007;
		}

		// The result is the sum of all bancnotes for the last step.
		total += curr10 % 1000000007;
		total += curr50 % 1000000007;
		total += curr100 % 1000000007;
		total += curr200 % 1000000007;
		total += curr500 % 1000000007;

		return total % 1000000007;
	}

    void read_input() {
        ifstream fin("bani.in");
		fin >> instructions >> len;
		fin.close();
    }

	void print_output(int result) {
		ofstream fout("bani.out");
		fout << result % 1000000007;
		fout.close();
	}

	/*
	* For the first case the program finds a linear solution, as described in README.
	* For the second case, the solution is recursive (in the sense that it depends on
	* the results from the previous step); also detailed in README.
	*/
    int get_result() {
		if (instructions == 1) {
			unsigned int result;
			result = first_case(2, (len - 1), 1000000007);
			return  (1LL * 5 * result) % 1000000007;
		} else if (instructions == 2) {
			return second_case();
		}

		return 0;
    }
};

int main() {
    Task task;
    task.solve();
    return 0;
}
