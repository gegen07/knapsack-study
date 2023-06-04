#include "knapsack.hpp"
#include "exhaustive_search.hpp"
#include <bits/stdc++.h>
#include <vector> 
#include <set> 
#include <algorithm>
#define ll long long

ll _search(ks::knapsack sack) {
    std::vector<std::vector<int>> subsets;
    for (ll i=0; i < (1<<sack.N); i++) {
        std::vector<int> a;
        for (ll j=0; j < sack.N; j++) {
            if (i & (1 << j)) {
                a.push_back(j);
            }
        }
        subsets.push_back(a);
    }

    ll optimal_value = 0;
    for (int i=0; i<subsets.size(); i++) {
        ll curr_value=0;
        ll curr_weight=0;
        for (int j=0; j<subsets[i].size(); j++) {
            curr_value += sack.values[subsets[i][j]];
            curr_weight+= sack.weights[subsets[i][j]];
        }

        if (curr_weight <= sack.cap and curr_value > optimal_value)
            optimal_value = curr_value;
    }

    return optimal_value;
}

ll esearch::solve(ks::knapsack sack) {
    return _search(sack);
}