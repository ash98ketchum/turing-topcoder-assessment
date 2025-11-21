#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

int main() {
    srand(time(0));

    int t = rand() % 1000;
    // int t = 5;
    cout << t << endl;

    int remaining_sum_N = 5000;

    while(t--) {
        int max_possible_N_here = min(1000, remaining_sum_N - (3 * t));
        
        int N = 3 + rand() % (max_possible_N_here - 3 + 1);
        remaining_sum_N -= N;

        cout << N << endl;
        
        for(int i = 0; i < N; ++i) {
            long long val = 1 + ((long long)rand() * rand()) % 1000000000;
            cout << val << (i == N-1 ? "" : " ");
        }
        cout << endl;
    }
    return 0;
}