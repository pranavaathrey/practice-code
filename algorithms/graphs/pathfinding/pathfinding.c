#include <stdio.h>
#include <stdlib.h>

int n;
int grid[10][10];
int visited[10][10];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Node {
    int x, y, d;
};

int isValid(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= n)
        return 0;
    if (grid[x][y] == 1 || visited[x][y])
        return 0;
    return 1;
}

int BFSshortestPath() {
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
        return -1;
    struct Node queue[100];
    int front = 0, rear = 0;
    queue[rear++] = (struct Node){0, 0, 1};
    visited[0][0] = 1;

    while (front < rear) {
        struct Node cur = queue[front++];

        if (cur.x == n - 1 && cur.y == n - 1)
            return cur.d;

        for (int i = 0; i < 8; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = 1;
                queue[rear++] = (struct Node){nx, ny, cur.d + 1};
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);
    }
    printf("%d\n", BFSshortestPath());
    return 0;
}