#include <queue>
#include <array>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

enum Dir : uint32_t {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct Node {
    uint32_t row;
    uint32_t column;
    uint32_t distance;
    Dir dir;

    bool operator<(const Node& o) const {
        return this->distance > o.distance;
    }
};

namespace AOC2023 {

std::vector<std::vector<std::array<Node, 4>>> createGraph(const std::vector<std::string>& grid) {
    std::vector<std::vector<std::array<Node, 4>>> graph(grid.size(), std::vector<std::array<Node, 4>>(grid[0].size(), std::array<Node, 4>()));
    for (uint32_t row = 0; row < grid.size(); ++row) {
        for (uint32_t column = 0; column < grid[0].size(); ++column) {
            graph[row][column][UP] = {row, column, UINT32_MAX, UP};
            graph[row][column][DOWN] = {row, column, UINT32_MAX, DOWN};
            graph[row][column][LEFT] = {row, column, UINT32_MAX, LEFT};
            graph[row][column][RIGHT] = {row, column, UINT32_MAX, RIGHT};
        }
    }

    graph[0][0][DOWN].distance = 0;
    graph[0][0][RIGHT].distance = 0;
    return graph;
}

void updateQueue(Node& node, std::priority_queue<Node>& pq, const std::vector<std::string>& grid, std::vector<std::vector<std::array<Node, 4>>>& graph, int minDistance, int maxDistance) {
    uint32_t inc = node.distance;
    switch (node.dir) {
        case UP: {
            for (int32_t row = node.row - 1; row >= 0 && row >= node.row - 3; --row) {
                inc += grid[row][node.column] - '0';
                if (inc < graph[row][node.column][LEFT].distance) {
                    graph[row][node.column][LEFT].distance = inc;
                    pq.push(graph[row][node.column][LEFT]);
                }
                if (inc < graph[row][node.column][RIGHT].distance) {
                    graph[row][node.column][RIGHT].distance = inc;
                    pq.push(graph[row][node.column][RIGHT]);
                }
            }
            break;
        }

        case DOWN: {
            for (int32_t i = node.row + 1; i < grid.size() && i <= node.row + 3; ++i) {
                inc += grid[i][node.column] - '0';
                if (inc < graph[i][node.column][LEFT].distance) {
                    graph[i][node.column][LEFT].distance = inc;
                    pq.push(graph[i][node.column][LEFT]);
                }
                if (inc < graph[i][node.column][RIGHT].distance) {
                    graph[i][node.column][RIGHT].distance = inc;
                    pq.push(graph[i][node.column][RIGHT]);
                }
            }
            break;
        }

        case LEFT: {
            for (int32_t i = node.column - 1; i >= 0 && i >= node.column - 3; --i) {
                inc += grid[node.row][i] - '0';
                if (inc < graph[node.row][i][UP].distance) {
                    graph[node.row][i][UP].distance = inc;
                    pq.push(graph[node.row][i][UP]);
                }
                if (inc < graph[node.row][i][DOWN].distance) {
                    graph[node.row][i][DOWN].distance = inc;
                    pq.push(graph[node.row][i][DOWN]);
                }
            }
            break;
        }

        case RIGHT: {
            for (int32_t i = node.column + 1; i < grid[0].size() && i <= node.column + 3; ++i) {
                inc += grid[node.row][i] - '0';
                if (inc < graph[node.row][i][UP].distance) {
                    graph[node.row][i][UP].distance = inc;
                    pq.push(graph[node.row][i][UP]);
                }
                if (inc < graph[node.row][i][DOWN].distance) {
                    graph[node.row][i][DOWN].distance = inc;
                    pq.push(graph[node.row][i][DOWN]);
                }
            }
            break;
        }
    }
}

int64_t solveDay17Part1() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day17.txt");
    std::vector<std::vector<std::array<Node, 4>>> graph = createGraph(grid);
    std::priority_queue<Node> pq;
    pq.push(graph[0][0][DOWN]);
    pq.push(graph[0][0][RIGHT]);

    while(!pq.empty() && pq.top().distance != UINT32_MAX) {
        Node node = pq.top();
        pq.pop();

        if (node.row == grid.size() - 1 && node.column == grid[0].size() - 1) {
            return node.distance;
        }

        updateQueue(node, pq, grid, graph, 1, 3);
    }

    return UINT32_MAX;
}

int64_t solveDay17Part2() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day17.txt");
    std::vector<std::vector<std::array<Node, 4>>> graph = createGraph(grid);
    std::priority_queue<Node> pq;
    pq.push(graph[0][0][DOWN]);
    pq.push(graph[0][0][RIGHT]);

    while(!pq.empty() && pq.top().distance != UINT32_MAX) {
        Node node = pq.top();
        pq.pop();

        if (node.row == grid.size() - 1 && node.column == grid[0].size() - 1) {
            return node.distance;
        }

        updateQueue(node, pq, grid, graph, 4, 10);
    }
    
    return UINT32_MAX;
}


}