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
        ll ni, targsum;
        input >> ni >> targsum;

        string expfirst, prodfirst;
        expected >> expfirst;
        produced >> prodfirst;

        // cout << "case " << i << ": ni " << ni << ", targsum " << targsum << " p=" << prodfirst << ", e= " << expfirst << endl;

        if(expfirst == "IMPOSSIBLE"){
            if(prodfirst != "IMPOSSIBLE"){
                failed++;
                // cout << "failed1 case " << i << endl;
            }
            continue;
        }
        if(prodfirst == "IMPOSSIBLE"){
            failed++;
            // cout << "failed2 case " << i << endl;

            continue;
        }
        ll prodsum = stoll(prodfirst);
        ll expsum = stoll(expfirst);
        for(int j = 1; j < ni; j++){
            ll x;
            produced >> x;
            prodsum += x;
            expected >> x;
            expsum += x;
        }
        // cout << "input says " << targsum << ", produced " << prodsum << ", expected " << expsum << endl;
        if(prodsum != targsum){
            // cout << "failed3 case " << i << endl;
            failed++;
        }
            
    }
    if(failed != 0) cout << "FAILED " << failed << " CASES\n";

    return 0;
}
