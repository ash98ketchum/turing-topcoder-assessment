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
        
        // Limit total operations to avoid infinite loops
        const int MAX_OPERATIONS = 20000;
        int op_count = 0;
        
        // Try to consolidate into cells 0 and 1
        bool success = true;
        
        for (int i = 2; i < n && op_count < MAX_OPERATIONS; i++) {
            while (a[i] > 0 && op_count < MAX_OPERATIONS) {
                bool transferred = false;
                
                // Try to transfer to cell 0
                if (a[0] <= a[i]) {
                    operations.push_back({1, i + 1});
                    a[i] -= a[0];
                    a[0] *= 2;
                    transferred = true;
                    op_count++;
                }
                // Try to transfer to cell 1
                else if (a[1] <= a[i]) {
                    operations.push_back({2, i + 1});
                    a[i] -= a[1];
                    a[1] *= 2;
                    transferred = true;
                    op_count++;
                }
                
                if (!transferred) {
                    // Need to make one of the targets smaller
                    if (a[0] > a[1]) {
                        if (a[1] <= a[0]) {
                            operations.push_back({2, 1});
                            a[0] -= a[1];
                            a[1] *= 2;
                            transferred = true;
                            op_count++;
                        } else {
                            // Try alternative: transfer from 1 to 0
                            if (a[0] <= a[1]) {
                                operations.push_back({1, 2});
                                a[1] -= a[0];
                                a[0] *= 2;
                                transferred = true;
                                op_count++;
                            }
                        }
                    } else {
                        if (a[0] <= a[1]) {
                            operations.push_back({1, 2});
                            a[1] -= a[0];
                            a[0] *= 2;
                            transferred = true;
                            op_count++;
                        } else {
                            // Try alternative: transfer from 0 to 1
                            if (a[1] <= a[0]) {
                                operations.push_back({2, 1});
                                a[0] -= a[1];
                                a[1] *= 2;
                                transferred = true;
                                op_count++;
                            }
                        }
                    }
                    
                    // If still no transfer possible, break to avoid infinite loop
                    if (!transferred) {
                        success = false;
                        break;
                    }
                }
            }
            
            if (op_count >= MAX_OPERATIONS) {
                success = false;
                break;
            }
        }
        
        if (!success) {
            cout << -1 << endl;
            continue;
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
            cout << -1 << endl;
        }
    }
    
    return 0;
}