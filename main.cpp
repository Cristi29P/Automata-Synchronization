#include <bits/stdc++.h>

#define EST 0
#define NORD 1
#define VEST 2
#define SUD 3

// Graph structure used for the first 3 exercises
// Credits : Geeks for Geeks
class Graph {
    public:
        std::map<int, bool> visitedNeighbours;
        std::map<int, std::vector<int>> adjacencyList;
        void addEdge(int v1, int v2);
        void DFS(int v);
};

void Graph::addEdge(int v1, int v2) {
    adjacencyList[v1].push_back(v2);
}

void Graph::DFS(int v) {
    visitedNeighbours[v] = true;
    std::vector<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i) {
        if (!visitedNeighbours[*i]) {
            DFS(*i);
        }    
    }
}

void accessible() {
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;
    
    Graph g;
    int vertex;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m ; j++) {
            std::cin >> vertex;
            g.addEdge(i, vertex);
        }
    }

    std::vector<int> start_states;
    int element;
    for (int i = 0; i < s; i++) {
        std::cin >> element;
        start_states.push_back(element);
    }

    for (int start : start_states) {
        if (g.visitedNeighbours[start] == false) {
            g.DFS(start);
        }
    }

    for (const auto& x : g.visitedNeighbours) {
        if (x.second == true) {
            std::cout << x.first << '\n';
        }
    }
}

void productive() {
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;

    Graph g;
    int vertex;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m ; j++) {
            std::cin >> vertex;
            g.addEdge(vertex, i);
        }
    }

    std::vector<int> start_states;
    int element;
    for (int i = 0; i < f; i++) {
        std::cin >> element;
        start_states.push_back(element);
    }

    for (int start : start_states) {
        if (g.visitedNeighbours[start] == false) {
            g.DFS(start);
        }
    }

    for (const auto& x : g.visitedNeighbours) {
        if (x.second == true) {
            std::cout << x.first << '\n';
        }
    }
}

void useful() {
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;

    Graph g1, g2;    // g1- accessible, g2 - productive
    int vertex;

    // Create the two graphs
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m ; j++) {
            std::cin >> vertex;
            g1.addEdge(i, vertex);
            g2.addEdge(vertex, i);
        }
    }

    std::vector<int> start_states_g1;
    int element;
    for (int i = 0; i < s; i++) {
        std::cin >> element;
        start_states_g1.push_back(element);
    }

    std::vector<int> start_states_g2;
    for (int i = 0; i < f; i++) {
        std::cin >> element;
        start_states_g2.push_back(element);
    }

    // do the accessible part
    for (int start : start_states_g1) {
        if (g1.visitedNeighbours[start] == false) {
            g1.DFS(start);
        }
    }

    // do the productive part
    for (int start : start_states_g2) {
        if (g2.visitedNeighbours[start] == false) {
            g2.DFS(start);
        }
    }

    std::vector<int> set_g1, set_g2;
    for (const auto& x : g1.visitedNeighbours) {
        if (x.second == true) {
            set_g1.push_back(x.first);
        }
    }

    for (const auto& x : g2.visitedNeighbours) {
        if (x.second == true) {
            set_g2.push_back(x.first);
        }
    }
    std::vector<int> intersection;

    std::set_intersection(set_g1.begin(), set_g1.end(), set_g2.begin(), set_g2.end(), back_inserter(intersection));

    for (const auto& x : intersection) {
        std::cout << x << '\n';
    }
}

bool dfs_sync(std::vector<std::vector<int>>& my_graph, std::set<std::pair<int, int>>& visited, std::pair<int, int> state, std::vector<int>& sequence, int& size) {
    visited.insert(state);
    if (state.first == state.second) {
        return true;
    }

    for (int i = 0; i != size; ++i) { 
        int next_1 = my_graph[state.first][i];
        int next_2 = my_graph[state.second][i];
        
        auto pair = std::make_pair(next_1, next_2);
        auto iterator = visited.find(pair);

        if (iterator == visited.end()) {
            sequence.push_back(i);
            if (dfs_sync(my_graph, visited, pair, sequence, size)) {
                return true;
            }
            sequence.pop_back();
        }
    }
    return false;
}

bool dfs_restrictive(int source, int& destination, std::set<int>& visited_neigh, std::vector<std::vector<int>> &my_graph, std::vector<int>& sequence) {
    visited_neigh.insert(source);
    int size = my_graph[0].size();
    if (source == destination) {
        return true;
    }
    for (int i = 0; i != size; ++i) {
        int next = my_graph[source][i];
       
        auto iterator = visited_neigh.find(next);
        if (iterator == visited_neigh.end()) {
            sequence.push_back(i);
            if (dfs_restrictive(next, destination, visited_neigh, my_graph, sequence)) {
                return true;
            }
            sequence.pop_back();
        }
    }
    return false;
}

void synchronize() {
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;

    std::vector<std::vector<int>> my_graph;

    // Create the graph
    int vertex;
    for (int i = 0; i < n; i++) {
        std::vector<int> vector;
        for (int j = 0; j < m ; j++) {
            std::cin >> vertex;
            vector.push_back(vertex);
        }
        my_graph.push_back(vector);
    }
    int size = my_graph[0].size();
    std::set<int> initial_states;
    std::vector<int> final_states;

    // Initial states
    if (s == 0) {
        for (int i = 0; i < n; i++) {
            initial_states.insert(i);
        }
    } else {
        for (int i = 0; i < s; i++) {
            std::cin >> vertex;
            initial_states.insert(vertex);
        }
    }

    // Final states
    for (int i = 0; i < f; i++) {
        std::cin >> vertex;
        final_states.push_back(vertex);
    }

     while (initial_states.size() > 1) {
        int first_state = *initial_states.begin();
        initial_states.erase(first_state);
        int second_state = *initial_states.begin();
     
        std::set<std::pair<int, int>> visited_pairs;
        std::vector<int> sequence;      

        dfs_sync(my_graph, visited_pairs, {first_state, second_state}, sequence, size);
        
        for (auto& x : sequence) {
            std::cout << x << std::endl;
            std::set<int> new_dest;
            for (auto& y : initial_states) {
                new_dest.insert(my_graph[y][x]);
            }
            initial_states = new_dest;
        }
    }
    
    int source = *initial_states.begin();
    int destination = final_states.at(0);
    std::vector<int> new_sequence;
    std::set<int> visited_neigh;

    dfs_restrictive(source, destination, visited_neigh, my_graph, new_sequence);

    for (const auto& x : new_sequence) {
        std::cout << x << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide the program name!\n");
        exit(1);
    }

    if (!strcmp("accessible", argv[1])) {
        accessible();
    }

    if (!strcmp("productive", argv[1])) {
        productive();
    }

    if (!strcmp("useful", argv[1])) {
        useful();
    }

    if (!strcmp("synchronize", argv[1])) {
        synchronize();
    }
    return 0;
}
