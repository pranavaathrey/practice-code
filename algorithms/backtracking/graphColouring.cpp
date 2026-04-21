#include <iostream>
#include <vector>

using namespace std;

// Helper function to check if it's safe to assign colour 'c' to vertex 'v'
bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& colour, int c) {
    for (int i = 0; i < graph.size(); i++) {
        // If there is an edge between v and i, and vertex i has the same colour 'c'
        if (graph[v][i] == 1 && colour[i] == c) 
            return false;
    }
    return true;
}

// Recursive utility function to solve the m-colouring problem
bool graphColouringUtil(const vector<vector<int>>& graph, int m, vector<int>& colour, int v) {
    // Base case: If all vertices are assigned a colour, return true
    if (v == graph.size()) {
        return true;
    }
    // Try different colours for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if assignment of colour c to v is valid
        if (isSafe(v, graph, colour, c)) {
            colour[v] = c; // Assign colour

            // Recur to assign colours to the rest of the vertices
            if (graphColouringUtil(graph, m, colour, v + 1)) {
                return true;
            }
            // If assigning colour c doesn't lead to a solution, backtrack
            colour[v] = 0;
        }
    }
    // If no colour can be assigned to this vertex, return false
    return false;
}

// Main function to initiate the backtracking algorithm
void solveGraphColouring(const vector<vector<int>>& graph, int m) {
    int V = graph.size();
    vector<int> colour(V, 0); // Initialize all colour assignments to 0 (uncoloured)

    if (!graphColouringUtil(graph, m, colour, 0)) {
        cout << "Solution does not exist for " << m << " colours." << endl;
        return;
    }
    // Print the solution
    cout << "Solution Exists. The assigned colours are:" << endl;
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " ---> Colour " << colour[i] << endl;
    }
}

int main() {
    /* Create the following graph and test whether it is 3-colourable
      (0)---(1)
       |   / |
       |  /  |
       | /   |
      (3)---(2)
    */
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 0}
    };

    int m = 3; // Number of available colours

    solveGraphColouring(graph, m);

    return 0;
}