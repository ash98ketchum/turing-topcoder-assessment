#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: checker <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    ifstream out(argv[2]);

    if (!in.is_open()) {
        cerr << "Error: Could not open input file: " << argv[1] << endl;
        return 1;
    }
    if (!out.is_open()) {
        cerr << "Error: Could not open output file: " << argv[2] << endl;
        return 1;
    }

    int t;
    if (!(in >> t)) {
        cerr << "Error: Input file empty or invalid format." << endl;
        return 1;
    }

    int case_num = 1;
    int total_passed = 0;

    while(t--) {
        int n;
        in >> n;
        vector<ll> a(n);
        int initial_nonzero = 0;
        for (int i = 0; i < n; ++i) {
            in >> a[i];
            if (a[i] > 0) initial_nonzero++;
        }

        int k;
        if (!(out >> k)) {
            cerr << "Case " << case_num << ": FAIL (Output file ended unexpectedly)" << endl;
            return 1;
        }

        if (k == -1) {
            if (initial_nonzero < 2) {
                cout << "Case " << case_num << ": OK (Correctly identified impossible)" << endl;
                total_passed++;
            } else {
                cout << "Case " << case_num << ": WARNING (Participant output -1, but solution likely exists)" << endl;
            }
        } 
        else {
            bool move_valid = true;
            string error_msg = "";

            if (k > 20000) {
                move_valid = false;
                error_msg = "Too many moves (" + to_string(k) + " > 20000)";
            }

            for (int i = 0; i < k; ++i) {
                int target, source;
                out >> target >> source;
                
                target--; 
                source--;

                if (!move_valid) continue;

                if (target < 0 || target >= n || source < 0 || source >= n) {
                    move_valid = false;
                    error_msg = "Invalid Index [" + to_string(target+1) + ", " + to_string(source+1) + "]";
                }
                else if (target == source) {
                    move_valid = false;
                    error_msg = "Target same as Source (" + to_string(target+1) + ")";
                }
                else if (a[source] < a[target]) {
                    move_valid = false;
                    error_msg = "Invalid Move: Source (" + to_string(a[source]) + ") < Target (" + to_string(a[target]) + ")";
                }
                else {
                    a[source] -= a[target];
                    a[target] *= 2;
                }
            }

            if (!move_valid) {
                cout << "Case " << case_num << ": FAIL (" << error_msg << ")" << endl;
            } else {
                int final_nonzero = 0;
                for (ll x : a) {
                    if (x > 0) final_nonzero++;
                }

                if (final_nonzero == 2) {
                    cout << "Case " << case_num << ": OK (" << k << " moves)" << endl;
                    total_passed++;
                } else {
                    cout << "Case " << case_num << ": FAIL (Result has " << final_nonzero << " active cells, expected 2)" << endl;
                }
            }
        }
        case_num++;
    }

    return 0;
}