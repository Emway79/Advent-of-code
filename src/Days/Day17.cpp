#include <queue>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

enum Dir: int32_t {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

struct Edge;

struct Vertex {
    int row;
    int column;
    int32_t cost = INT32_MAX;
    std::vector<Edge> edges;

    bool operator<(const Vertex& o) const {
        return this->cost > o.cost;
    }
};

struct Edge {
    int32_t cost;
    Vertex& destination;
};


namespace AOC2023 {


void addEdges(const int row, const int column, const int minDistance, const int maxDistance, std::vector<std::vector<std::vector<Vertex>>>& graph, const std::vector<std::string>& grid) {
    Vertex& up = graph[row][column][UP];
    up.row = row;
    up.column = column;
    Vertex& down = graph[row][column][DOWN];
    down.row = row;
    down.column = column;

    int32_t upCost = 0;
    int32_t downCost = 0;
    for (int dist = 1; dist <= maxDistance; ++dist) {
        int upY = row - dist;
        int downY = row + dist;
        if (dist < minDistance) {
            if (upY >= 0) {
                upCost += grid[upY][column] - '0';
            }
            if (downY < graph.size()) {
                downCost += grid[downY][column] - '0';
            }
            continue;
        }

        if (upY >= 0) {
            upCost += grid[upY][column] - '0';
            up.edges.push_back({upCost, graph[upY][column][LEFT]});
            up.edges.push_back({upCost, graph[upY][column][RIGHT]});
        }
        if (downY < graph.size()) {
            downCost += grid[downY][column] - '0';
            down.edges.push_back({downCost, graph[downY][column][LEFT]});
            down.edges.push_back({downCost, graph[downY][column][RIGHT]});
        }
    }

    Vertex& left = graph[row][column][LEFT];
    left.row = row;
    left.column = column;
    Vertex& right = graph[row][column][RIGHT];
    right.row = row;
    right.column = column;

    int32_t leftCost = 0;
    int32_t rightCost = 0;
    for (int dist = 1; dist <= maxDistance; ++dist) {
        int leftX = column - dist;
        int rightX = column + dist;
        if (dist < minDistance) {
            if (leftX >= 0) {
                leftCost += grid[row][leftX] - '0';
            }
            if (rightX < graph[0].size()) {
                rightCost += grid[row][rightX] - '0';
            }
            continue;
        }

        if (leftX >= 0) {
            leftCost += grid[row][leftX] - '0';
            left.edges.push_back({leftCost, graph[row][leftX][UP]});
            left.edges.push_back({leftCost, graph[row][leftX][DOWN]});
        }
        if (rightX < graph[0].size()) {
            rightCost += grid[row][rightX] - '0';
            right.edges.push_back({rightCost, graph[row][rightX][UP]});
            right.edges.push_back({rightCost, graph[row][rightX][DOWN]});
        }
    }

}

std::vector<std::vector<std::vector<Vertex>>> createGraph(const std::vector<std::string>& input, const int minDistance, const int maxDistance) {
    std::vector<std::vector<std::vector<Vertex>>> graph(
        input.size(), std::vector<std::vector<Vertex>>(
            input[0].size(), std::vector<Vertex>(
                    4, Vertex()
                )));
    graph[0][0][DOWN].cost = 0;
    graph[0][0][RIGHT].cost = 0;

    for (int row = 0; row < graph.size(); ++row) {
        for (int column = 0; column < graph[0].size(); ++column) {
            addEdges(row, column, minDistance, maxDistance, graph, input);
        }
    }

    return graph;
}


int64_t solveDay17Part1() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day17.txt");
    std::vector<std::vector<std::vector<Vertex>>> graph = createGraph(grid, 1, 3);
    std::priority_queue<Vertex> pq;
    pq.push(graph[0][0][DOWN]);
    pq.push(graph[0][0][RIGHT]);

    while (!pq.empty()) {
        Vertex v = pq.top();
        pq.pop();
        if (v.row == grid.size() - 1 && v.column == grid[0].size() -1) {
            return v.cost;
        }

        for (const Edge& e : v.edges) {
            Vertex& destination = e.destination;
            if (destination.cost > v.cost + e.cost) {
                destination.cost = v.cost + e.cost;
                pq.push(destination);
            }
        }
    }

    return -1;
}

int64_t solveDay17Part2() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day17.txt");
    std::vector<std::vector<std::vector<Vertex>>> graph = createGraph(grid, 4, 10);
    std::priority_queue<Vertex> pq;
    pq.push(graph[0][0][DOWN]);
    pq.push(graph[0][0][RIGHT]);

    while (!pq.empty()) {
        Vertex v = pq.top();
        pq.pop();
        if (v.row == grid.size() - 1 && v.column == grid[0].size() -1) {
            return v.cost;
        }

        for (const Edge& e : v.edges) {
            Vertex& destination = e.destination;
            if (destination.cost > v.cost + e.cost) {
                destination.cost = v.cost + e.cost;
                pq.push(destination);
            }
        }
    }

    return -1;
}


}