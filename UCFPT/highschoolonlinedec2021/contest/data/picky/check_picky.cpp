#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;

ld error = 0.0001;
int oo = -1^1<<31;

int eq(ld a, ld b){
    return abs(a-b) < error;
}

int leq(ld a, ld b){
    return a < b || eq(a, b);
}

// ./a.out input.in produced.out expected.out
int main(int argc, char *argv[]){
    cin.tie(0)->sync_with_stdio(0);
    
    ifstream input(argv[1]), produced(argv[2]), expected(argv[3]);
    int numcases;
    input >> numcases;
    int failed = 0;
    for(int i = 0; i < numcases; i++){
        string expstat, prodstat;
        expected >> expstat;
        produced >> prodstat;


        ld exp = -1, prod = -1;
        if(expstat == "Yes")
            expected >> exp;
        if(prodstat == "Yes")
            produced >> prod;

        if(expstat != prodstat){
            failed++;
            continue;
        }

        if(eq(exp, prod) || leq((prod-exp)/exp, error));
        else{
            // cout << "Failed case " << i << endl;
            failed++;
        }
    }
    if(failed != 0) cout << "FAILED " << failed << " CASES\n";

    return 0;
}
