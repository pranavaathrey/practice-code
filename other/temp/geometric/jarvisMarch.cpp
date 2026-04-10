#include <iostream>
#include <vector>

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

std::vector<Point> jarvisMarch(const std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};

    std::vector<Point> hull;

    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x) {
            leftmost = i;
        }
    }

    int p = leftmost;
    int q = 0;

    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            int o = orientation(points[p], points[i], points[q]);

            if (o == 2 || (o == 0 && distSq(points[p], points[i]) > distSq(points[p], points[q]))) {
                q = i;
            }
        }
        p = q;

    } while (p != leftmost);

    return hull;
}

int main() {
    int n;
    if (!(std::cin >> n) || n < 0) return 0;
    std::vector<Point> points(n);
    for (int i = 0; i < n; i++) std::cin >> points[i].x >> points[i].y;

    std::vector<Point> convexHull = jarvisMarch(points);

    std::cout << convexHull.size() << "\n";
    for (const auto &p : convexHull) {
        std::cout << p.x << " " << p.y << "\n";
    }

    return 0;
}