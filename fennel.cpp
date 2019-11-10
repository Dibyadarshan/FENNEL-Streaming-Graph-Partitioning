#include <bits/stdc++.h>
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
using namespace std;

// Number of partitions
const int k = 5;
const int mx = 1000005;
set<int> partitions[k];
set<int> adjacency[mx];

int main() {
    srand(42);
    
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int number_of_nodes;
        cin >> number_of_nodes;
        for(int j = 0; j < number_of_nodes; ++j) {
            int x;
            cin >> x;
            adjacency[i].insert(x);
        }
    }

    // Ordering of streaming vertices
    vector<int> ordering(n);
    for(int i = 1; i <= n; ++i) {
        ordering[i-1] = i;
    }
    random_shuffle(ordering.begin(), ordering.end());

    for(int i = 0; i < k; ++i) {
        partitions[i].insert(ordering[i]);
    }

    // Streaming vertices
    for(int node_number = k; node_number < n; ++node_number) {
        for(int container = 0; container < k; ++container) {

        }
    }

    for(int i = 0; i < k; ++i) {
        for(auto it: partitions[i]) cout << it << " ";
        cout << "\n";
    }
    return 0;
}