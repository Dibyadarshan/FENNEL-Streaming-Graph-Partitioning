# FENNEL-Streaming-Graph-Partitioning

All of the following codes have been tested using gcc version is 7.5.0.

### Generating a Randomized Graph
The dataset generation can be done using the following command

`$ cd dataset`

`$ g++ generate_graph.cpp && ./a.out > outputfile`

### Partitioning a Graph
The graph can be partitioned using FENNEL using following command

`$ cd codes`

`$ g++ fennel.cpp && ./a.out > outputfile < ../dataset/inputfile`

Similarly, for running minimum cardinality heuristic

`$ cd codes`

`$ g++ heuristic.cpp && ./a.out > outputfile < ../dataset/inputfile`

Note: The inputfile in these 2 examples should be the dataset. Output file stores the result of the execution.
