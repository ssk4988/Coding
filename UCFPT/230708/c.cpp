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

int K = 40000; // in theory should be 1000/1001?

pi divide(pi interval, int k){
    return {(interval.f + k - 1) / k, interval.s / k};
}

void solve(){
    int s1, s2, w1, w2; cin >> s1 >> s2 >> w1 >> w2;
    int ans = min(s2 - s1 + 1, w2 - w1 + 1);
    rep(i, 1, K){
        pi s3 = divide({s1, s2}, i), w3 = divide({w1, w2}, i);
        if(s3.f <= s3.s && w3.f <= w3.s) ans = max(ans, i);
    }
    vector<array<int, 3>> sevents, wevents; // {val, add/rem, dim}
    for(int i = K; i >= 1; i--){
        pi s3 = divide({s1, s2}, i), w3 = divide({w1, w2}, i);
        if(s3.f <= s3.s){
            sevents.pb({s3.f, 0, 1});
            sevents.pb({s3.s, 1, 1});
        }
        if(w3.f <= w3.s){
            wevents.pb({w3.f, 0, 0});
            wevents.pb({w3.s, 1, 0});
        }
    }
    int sidx = 0, widx = 0;
    vi open(2);
    while(sidx < sz(sevents) || widx < sz(wevents)){
        bool canS = sidx < sz(sevents), canW = widx < sz(wevents);
        if(canS && canW){
            auto [x, t, d] = (sevents[sidx] < wevents[widx] ? sevents[sidx++] : wevents[widx++]);
            if(open[1-d]){
                ans = max(ans, x);
            }
            open[d] += (t == 0 ? 1 : -1);
            
        }
        else if(canS){
            auto [x, t, d] = sevents[sidx++];
            if(open[1-d]){
                ans = max(ans, x);
            }
            open[d] += (t == 0 ? 1 : -1);
        }
        else{
            auto [x, t, d] = wevents[widx++];
            if(open[1-d]){
                ans = max(ans, x);
            }
            open[d] += (t == 0 ? 1 : -1);
        }
    }
    // for(auto [x, t, d] : events){
    //     if(open[1-d]){
    //         ans = max(ans, x);
    //     }
    //     open[d] += (t == 0 ? 1 : -1);
    // }
    cout << ans << "\n";
}


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    rep(i, 0, n) solve();
}
