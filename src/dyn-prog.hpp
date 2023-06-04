#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
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

ll bottom_up(knapsack sack, ll ***dp) {
    for (ll i=1; i<=sack.N; i++) {
        for (ll j=0; j<=sack.cap; j++) {
            if (j-sack.weights[i-1] >= 0) {
                (*dp)[i][j] = max((*dp)[i-1][j], sack.values[i-1]+(*dp)[i-1][j-sack.weights[i-1]]);
            } else {
                (*dp)[i][j] = (*dp)[i-1][j];
            }
        }
    }

    return (*dp)[sack.N][sack.cap];
}

ll top_down(knapsack sack, int i, int j, ll*** dp) {
    if ((*dp)[i][j]) {
        return (*dp)[i][j];
    }

    if (i>0) {
        if (j-sack.weights[i-1] >= 0) {
            (*dp)[i][j] = max(top_down(sack, i-1, j, dp), sack.values[i-1]+top_down(sack, i-1, j-sack.weights[i-1], dp)); 
        } else {
            (*dp)[i][j] = top_down(sack, i-1, j, dp);
        }
    }
        
    return (*dp)[i][j];
}

ll solve(knapsack sack) {
    ll** dp;

    dp = (ll**) malloc(110*sizeof(ll*));

    for (int i = 0; i < 110; i++) 
        dp[i] = (ll*) malloc(101010*sizeof(ll));

    for (int i=0; i<110; i++)
        for (int j=0; j<101010; j++)
            dp[i][j] = 0;

    return top_down(sack, sack.N, sack.cap, &dp);

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


    cout << solve(sack) << endl;

    return 0;
}