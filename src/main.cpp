#include <bits/stdc++.h>
#include <vector>
#include "./lib/knapsack.hpp"
#include "./lib/algorithms.hpp"
#define ll long long
using namespace ::std;

ll test(ks::knapsack sack, ll (*fn)(ks::knapsack sack)) {
    return fn(sack);
}

int main() {
    ks::knapsack sack;
    cin >> sack.N >> sack.cap;

    for (int i =0; i<sack.N; i++) {
        int w, v;

        cin >> w >> v;

        sack.weights.push_back(w);
        sack.values.push_back(v);
    }

    ll (*fn[6])(ks::knapsack sack) = {
        dpbot::solve, dptop::solve, back::solve,
        gdy::solve, brute::solve, esearch::solve
    };

    for (ll(*f)(ks::knapsack sack): fn) {
        cout << test(sack, dpbot::solve) << endl;
    }

    return 0;
}