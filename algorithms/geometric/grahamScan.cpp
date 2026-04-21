#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

long long distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r) {
    long long crossProduct = (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
    if (crossProduct == 0) return 0;
    return (crossProduct > 0) ? 2 : 1;
}

vector<Point> grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};

    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[min_idx].y ||
           (points[i].y == points[min_idx].y && points[i].x < points[min_idx].x)) {
            min_idx = i;
        }
    }
    swap(points[0], points[min_idx]);
    Point p0 = points[0];

    sort(points.begin() + 1, points.end(), [&p0](Point p1, Point p2) {
        int o = orientation(p0, p1, p2);
        if (o == 0) {
            return distSq(p0, p1) < distSq(p0, p2);
        }
        return o == 2;
    });

    vector<Point> filtered;
    filtered.push_back(points[0]);
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0) {
            i++;
        }
        filtered.push_back(points[i]);
    }

    if (filtered.size() < 3) return {};

    vector<Point> hull;
    hull.push_back(filtered[0]);
    hull.push_back(filtered[1]);
    hull.push_back(filtered[2]);

    for (size_t i = 3; i < filtered.size(); i++) {
        while (hull.size() > 1 &&
               orientation(hull[hull.size() - 2], hull.back(), filtered[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(filtered[i]);
    }

    return hull;
}

int main() {
    int n;
    if (!(cin >> n) || n < 0) return 0;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;

    vector<Point> convexHull = grahamScan(points);

    cout << convexHull.size() << "\n";
    for (const auto &p : convexHull) {
        cout << p.x << " " << p.y << "\n";
    }

    return 0;
}