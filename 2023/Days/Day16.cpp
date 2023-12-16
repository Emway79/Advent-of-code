#include <queue>

#include "Day.hpp"
#include "../Libraries/utils.hpp"

enum Dir: int {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
};

struct Laser {
    int row;
    int column;
    Dir dir;
};

namespace AOC2023 {

int64_t countEnergized(const std::vector<std::string>& grid) {
    int64_t result = 0;
    for (auto row = 0; row < grid.size(); ++row) {
        for (auto column = 0; column < grid[0].size(); ++column) {
            if (grid[row][column] == '#') {
                ++result;
            }
        }
    }

    return result;
}

void mirrorLaser(Laser& laser, bool slash) {
    if (slash) {
        switch (laser.dir) {
            case Up: { laser.dir = Right; break; }
            case Down: { laser.dir = Left; break; }
            case Left: { laser.dir = Down; break; }
            case Right: { laser.dir = Up; break; }
        }
    } else {
        switch (laser.dir) {
            case Up: { laser.dir = Left; break; }
            case Down: { laser.dir = Right; break; }
            case Left: { laser.dir = Up; break; }
            case Right: { laser.dir = Down; break; }
        }
    }
}

void increaseBeam(Laser& laser) {
    switch (laser.dir) {
        case Up: { --laser.row; break; }
        case Down: { ++laser.row; break; }
        case Left: { --laser.column; break; }
        case Right: { ++laser.column; break; }
    }
}

std::vector<std::string> energize(Laser start, const std::vector<std::string>& grid) {
    std::vector<std::string> result = grid;
    std::queue<Laser> queue;
    queue.push(start);
    int64_t iteration = 0;

    while(!queue.empty()) {
        ++iteration;
        if (iteration == 1000000) {
            break;
        }
        Laser laser = queue.front();
        queue.pop();

        nextLocation:
        if (laser.row < 0 || laser.row >= grid.size() || laser.column < 0 || laser.column >= grid[0].size()) {
            continue;
        }
        result[laser.row][laser.column] = '#';

        switch(grid[laser.row][laser.column]) {
            case '\\': {
                mirrorLaser(laser, false);
                increaseBeam(laser);
                break;
            }
            case '/': {
                mirrorLaser(laser, true);
                increaseBeam(laser);
                break;
            }
            case '|': {
                if (laser.dir == Up || laser.dir == Down) {
                    goto defaultBranch;
                }

                Laser split = laser;
                split.dir = Up;
                increaseBeam(split);
                queue.push(split);

                laser.dir = Down;
                increaseBeam(laser);
                break;
            }
            case '-': {
                if (laser.dir == Left || laser.dir == Right) {
                    goto defaultBranch;
                }

                Laser split = laser;
                split.dir = Left;
                increaseBeam(split);
                queue.push(split);

                laser.dir = Right;
                increaseBeam(laser);
                break;
            }
            default: {
                defaultBranch:
                increaseBeam(laser);
                goto nextLocation;
            }
        }

        queue.push(laser);
    }

    return result;
}

int64_t solveDay16Part1() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day16.txt");

    grid = energize({0, 0, Right}, grid);
    int64_t result = countEnergized(grid);

    return result;
}

int64_t solveDay16Part2() {
    std::vector<std::string> grid = utils::readFileLines("..\\Resources\\day16.txt");
    int64_t result = 0;

    for (auto row = 0; row < grid.size(); ++row) {
        result = std::max(result, countEnergized(energize({row, 0, Right}, grid)));
        result = std::max(result, countEnergized(energize({row, (int) grid[0].size() - 1, Left}, grid)));
    }

    for (auto column = 0; column < grid[0].size(); ++column) {
        result = std::max(result, countEnergized(energize({0, column, Down}, grid)));
        result = std::max(result, countEnergized(energize({(int) grid.size(), column, Up}, grid)));
    }

    return result;
}

}