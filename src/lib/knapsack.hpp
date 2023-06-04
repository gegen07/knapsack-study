#ifndef __KNAPSACK_H__
#define __KNAPSACK_H__

#include <bits/stdc++.h>
#define ll long long

namespace ks {
    struct knapsack {
        ll N, cap;
        std::vector<ll> weights;
        std::vector<ll> values;
        ll sol=0;
    };
}

#endif
