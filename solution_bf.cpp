#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

vector<pair<int, int>> path;

bool is_target_state(const vector<ll>& a) {
    int nz = 0;
    for (ll x : a) {
        if (x > 0) nz++;
    }
    return nz == 2;
}

bool iddfs(vector<ll>& a, int current_depth, int max_depth) {
    if (is_target_state(a)) {
        return true;
    }

    if (current_depth == max_depth) {
        return false;
    }

    int n = a.size();

    for (int i = 0; i < n; ++i) {      
        for (int j = 0; j < n; ++j) {  
            if (i == j) continue;

            if (a[i] > 0 && a[j] > 0 && a[j] >= a[i]) {
                
                ll original_target = a[i];
                ll original_source = a[j];

                a[j] -= a[i];
                a[i] *= 2;
                path.push_back({i + 1, j + 1});

                if (iddfs(a, current_depth + 1, max_depth)) {
                    return true;
                }

                path.pop_back();
                a[i] = original_target;
                a[j] = original_source;
            }
        }
    }

    return false;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    int non_zeros = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] > 0) non_zeros++;
    }

    if (non_zeros < 2) {
        cout << -1 << endl;
        return;
    }
    if (non_zeros == 2) {
        cout << 0 << endl;
        return;
    }

    for (int limit = 1; limit <= 9; ++limit) {
        path.clear();
        if (iddfs(a, 0, limit)) {
            cout << path.size() << endl;
            for (auto p : path) {
                cout << p.first << " " << p.second << endl;
            }
            return;
        }
    }

    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while(t--) {
            solve();
        }
    }
    return 0;
}