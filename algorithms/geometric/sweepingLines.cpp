#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

// --- Geometric Primitives and Intersection Logic ---

struct Point {
    double x, y;
};

struct Segment {
    Point p1, p2;
    int id;
};

// Determines the orientation of the ordered triplet (p, q, r).
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if(abs(val) < EPS) return 0; 
    return (val > 0) ? 1 : 2;
}

// Checks if point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) + EPS && q.x >= min(p.x, r.x) - EPS &&
           q.y <= max(p.y, r.y) + EPS && q.y >= min(p.y, r.y) - EPS;
}

// Returns true if segment s1 and s2 intersect
bool doIntersect(const Segment& s1, const Segment& s2) {
    Point p1 = s1.p1, q1 = s1.p2;
    Point p2 = s2.p1, q2 = s2.p2;

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if(o1 != o2 && o3 != o4) return true;

    // Collinear cases
    if(o1 == 0 && onSegment(p1, p2, q1)) return true;
    if(o2 == 0 && onSegment(p1, q2, q1)) return true;
    if(o3 == 0 && onSegment(p2, p1, q2)) return true;
    if(o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// --- Sweep-line Data Structures ---

struct Event {
    double x, y;
    bool is_left;
    int seg_id;

    // Line 2: Sort endpoints from left to right, left before right, lower y first.
    bool operator<(const Event& other) const {
        if(abs(x - other.x) > EPS)
            return x < other.x;
        if(is_left != other.is_left)
            return is_left > other.is_left; // true (left) > false (right)
        return y < other.y;
    }
};

// Global sweep line x-coordinate used by the set comparator
double current_x;

struct SegmentComparator {
    bool operator()(const Segment* s1, const Segment* s2) const {
        if(s1->id == s2->id) return false;
        
        // Evaluate the y-coordinate of the segments at the current sweep line x
        double y1 = s1->p1.y + (s1->p2.y - s1->p1.y) * (current_x - s1->p1.x) / (s1->p2.x - s1->p1.x);
        double y2 = s2->p1.y + (s2->p2.y - s2->p1.y) * (current_x - s2->p1.x) / (s2->p2.x - s2->p1.x);
        
        if(abs(y1 - y2) > EPS)
            return y1 < y2;
        return s1->id < s2->id; // Tie breaker for segments intersecting exactly at current_x
    }
};

// --- Algorithm Implementation ---

bool anySegmentsIntersect(vector<Segment>& segments) {
    int n = segments.size();
    if(n == 0) return false;

    vector<Event> events;
    
    // Normalize segments so p1 is always the left endpoint
    for(int i = 0; i < n; ++i) {
        segments[i].id = i;
        if(segments[i].p1.x > segments[i].p2.x 
        || (abs(segments[i].p1.x - segments[i].p2.x) < EPS
        && segments[i].p1.y > segments[i].p2.y)) {
            swap(segments[i].p1, segments[i].p2);
        }
        events.push_back({segments[i].p1.x, segments[i].p1.y, true, i});
        events.push_back({segments[i].p2.x, segments[i].p2.y, false, i});
    }
    sort(events.begin(), events.end());

    set<const Segment*, SegmentComparator> T;
    vector<set<const Segment*, SegmentComparator>::iterator> active_iters(n);

    for(const auto& event : events) {
        current_x = event.x;
        int id = event.seg_id;
        const Segment* s = &segments[id];

        if(event.is_left) {
            auto result = T.insert(s);
            auto it = result.first;
            active_iters[id] = it;

            auto next_it = next(it);
            if(next_it != T.end() && doIntersect(*s, **next_it)) 
                return true; 
            if(it != T.begin()) {
                auto prev_it = prev(it);
                if(doIntersect(*s, **prev_it)) 
                    return true; 
            }
        } 
        else {
            auto it = active_iters[id];

            if(it != T.end() && it != T.begin()) {
                auto next_it = next(it);
                auto prev_it = prev(it);
                
                if(next_it != T.end() && doIntersect(**prev_it, **next_it)) 
                    return true; 
            }
            T.erase(it);
        }
    }
    return false;
}

int main() {
    // Example dataset: 3 segments, two of which intersect.
    vector<Segment> segments = {
        {{1, 5}, {5, 5}, 0},
        {{2, 4}, {4, 6}, 0},
        {{6, 1}, {8, 3}, 0}
    };

    if(anySegmentsIntersect(segments)) {
        cout << "Intersection found: TRUE\n";
    } else {
        cout << "No intersections: FALSE\n";
    }

    return 0;
}