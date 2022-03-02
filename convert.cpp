#include <bits/stdc++.h>

#define EST 0
#define NORD 1
#define VEST 2
#define SUD 3

// Find your neighbour and prints its index (if there is no wall)
void print_nodes(int code, int i, int j, int row_size) {
    std::bitset<4> set(code); // encode 4 bit number
    if (!set.test(EST)) {
        std::cout << i * row_size + (j + 1) << ' ';
    } else {
        std::cout << i * row_size + j << ' ';
    } 

    if (!set.test(NORD)) {
        std::cout << (i - 1) * row_size + j << ' ';
    } else {
        std::cout << i * row_size + j << ' ';
    }

    if (!set.test(VEST)) {
        std::cout << i * row_size + (j - 1) << ' ';
    } else {
        std::cout << i * row_size + j << ' ';
    }

    if (!set.test(SUD)) {
        std::cout << (i + 1) * row_size + j << ' ';
    } else {
        std::cout << i * row_size + j << ' ';
    }
    std::cout << std::endl;   
}

void labyrinth() {
    int n, m, s, f, x_pos, y_pos, node;
    std::cin >> n >> m >> s >> f;
    std::vector<std::vector<int>> matrix;
    std::vector<std::pair<int, int>> robots_positions;
    std::vector<std::pair<int, int>> exits;

    // Read matrix
    for (int i = 0; i != n; ++i) {
        std::vector<int> aux;
        for (int j = 0; j != m; ++j) {
            std::cin >> node;
            aux.push_back(node);
        }
        matrix.push_back(aux);
    }
    
    // Read robots positions
    for (int i = 0; i != s; ++i) {
        std::cin >> x_pos >> y_pos;
        robots_positions.push_back({x_pos, y_pos});
    }

    // Read exits positions
    for (int i = 0; i != f; ++i) {
        std::cin >> x_pos >> y_pos;
        exits.push_back({x_pos, y_pos});
    }
    // Print first line
    std::cout << n * m << ' ' << 4 << ' ' << s << ' ' << f << std::endl;
    // Print DFA Struct
    int row_size = matrix.at(0).size();
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; j++) {
            print_nodes(matrix[i][j], i, j, row_size);
        }
    }
    // Print robots positions
    for (const auto& x : robots_positions) {
        std::cout << x.first * row_size + x.second << ' ';
    }
    std::cout << std::endl;
    // Print exits positions
    for (int i = 0; i < exits.size() - 1; i++) {
        std::cout << exits[i].first * row_size + exits[i].second << ' ';
    }
    std::cout << exits[exits.size() - 1].first * row_size + exits[exits.size() - 1].second;
}

int main(int argc, char *argv[]) {
    labyrinth();
    return 0;
}