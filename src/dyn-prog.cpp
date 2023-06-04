#include "knapsack.hpp"
#include "dyn-prog.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#define ll long long

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

ll bottom_up(ks::knapsack sack, ll ***dp) {
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