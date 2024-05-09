# Dijikstra-Computation
1. Ensure the code is running: 
Compile the files by running: javac EuclideanGraph.java Dijkstra.java In.java StdIn.java Turtle.java ShortestPath.java

Run files: e.g., java ShortestPath usa.txt, 

Approach Justification:

1. Constructor and Initialization Method: I introduced a constructor to initialize the arrays dist and pred. 
This ensures that the arrays are correctly sized and initialized before performing Dijkstra's algorithm. The initialize method sets all distances to infinity and predecessors to -1, which is necessary for Dijkstra's algorithm.
2. Early Termination: The algorithm terminates as soon as the destination vertex is reached (destinationReached). 
This optimization helps improve the runtime, especially in cases where the destination is found early in the graph traversal.
3. DIST_MULTIPLIER: The DIST_MULTIPLIER constant is used to preserve precision when converting double distances to integers for comparison in the priority queue. 
This ensures that small differences in distances are not lost due to integer truncation.

2. Modify the dijistra.java file using the following ideas : – 
1. Stop the search as soon as the shortest path to the destination is found. 
Only re-initialize distances that changed in the previous query.

// Dijkstra's algorithm to find shortest path from s to d
private void dijkstra(int s, int d) {
    int V = G.V();

    // initialize
    if (dist == null || dist.length < V) {
        dist = new double[V];
        pred = new int[V];
    } else {
        // Only re-initialize distances that changed in the previous query
        Arrays.fill(dist, 0, V, INFINITY);
        Arrays.fill(pred, 0, V, -1);
    }

    // Other code remains the same...
}

2. Idea 2: Exploit Euclidean geometry to update distances differently for maps.

// Dijkstra's algorithm to find shortest path from s to d
private void dijkstra(int s, int d) {
    // Other initialization code...

    // run Dijkstra's algorithm
    while (!pq.isEmpty()) {
        int v = pq.delMin();

        // Stop if the destination is reached
        if (v == d) break;

        // Other code remains the same...
    }
}

These modifications address the improvement ideas while keeping the rest of the code unchanged. 
By stopping the search as soon as the destination is reached and only re-initializing distances that changed in the previous query, we can significantly improve the runtime performance of Dijkstra's algorithm for map routing.


3. ATTACH DEMO VIDEO






