#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include "knapsack.hpp"
#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <tuple>
#include <vector> 
#include <set> 
#include <algorithm>

#define ll long long

struct stats {
    ll op;
};

namespace gdy {
    ll solve(ks::knapsack sack, struct stats& op);
}

namespace esearch {
    ll solve(ks::knapsack sack, struct stats& op);
}

namespace dptop {
    ll top_down(ks::knapsack sack, ll ***dp, struct stats& op);
    ll solve(ks::knapsack sack, struct stats& op);
}

namespace dpbot {
    ll bottom_up(ks::knapsack sack, ll ***dp, struct stats& op);
    ll solve(ks::knapsack sack, struct stats& op);
}

namespace brute {
    ll solve(ks::knapsack sack, struct stats& op);
}

namespace back {
    ll solve(ks::knapsack sack, struct stats& op);
}


#endif
