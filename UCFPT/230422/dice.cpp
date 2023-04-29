#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ld = long double;

int main(){
    cin.tie(0)->sync_with_stdio();
    cin.exceptions(cin.failbit);
    int a1, b1, a2, b2; cin >> a1 >> b1 >> a2 >> b2;
    vector<ld> freq(300);
    ld EPS = 1e-9;
    for(int i = a1; i <= b1; i++){
        for(int j = a2; j <= b2; j++){
            freq[i + j] += 1 / (ld)((b1 - a1 + 1) * (b2 - a2 + 1));
        }
    }
    cin >> a1 >> b1 >> a2 >> b2;
    vector<ld> freq2(300);
    vector<ld> pf(300), pf2(300);
    for(int i = a1; i <= b1; i++){
        for(int j = a2; j <= b2; j++){
            freq2[i + j] += ld(1) / ((b1 - a1 + 1) * (b2 - a2 + 1));
        }
    }
    ld tieprob = 0;
    for(int i = 0; i < 300; i++){
        tieprob += freq[i] * freq2[i];
        pf[i] = freq[i];
        pf2[i] = freq2[i];
    }
    for(int i = 1; i < 300; i++){
        pf[i] += pf[i - 1];
        pf2[i] += pf2[i - 1];
    }
    ld gwin = 0;
    for(int i = 1; i < 300; i++){
        gwin += freq[i] * pf2[i - 1];
    }
    ld left = 1 - tieprob;
    ld ewin = left - gwin;
    if(fabs(ewin - gwin) < EPS){
        cout << "Tie\n";
    }
    else if(gwin > ewin){
        cout << "Gunnar\n";
    }
    else{
        cout << "Emma\n";
    }

    return 0;
}