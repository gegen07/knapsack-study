#include "knapsack.hpp"
#include "algorithms.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#define ll long long

/**
 * @brief 
 * backtracking method
 * @param i 
 * @param curr_cap 
 * @param curr_value 
 * @param best_val 
 * @param sack 
 * @return ll 
 */

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

ll _solve_util(ks::knapsack& sack) {
    ll v = 0;
    return _backtracking(0, sack.cap, v, sack.sol, sack);
}

ll back::solve(ks::knapsack sack) {
    return _solve_util(sack);
}

/**
 * @brief 
 * Brute Force Method
 * @param sack 
 * @param i 
 * @param j 
 * @return Brute 
 */

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

ll brute::solve(ks::knapsack sack) {
    sack.sol = _brute_force(sack, sack.N, sack.cap);
    return sack.sol;
}

/**
 * @brief 
 * greedy method
 * @param sack 
 * @return ll 
 */

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

ll gdy::solve(ks::knapsack sack) {
    return _greedy(sack);
}

/**
 * @brief 
 * exhaustive search method
 * @param sack 
 * @return ll 
 */

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

/**
 * @brief 
 * dynamic programming methods
 * @param sack 
 * @param i 
 * @param j 
 * @param dp 
 * @return ll 
 */

ll top_down_util(ks::knapsack sack, int i, int j, ll*** dp) {
    if ((*dp)[i][j]) {
        return (*dp)[i][j];
    }

    if (i>0) {
        if (j-sack.weights[i-1] >= 0) {
            (*dp)[i][j] = std::max(top_down_util(sack, i-1, j, dp), sack.values[i-1]+top_down_util(sack, i-1, j-sack.weights[i-1], dp)); 
        } else {
            (*dp)[i][j] = top_down_util(sack, i-1, j, dp);
        }
    }
        
    return (*dp)[i][j];
}

ll dptop::top_down(ks::knapsack sack, ll*** dp) {
    return top_down_util(sack, sack.N, sack.cap, dp);
}

ll dptop::solve(ks::knapsack sack) {
    ll** dp;

    dp = (ll**) malloc(110*sizeof(ll*));

    for (int i = 0; i < 110; i++) 
        dp[i] = (ll*) malloc(101010*sizeof(ll));

    for (int i=0; i<110; i++)
        for (int j=0; j<101010; j++)
            dp[i][j] = 0;

    return top_down(sack, &dp);

}

ll dpbot::bottom_up(ks::knapsack sack, ll ***dp) {
    for (ll i=1; i<=sack.N; i++) {
        for (ll j=0; j<=sack.cap; j++) {
            if (j-sack.weights[i-1] >= 0) {
                (*dp)[i][j] = std::max((*dp)[i-1][j], sack.values[i-1]+(*dp)[i-1][j-sack.weights[i-1]]);
            } else {
                (*dp)[i][j] = (*dp)[i-1][j];
            }
        }
    }

    return (*dp)[sack.N][sack.cap];
}

ll dpbot::solve(ks::knapsack sack) {
    ll** dp;

    dp = (ll**) malloc(110*sizeof(ll*));

    for (int i = 0; i < 110; i++) 
        dp[i] = (ll*) malloc(101010*sizeof(ll));

    for (int i=0; i<110; i++)
        for (int j=0; j<101010; j++)
            dp[i][j] = 0;

    return bottom_up(sack, &dp);

}