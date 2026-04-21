#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int row, col;

    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

using Grid = vector<vector<int>>;
using VisitedGrid = vector<vector<bool>>;

const int OBSTACLE = 0;
const int PART_OF_PATH = 1;

const vector<Point> directions = {
    {1, 0},   {0, 1},       // next row, next col
    {-1, 0},  {0, -1}       // prev row, prev col
};

bool isWithinBounds(const Grid& maze, Point p) {
    return p.row >= 0 && p.row < maze.size() && 
           p.col >= 0 && p.col < maze[0].size();
}

bool isWalkable(const Grid& maze, const VisitedGrid& visited, Point p) {
    if(!isWithinBounds(maze, p)) 
        return false;
    if(maze[p.row][p.col] == OBSTACLE) 
        return false;
    if(visited[p.row][p.col]) 
        return false;

    return true;
}

bool findMazePath(const Grid& maze, Grid& path, VisitedGrid& visited, 
                        Point current, Point target) {
    if(!isWalkable(maze, visited, current)) 
        return false;

    visited[current.row][current.col] = true;
    path[current.row][current.col] = PART_OF_PATH;

    if(current == target) 
        return true;

    for(const Point& direction: directions) {
        Point nextPoint = {current.row + direction.row, 
                           current.col + direction.col};
        if(findMazePath(maze, path, visited, nextPoint, target)) 
            return true;
    }
    path[current.row][current.col] = 0; // not part of path
    return false;
}

int main() {
    int rows, cols; cin >> rows >> cols;

    Grid maze(rows, vector<int>(cols));
    for(int r = 0; r < rows; r++) 
        for(int c = 0; c < cols; c++) 
            cin >> maze[r][c];

    Point  start, target;
    cin >> start.row >> start.col 
        >> target.row >> target.col;

    if(!isWithinBounds(maze, start) 
    || !isWithinBounds(maze, target)) 
        return 0;



    Grid           path(rows, vector<int>(cols, 0));
    VisitedGrid visited(rows, vector<bool>(cols, false));

    findMazePath(maze, path, visited, start, target);

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            cout << path[r][c];
            if(c + 1 < cols) 
                cout << " ";
        }
        cout << "\n";
    }
    return 0;
}