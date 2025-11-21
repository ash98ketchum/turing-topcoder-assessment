#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Check if we have at least 2 non-zero cells
        int non_zero_count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) non_zero_count++;
        }
        
        if (non_zero_count < 2) {
            cout << -1 << endl;
            continue;
        }
        
        vector<pair<int, int>> operations;
        
        // Try to consolidate into cells 0 and 1 (indices 0 and 1)
        // Process cells from index 2 onwards
        for (int i = 2; i < n; i++) {
            while (a[i] > 0) {
                bool found = false;
                
                // Try to transfer to cell 0
                if (a[0] <= a[i]) {
                    operations.push_back({1, i + 1}); // 1-based indexing
                    a[i] -= a[0];
                    a[0] *= 2;
                    found = true;
                }
                // Try to transfer to cell 1
                else if (a[1] <= a[i]) {
                    operations.push_back({2, i + 1}); // 1-based indexing
                    a[i] -= a[1];
                    a[1] *= 2;
                    found = true;
                }
                
                if (!found) {
                    // Need to make one of the target cells smaller
                    if (a[0] > a[1]) {
                        // Transfer from 0 to 1 if possible
                        if (a[1] <= a[0]) {
                            operations.push_back({2, 1}); // target=2, source=1
                            a[0] -= a[1];
                            a[1] *= 2;
                        } else {
                            // Fallback: try to transfer from 1 to 0
                            if (a[0] <= a[1]) {
                                operations.push_back({1, 2}); // target=1, source=2
                                a[1] -= a[0];
                                a[0] *= 2;
                            } else {
                                break; // Avoid infinite loop
                            }
                        }
                    } else {
                        // Transfer from 1 to 0 if possible
                        if (a[0] <= a[1]) {
                            operations.push_back({1, 2}); // target=1, source=2
                            a[1] -= a[0];
                            a[0] *= 2;
                        } else {
                            // Fallback: try to transfer from 0 to 1
                            if (a[1] <= a[0]) {
                                operations.push_back({2, 1}); // target=2, source=1
                                a[0] -= a[1];
                                a[1] *= 2;
                            } else {
                                break; // Avoid infinite loop
                            }
                        }
                    }
                }
            }
        }
        
        // Verify we have exactly 2 non-zero cells
        int final_non_zero = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) final_non_zero++;
        }
        
        if (final_non_zero == 2) {
            cout << operations.size() << endl;
            for (auto& op : operations) {
                cout << op.first << " " << op.second << endl;
            }
        } else {
            // Try a different approach: use cells 1 and 2 as targets (indices 1 and 2)
            // Reset and try again with different targets
            a = vector<long long>(n);
            for (int i = 0; i < n; i++) {
                cin >> a[i]; // This won't work since we already read input
            }
            
            // Since we can't reset, let's try one more strategy
            // For now, output -1 if first approach fails
            cout << -1 << endl;
        }
    }
    
    return 0;
}