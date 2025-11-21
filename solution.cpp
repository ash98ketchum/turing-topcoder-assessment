#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;

struct State {
    vector<ll> cells;
    vector<pair<int, int>> history;

    bool operator<(const State& other) const {
        return cells < other.cells;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<ll> start_cells(n);
    int non_zeros = 0;
    for (int i = 0; i < n; ++i) {
        cin >> start_cells[i];
        if (start_cells[i] > 0) non_zeros++;
    }

    if (non_zeros < 2) {
        cout << -1 << endl;
        return; 
    }

    queue<State> q;
    q.push({start_cells, {}});

    set<vector<ll>> visited;
    visited.insert(start_cells);
    int visited_limit = 200000; 

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int nz = 0;
        for (ll x : current.cells) {
            if (x > 0) nz++;
        }

        if (nz == 2) {
            cout << current.history.size() << endl;
            for (auto p : current.history) {
                cout << p.first << " " << p.second << endl;
            }
            return;
        }

        if (visited.size() > visited_limit) break;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (current.cells[j] >= current.cells[i] && current.cells[i] > 0) {
                    State next_state = current;
                    next_state.cells[j] -= next_state.cells[i];
                    next_state.cells[i] *= 2;
                    
                    next_state.history.push_back({i + 1, j + 1});

                    if (visited.find(next_state.cells) == visited.end()) {
                        visited.insert(next_state.cells);
                        q.push(next_state);
                    }
                }
            }
        }
    }

    cout << -1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; 
    cin >> t;

    while(t--){
        solve();
    }
    return 0;
}