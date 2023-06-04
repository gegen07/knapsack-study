#include "knapsack.hpp"
#include "backtracking.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#define ll long long

ll _backtracking(int i, int curr_cap, ll curr_value, ll& best_val, ks::knapsack sack) {
    if (i >= sack.N) {
        return curr_value;
    }

    if (curr_cap-sack.weights[i] >= 0) {
        ll v = _backtracking(i+1, curr_cap-sack.weights[i], sack.values[i]+curr_value, best_val, sack);
        best_val = std::max(v, best_val);
    }

    ll v2 = _backtracking(i+1, curr_cap, curr_value, best_val, sack);
    
    return std::max(v2, best_val);
}

ll back::backtracking(ks::knapsack& sack) {
    ll v = 0;
    return _backtracking(0, sack.cap, v, sack.sol, sack);
}