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
    int n; cin >> n;
    vi p(n), rp(n);
    rep(i, 0, n){
        cin >> p[i];
        p[i]--;
        rp[p[i]] = i;
    }
    vector<vpi> ans;
    ans.pb({});
    vi used(n);
    auto sw = [&](int v1, int v2)->void{
        int i1 = rp[v1], i2 = rp[v2];
        used[i1] = used[i2] = true;
        swap(p[i1], p[i2]);
        swap(rp[v1], rp[v2]);
        ans.back().pb({i1, i2});
    };
    rep(i, 0, n){
        if(used[i] || used[p[i]] || p[i] == i) continue;
        if(p[p[i]] == i){
            sw(p[i], p[p[i]]);
        }
        else{
            int cur = p[i], nex = p[cur];
            sw(cur, nex);
            while(p[nex] != rp[nex]){
                cur = rp[nex], nex = p[nex];
                sw(cur, nex);
            }
            cur = p[i];
        }
    }
    if(sz(ans[0]) == 0) ans.pop_back();
    bool solved = true;
    rep(i, 0, n){
        if(p[i] != i) solved = false;
    }
    if(!solved){
        ans.pb({});
        rep(i, 0, n){
            if(p[i] != i) sw(i, p[i]);
        }
    }
    cout << sz(ans) << nL;
    for(auto v : ans){
        cout << sz(v) << nL;
        for(auto [a, b] : v){
            cout << (a + 1) << " " << (b + 1) << nL;
        }
    }
    return 0;
}
