#ifndef __DYN_PROG_H__
#define __DYN_PROG_H__
#include "knapsack.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#define ll long long

namespace dptop {
    ll top_down(ks::knapsack sack, ll ***dp);
    ll solve(ks::knapsack sack);
}

namespace dpbot {
    ll bottom_up(ks::knapsack sack, ll ***dp);
    ll solve(ks::knapsack sack);
}


#endif