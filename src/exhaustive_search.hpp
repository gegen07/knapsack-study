#include <bits/stdc++.h>
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

ll _search(knapsack sack) {
    vector<vector<int>> subsets;
    for (ll i=0; i < (1<<sack.N); i++) {
        vector<int> a;
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

ll exhaustive_search(knapsack sack) {
    return _search(sack);
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


    cout << exhaustive_search(sack) << endl;

    return 0;
}