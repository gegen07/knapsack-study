#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#define fast_input ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define ll long long
#define vi vector<int>
#define pii pair<int, int>
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
using namespace ::std;

struct knapsack {
    ll N, cap;
    vector<ll> weights;
    vector<ll> values;
    ll sol=0;
};

ll _backtracking(int i, int curr_cap, ll curr_value, ll& best_val, knapsack sack) {
    if (i >= sack.N) {
        return curr_value;
    }

    if (curr_cap-sack.weights[i] >= 0) {
        ll v = _backtracking(i+1, curr_cap-sack.weights[i], sack.values[i]+curr_value, best_val, sack);
        best_val = max(v, best_val);
    }

    ll v2 = _backtracking(i+1, curr_cap, curr_value, best_val, sack);
    
    return max(v2, best_val);
}

ll backtracking(knapsack& sack) {
    ll v = 0;
    return _backtracking(0, sack.cap, v, sack.sol, sack);
}

int main() {
    fast_input;
    
    knapsack sack;

    cin >> sack.N >> sack.cap;

    for (int i =0; i<sack.N; i++) {
        int w, v;

        cin >> w >> v;

        sack.weights.push_back(w);
        sack.values.push_back(v);
    
    }

    cout << backtracking(sack) << endl;

    return 0;
}