#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;
using vvi = vector<vi>;
#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi h(n), h1, h2;
    rep(i, 0, n) cin >> h[i];
    rep(i, 0, n / 2) h1.pb(h[i]);
    rep(i, n/2, n) h2.pb(h[i]);
    vector<bool> b(1 << n);
    vi sumh1(1 << sz(h1)), sumh2(1 << sz(h2));
    rep(i, 0, 1 << sz(h1)){
        rep(j, 0, sz(h1)){
            if(i & (1 << j)) sumh1[i] += h1[j];
        }
    }
    unordered_set<int> ks;
    unordered_map<int, vi> h1sub;
    // vvi h1sub(1 << sz(h1));
    rep(i, 0, 1 << sz(h1)){
        rep(j, 0, 1 << sz(h1)){
            if((~i & j) == 0){
                // b[i | j] = true;
                int dif = abs((sumh1[i] - sumh1[j]) - sumh1[j]);
                h1sub[dif].pb(i);
                ks.insert(dif);
            }
        }
    }
    rep(i, 0, 1 << sz(h2)){
        rep(j, 0, sz(h2)){
            if(i & (1 << j)) sumh2[i] += h2[j];
        }
    }
    unordered_map<int, vi> h2sub;
    rep(i, 0, 1 << sz(h2)){
        rep(j, 0, 1 << sz(h2)){
            if((~i & j) == 0){
                // b[i | j] = true;
                int dif = abs((sumh2[i] - sumh2[j]) - sumh2[j]);
                h2sub[dif].pb(i << sz(h1));
                ks.insert(dif);
            }
        }
    }
    for(int k : ks){
        for(int i : h1sub[k]){
            for(int j : h2sub[k]){
                b[i | j] = true;
                // cout << k << "\n";
            }
        }
    }
    int ans = 0;
    rep(i, 1, sz(b)){
        ans += b[i];
    }
    cout << ans << "\n";
}
