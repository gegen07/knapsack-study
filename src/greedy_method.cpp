#include "knapsack.hpp"
#include "greedy_method.hpp"
#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <tuple>
#include <vector> 
#include <set> 
#include <algorithm>

#define ll long long

ll _greedy(ks::knapsack sack) {
    std::vector<std::array<double, 3>> profit;
    for (int i=0; i<sack.N; i++) 
        profit.push_back({(double) sack.values[i]/sack.weights[i], (double) sack.values[i], (double) sack.weights[i]});

    sort(profit.begin(), profit.end(), std::greater<std::array<double, 3>>());

    int c = sack.cap;
    ll optimal_value = 0;
    for (int i=0; i<profit.size(); i++) {
        if (c-profit[i][2] >= 0) {
            optimal_value += profit[i][1]; 
            c-=profit[i][2];
        }
    }

    return optimal_value;
}

ll gdy::greedy(ks::knapsack sack) {
    return _greedy(sack);
}