#include "knapsack.hpp"
#include "brute-force.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#define ll long long

ll _brute_force(ks::knapsack sack, int i, int j) {
    int v = 0;
    if (i>0) {
        if (j-sack.weights[i-1] >= 0) {
            v = std::max(_brute_force(sack, i-1, j), sack.values[i-1]+_brute_force(sack, i-1, j-sack.weights[i-1])); 
        } else {
            v = _brute_force(sack, i-1, j);
        }
    }
        
    return v;
}

ll brute::brute_force(ks::knapsack sack) {
    sack.sol = _brute_force(sack, sack.N, sack.cap);
    return sack.sol;
}