#include <bits/stdc++.h>
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
using namespace std;

const int mx = 1000005;

set<int> adjacency[mx];

int main() {
	srand(42);
	int n, m;
	cin >> n >> m;
	cout << n << "\n";
	for(int i = 1; i <= m; ++i) {
		int x = 1 + rand() % n;
		int y = 1 + rand() % n;
		if(x == y || adjacency[x].find(y) != adjacency[x].end()) {
			--i;
			continue;
		}
		adjacency[x].insert(y);
		adjacency[y].insert(x);
	}
	for(int i = 1; i <= n; ++i) {
		cout << adjacency[i].size() << " ";
		for(auto it: adjacency[i]) {
			cout << it << " ";
		}
		cout << "\n";
	}
	return 0;
}