#include <bits/stdc++.h>
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
using namespace std;

// Number of partitions
const int k = 5;
const int mx = 1000005;
set<int> partitions[k];
set<int> adjacency[mx];

// Parameters
double alpha = 0.5;
double gammaPower = 2.0;

double partitionCost(double sz) {
    double cost = 0;
    cost = alpha * pow(sz+1.0, gammaPower) - alpha * pow(sz, gammaPower);
    return cost;
}

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

    // Results
    vector<int> cutEdge(k);

    // Ordering of streaming vertices
    vector<int> ordering(n);
    for(int i = 1; i <= n; ++i) {
        ordering[i-1] = i;
    }
    random_shuffle(ordering.begin(), ordering.end());

    // Initial paritions
    for(int i = 0; i < k; ++i) {
        partitions[i].insert(ordering[i]);
    }

    // Streaming vertices
    for(int node_number = k; node_number < n; ++node_number) {
        int finalPartition = 0, node = ordering[node_number], additionalEdge = 0;
        double objectiveFunctionScore = -1e18; 
        for(int container = 0; container < k; ++container) {
            double intraPartition = partitionCost((int)partitions[container].size());
            int interPartition = 0;

            for(auto neighbours: adjacency[node]) {
                if(partitions[container].find(neighbours) != partitions[container].end()) {
                    ++interPartition;
                }
            }
            // DB(interPartition);
            // DB(intraPartition);
            if(((double)interPartition) - intraPartition > objectiveFunctionScore) {
                objectiveFunctionScore = interPartition - intraPartition;
                finalPartition = container;
                additionalEdge = interPartition;
            }
        }
        partitions[finalPartition].insert(node);
        cutEdge[finalPartition] += additionalEdge;
    }

    for(int i = 0; i < k; ++i) {
        cout << "Partition: " << i+1 << "\n"; 
        for(auto it: partitions[i]) cout << it << " ";
        cout << "\n---\n";
    }

    double result = 0;
    for(int i = 0; i < k; ++i) {
        DB(cutEdge[i]);
        DB(partitionCost(partitions[i].size()));
        result = ((double) cutEdge[i]) - partitionCost(partitions[i].size());
    }
    cout << "Objective function score: " << result << "\n";
    return 0;
}