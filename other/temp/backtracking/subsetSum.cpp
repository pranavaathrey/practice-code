#include <iostream>
#include <vector>

using namespace std;

void findSubsets(const vector<int> &a, int target, int idx, int sum, vector<int> &picked, vector<vector<int>> &ans) {
    if (idx == (int)a.size()) {
        if (sum == target) ans.push_back(picked);
        return;
    }

    picked.push_back(a[idx]);
    findSubsets(a, target, idx + 1, sum + a[idx], picked, ans);
    picked.pop_back();
    findSubsets(a, target, idx + 1, sum, picked, ans);
}

int main() {
    int n, target;
    if (!(cin >> n >> target) || n < 0) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> picked;
    vector<vector<int>> ans;
    findSubsets(a, target, 0, 0, picked, ans);

    if (ans.empty()) {
        cout << "No subset found\n";
        return 0;
    }

    cout << ans.size() << "\n";
    for (const auto &s : ans) {
        cout << "{ ";
        for (size_t i = 0; i < s.size(); i++) cout << s[i] << (i + 1 == s.size() ? " " : ", ");
        cout << "}\n";
    }
    return 0;
}