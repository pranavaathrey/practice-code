#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x, y;
};

long long distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) 
         + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p1, Point p2, Point p3) {
    long long crossProduct = (p2.x - p1.x) * (p3.y - p2.y) 
                           - (p2.y - p1.y) * (p3.x - p2.x);
    if (crossProduct == 0) return 0;
    return (crossProduct > 0) ? 2 : 1;
}

vector<Point> jarvisMarch(const vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};

    vector<Point> hull;

    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x) 
            leftmost = i;
    }
    int p = leftmost;
    int q = 0;

    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            int o = orientation(points[p], points[i], points[q]);

            if (o == 2 
            || (o == 0 && distSq(points[p], points[i]) 
                        > distSq(points[p], points[q]))) {
                q = i;
            }
        }
        p = q;
    } while (p != leftmost);

    return hull;
}

int main() {
    int n;
    if (!(cin >> n) || n < 0) return 0;
    vector<Point> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y;

    vector<Point> convexHull = jarvisMarch(points);

    cout << convexHull.size() << "\n";
    for (const auto &p : convexHull) 
        cout << p.x << " " << p.y << "\n";
    return 0;
}