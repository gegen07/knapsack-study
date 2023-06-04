#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector> 
#include <set> 
#include <algorithm>

#define fast_input ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define ll long long
#define vi vector<int>
#define pii pair<int, int>
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
using namespace ::std;

struct knapsack {
    ll N, cap;
    vector<ll> weights;
    vector<ll> values;
    ll sol=0;
};

ll _greedy(knapsack sack) {
    vector<array<double, 3>> profit;
    for (int i=0; i<sack.N; i++) 
        profit.push_back({(double) sack.values[i]/sack.weights[i], (double) sack.values[i], (double) sack.weights[i]});

    sort(profit.begin(), profit.end(), greater<array<double, 3>>());

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

ll greedy(knapsack sack) {
    return _greedy(sack);
}

int main() {
    fast_input;
    knapsack sack;
    cin >> sack.N >> sack.cap;

    for (int i =0; i<sack.N; i++) {
        int w, v;

        cin >> w >> v;

        sack.weights.push_back(w);
        sack.values.push_back(v);
    
    }


    cout << greedy(sack) << endl;

    return 0;
}