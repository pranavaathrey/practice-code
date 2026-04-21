#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

double direction(Point pi, Point pj, Point pk) {
    return (pk.x - pi.x) * (pj.y - pi.y) 
         - (pj.x - pi.x) * (pk.y - pi.y);
}

bool onSegment(Point pi, Point pj, Point pk) {
    return min(pi.x, pj.x) <= pk.x && pk.x <= max(pi.x, pj.x)
        && min(pi.y, pj.y) <= pk.y && pk.y <= max(pi.y, pj.y);
}

bool segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
    double d1 = direction(p3, p4, p1);
    double d2 = direction(p3, p4, p2);
    double d3 = direction(p1, p2, p3);
    double d4 = direction(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
    &&  ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;

    if (d1 == 0 && onSegment(p3, p4, p1)) return true;
    if (d2 == 0 && onSegment(p3, p4, p2)) return true;
    if (d3 == 0 && onSegment(p1, p2, p3)) return true;
    if (d4 == 0 && onSegment(p1, p2, p4)) return true;
    return false;
}

int main() {
    int n;
    if (!(cin >> n) || n < 0) return 0;

    for (int i = 0; i < n; i++) {
        Point p1, p2, p3, p4;
        cin >> p1.x >> p1.y 
            >> p2.x >> p2.y 
            >> p3.x >> p3.y 
            >> p4.x >> p4.y;
        cout << ((segmentsIntersect(p1, p2, p3, p4)) ? 
                    "Intersect" : "Do Not Intersect");
    }
    return 0;
}