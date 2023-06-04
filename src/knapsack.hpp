#ifndef __KNAPSACK_H__
#define __KNAPSACK_H__

#include <bits/stdc++.h>
#define ll long long

using namespace ::std;

struct knapsack {
    ll N, cap;
    vector<ll> weights;
    vector<ll> values;
    ll sol=0;
};

void test(knapsack sack, ll (*fn)(knapsack sack));

#endif
