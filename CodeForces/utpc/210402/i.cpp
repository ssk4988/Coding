#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
const int N = 2e5 + 10;
int composite[N];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    composite[0] = composite[1] = true;
    rep(i, 2, N){
        if(composite[i]) continue;
        if(ll(i) * i < N){
            for(int j = i * i; j < N; j+= i) composite[j] = true;
        }
    }
    vvi cands;
    rep(i, 0, n){
        int p; cin >> p;
        int s = sz(cands);
        rep(j, 0, s){
            auto &v = cands[j];
            bool bad = false;
            for(int x : v){
                if(!composite[x + p]) bad = true;
            }
            if(!bad){
                vi v1(v);
                v1.push_back(p);
                cands.push_back(v1);
            }
        }
        cands.push_back(vi{p});
    }
    int best = 0;
    for(auto &v : cands){
        best = max(best, sz(v));
        // for(int i : v) cout << i << " ";
        // cout << "\n";
    }
    cout << best << "\n";
    return 0;
}