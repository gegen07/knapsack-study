#include "knapsack.hpp"
#include "algorithms.hpp"
#include <algorithm>
#include <array>
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

ll _backtracking(ll v_max, ks::knapsack sack, int i, int j, ll cur_value, ll& best_val, struct stats& s) {
    if (j < 0 || i < 0) return cur_value;

    ll v = 0;

    if (cur_value+v_max <= best_val) {
        return cur_value;
    }

    v_max-=sack.values[i];
    
    s.op+=1;
    if (sack.weights[i] > j) {
        return _backtracking(v_max, sack, i-1, j, cur_value, best_val, s);
    }

    s.op+=2;
    v = std::max(_backtracking(v_max, sack, i-1, j, cur_value, best_val, s), _backtracking(v_max, sack, i-1, j-sack.weights[i], cur_value+sack.values[i], best_val, s)); 

    best_val = std::max(v, best_val);

    // std::cout << s.op << std::endl;
    return v;
}

ll _solve_util(ks::knapsack& sack, struct stats& s) {
    ll v = 0;

    ll v_max = 0;
    for (ll v: sack.values) { s.op++; v_max += v; }

    sack.sol = 0;

    return _backtracking(v_max, sack, sack.N-1, sack.cap, 0, sack.sol, s);
}

ll back::solve(ks::knapsack sack, struct stats& s) {
    return _solve_util(sack, s);
}

/**
 * @brief 
 * Brute Force Method
 * @param sack 
 * @param i 
 * @param j 
 * @return Brute 
 */

ll _brute_force(ks::knapsack sack, int i, int j, struct stats& s) {
    if (j < 0 || i < 0) return 0;
    
    s.op++; if (sack.weights[i-1] > j) {
        return _brute_force(sack, i-1, j, s);
    }

    s.op+=2;
    return std::max(_brute_force(sack, i-1, j, s), 
                    sack.values[i-1]+_brute_force(sack, i-1, j-sack.weights[i-1], s)); 
}

ll brute::solve(ks::knapsack sack, struct stats& s) {
    sack.sol = _brute_force(sack, sack.N, sack.cap, s);
    return sack.sol;
}

/**
 * @brief 
 * greedy method
 * @param sack 
 * @return ll 
 */

ll _greedy(ks::knapsack sack, struct stats& s) {
    std::vector<std::array<double, 3>> profit;
    for (int i=0; i<sack.N; i++) 
        profit.push_back({(double) sack.values[i]/sack.weights[i], (double) sack.values[i], (double) sack.weights[i]});
        
    unsigned int comparisons=0U;
    sort(profit.begin(), profit.end(), [&comparisons](std::array<double, 3>& a, std::array<double, 3>& b){
        comparisons++;
        return a[0] > b[0];
    });

    s.op += comparisons;

    int c = sack.cap;
    ll optimal_value = 0;
    for (int i=0; i<profit.size(); i++) {
        if (c-profit[i][2] >= 0) {
            optimal_value += profit[i][1]; 
            c-=profit[i][2];
            s.op++;
        }
    }

    return optimal_value;
}

ll gdy::solve(ks::knapsack sack, struct stats& s) {
    return _greedy(sack, s);
}

/**
 * @brief 
 * exhaustive search method
 * @param sack 
 * @return ll 
 */

ll _search(ks::knapsack sack, struct stats& s) {
    std::vector<std::vector<int>> subsets;
    for (ll i=0; i < (1<<sack.N); i++) {
        std::vector<int> a;
        for (ll j=0; j < sack.N; j++) {
            if (i & (1 << j)) {
                a.push_back(j);
            }
            s.op++;
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

        if (curr_weight <= sack.cap and curr_value > optimal_value) {
            optimal_value = curr_value;
            s.op++;
        }
    }

    return optimal_value;
}

ll esearch::solve(ks::knapsack sack, struct stats& s) {
    return _search(sack, s);
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

ll top_down_util(ks::knapsack sack, int i, int j, ll*** dp, struct stats& s) {

    if (j < 0 || i < 0) return 0;

    if ((*dp)[i][j]) return (*dp)[i][j];
    
    ++s.op;
    if (sack.weights[i] > j) {
        return (*dp)[i][j] = top_down_util(sack, i-1, j, dp, s);
    }

    s.op+=2;
    return (*dp)[i][j] = std::max(top_down_util(sack, i-1, j, dp, s), sack.values[i]+top_down_util(sack, i-1, j-sack.weights[i], dp, s)); 
}

ll dptop::top_down(ks::knapsack sack, ll*** dp, struct stats& s) {
    return top_down_util(sack, sack.N-1, sack.cap, dp, s);
}

ll dptop::solve(ks::knapsack sack, struct stats& s) {
    ll** dp;

    dp = (ll**) malloc(110*sizeof(ll*));

    for (int i = 0; i < 110; i++) 
        dp[i] = (ll*) malloc(101010*sizeof(ll));

    for (int i=0; i<110; i++)
        for (int j=0; j<101010; j++)
            dp[i][j] = 0;

    return top_down(sack, &dp, s);

}

ll dpbot::bottom_up(ks::knapsack sack, ll ***dp, struct stats& s) {
    for (ll i=1; i<=sack.N; i++) {
        for (ll j=0; j<=sack.cap; j++) {
            if (j-sack.weights[i-1] >= 0) {
                s.op+=2;
                (*dp)[i][j] = std::max((*dp)[i-1][j], sack.values[i-1]+(*dp)[i-1][j-sack.weights[i-1]]);
            } else {
                s.op+=1;
                (*dp)[i][j] = (*dp)[i-1][j];
            }
        }
    }

    return (*dp)[sack.N][sack.cap];
}

ll dpbot::solve(ks::knapsack sack, struct stats& s) {
    ll** dp;

    dp = (ll**) malloc(110*sizeof(ll*));

    for (int i = 0; i < 110; i++) 
        dp[i] = (ll*) malloc(101010*sizeof(ll));

    for (int i=0; i<110; i++)
        for (int j=0; j<101010; j++)
            dp[i][j] = 0;

    return bottom_up(sack, &dp, s);

}