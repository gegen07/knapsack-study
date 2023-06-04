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

namespace gdy {
    ll solve(ks::knapsack sack);
}

namespace esearch {
    ll solve(ks::knapsack sack);
}

namespace dptop {
    ll top_down(ks::knapsack sack, ll ***dp);
    ll solve(ks::knapsack sack);
}

namespace dpbot {
    ll bottom_up(ks::knapsack sack, ll ***dp);
    ll solve(ks::knapsack sack);
}

namespace brute {
    ll solve(ks::knapsack sack);
}

namespace back {
    ll solve(ks::knapsack sack);
}


#endif
