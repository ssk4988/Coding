#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a = 1, b = 1; // n = 2
    int ans = 5;
    priority_queue<int, vi, greater<int>> pq;
    pq.push(1);
    pq.push(4);
    map<int, int> ff;
    rep(n, 3, 101){
        int k = pq.top();
        pq.pop();
        ans += k * 2 + 5 - k;
        pq.push(k + 1);
        pq.push(k + 4);
        ff[k]++;
        // cout << n << " " << ans << " " << k << nL;
    }
    for(auto [key, val] : ff){
        // cout << key << " " << val << nL;
    }
    vl cnt = {0, 0, 1, 1, 1, 2, 3};
    vl sum = {1, 5, 11, 18, 26, 44, 74};
    vl ns = {1, 2, 3, 4, 5, 7, 10};
    while(ns.back() < ll(1e9)){
        int idx = sz(cnt);
        cnt.pb(cnt[idx - 1] + cnt[idx - 4]);
        ns.pb(ns.back() + cnt[idx]);
        sum.pb((idx - 1 + 5) * cnt[idx] + sum.back());
        // cout << cnt.back() << " " << sum.back() << " " << ns.back() << nL;
    }
    // cout << sz(cnt) << nL;
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        int idx = 0;
        rep(i, 0, sz(cnt)){
            if(ns[i] >= n){
                idx = i;
                break;
            }
        }
        ll ans = sum[idx] - (ns[idx] - n) * (idx - 1 + 5);
        cout << n << ": " << ans << nL;//" ns is " << ns[idx] << " " << sum[idx] << nL;
    }
    
    return 0;
}
