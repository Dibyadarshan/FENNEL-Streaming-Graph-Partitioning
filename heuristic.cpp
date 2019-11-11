#include <bits/stdc++.h>
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
using namespace std::chrono; 

// Number of partitions
const int k = 8;
const int mx = 1000005;
set<int> partitions[k];
set<int> adjacency[mx];

// Parameters
double alpha = 0.5;
double gammaPower = 1.5;
const int theta = 4;

double partitionCost(double sz) {
    double cost = 0;
    cost = alpha * pow(sz+1.0, gammaPower) - alpha * pow(sz, gammaPower);
    return cost;
}

int main() {
    IOS;
    srand(42);
    
    int n, m = 0;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int number_of_nodes;
        cin >> number_of_nodes;
        m += number_of_nodes;
        for(int j = 0; j < number_of_nodes; ++j) {
            int x;
            cin >> x;
            adjacency[i].insert(x);
        }
    }
    m /= 2;

    // Results
    vector<int> cutEdge(k, 0);

    // Ordering of streaming vertices
    vector<int> ordering(n);
    for(int i = 1; i <= n; ++i) {
        ordering[i-1] = i;
    }
    random_shuffle(ordering.begin(), ordering.end());

    set<pair<int, int> > cardinality;
    set<pair<int, int> > :: iterator itr;
    map<int, int> partitionSize;

    // Initial paritions
    for(int i = 0; i < k; ++i) {
        partitions[i].insert(ordering[i]);
        cardinality.insert({1, i});
        partitionSize[i] = 1;
    }

    auto start = high_resolution_clock::now(); 

    // Streaming vertices
    for(int node_number = k; node_number < n; ++node_number) {
        int finalPartition = 0, node = ordering[node_number], additionalEdge = 0;
        double objectiveFunctionScore = -1e18;

        itr = cardinality.begin(); 
        for(int i = 0; i < min(k, theta); ++i, ++itr) {
            int container = itr->second;
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
        cardinality.erase({partitionSize[finalPartition], finalPartition});
        ++partitionSize[finalPartition];
        cardinality.insert({partitionSize[finalPartition], finalPartition});
    }

    for(int i = 0; i < k; ++i) {
        cout << "Partition: " << i+1 << "\n"; 
        for(auto it: partitions[i]) cout << it << " ";
        cout << "\n---\n";
    }

    auto stop = high_resolution_clock::now(); 

    double result = 0;
    for(int i = 0; i < k; ++i) {
        DB(cutEdge[i]);
        DB(partitionCost(partitions[i].size()));
        result = ((double) cutEdge[i]) - partitionCost(partitions[i].size());
    }
    DB(result);

    auto duration = duration_cast<microseconds>(stop - start); 
    DB(duration.count());

    return 0;
}