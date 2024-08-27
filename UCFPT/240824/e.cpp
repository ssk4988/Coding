#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

void solve() {
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<pair<ll, ll>> cur = {
        {18, 288},
        {27, 3699},
        {12, 48},
        {36, 48888},
        {15, 5055},
        {45, 5055555555},
        {54, 222888888},
        {21, 7077},
        {63, 111888},
        {24, 8088},
        {72, 8088888888},
        {81, 9099999999}
    };
    map<int, ll> ans;
    for(auto [key, val] : cur) {
        ans[key] = val;
    }
    rep(i, 1, 10) ans[i] = i;
    
    int t; cin >> t; while(t--)
    {
        ll n; cin >> n;
        int mask = 0;
        for(ll c = n; c; c /= 10) {
            mask |= 1 << (c % 10);
        }
        if(__builtin_popcount(mask) == 1){
            cout << n << "\n";
            continue;
        }
        if(!ans.count(n)){
            cout << -1 << "\n";
        } else cout << ans[n] << "\n";
    }

    return 0;
}
