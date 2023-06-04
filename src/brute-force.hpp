#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
#define fast_input ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define ll long long
#define vi vector<int>
#define pii pair<int, int>
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
using namespace ::std;

//recurrence relation
// if w <= c: { max(f[i-i][j], v[i] + f[i-1][j-w[i]]) }
// else f[i-1][j]

struct knapsack {
    ll N, cap;
    vector<ll> weights;
    vector<ll> values;
    ll sol=0;
};


ll _brute_force(knapsack sack, int i, int j) {
    int v = 0;
    if (i>0) {
        if (j-sack.weights[i-1] >= 0) {
            v = max(_brute_force(sack, i-1, j), sack.values[i-1]+_brute_force(sack, i-1, j-sack.weights[i-1])); 
        } else {
            v = _brute_force(sack, i-1, j);
        }
    }
        
    return v;
}

ll brute_force(knapsack sack) {
    sack.sol = _brute_force(sack, sack.N, sack.cap);
    return sack.sol;
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

    cout << brute_force(sack) << endl;

    return 0;
}