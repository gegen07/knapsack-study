#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#include "./lib/knapsack.hpp"
#include "./lib/algorithms.hpp"
#define ll long long
using namespace ::std;

ll test(ks::knapsack sack, ll (*fn)(ks::knapsack sack, struct stats& op), struct stats& op) {
    return fn(sack, op);
}

ks::knapsack read_input(std::string filename) {
    std::ifstream file;
    
    file.open(filename);
    
    ks::knapsack sack;

    ll x, y;
    int num_lines=0;

    if (file.is_open()) {
        std::string line;       


        while(file>>x>>y) {
            if(num_lines==0) { sack.N = x; sack.cap = y; }
            else {
                sack.weights.push_back(x);
                sack.values.push_back(y);
            }
            num_lines++;
        }
        file.close();
    }

    return sack;
}

int main() {
    ll (*fn[6])(ks::knapsack sack, struct stats& op) = {
        dpbot::solve, dptop::solve, back::solve,
        gdy::solve, brute::solve, esearch::solve
    };

    string methods[6] = {"bottom-up", "top-down", "backtracking", "greedy", "brute-force", "exhaustive-search"};

    std::ofstream out("../analysis/data.csv");

    out << "N,cap,sol_val,op,method" << std::endl;
    
    for (int i=8; i<=32; i+=2) {
        for (int j=8; j<=32; j+=2) {
            ks::knapsack sack;

            string filename = "../data/knapsack-" + to_string(i) + "/" + to_string(j) + ".txt";
            cout << filename << endl;
            sack = read_input(filename);

            for (int k=0; k<6; k++) {
                struct stats s;
                s.op=0;
                ll opt_value = test(sack, fn[k], s);
                
                out << sack.N << "," << sack.cap << "," << opt_value << "," << s.op << "," << methods[k] << std::endl;
                cout << "Solution_value: " << opt_value << " op: " << s.op << endl;
            }
        }
    }

    return 0;
}