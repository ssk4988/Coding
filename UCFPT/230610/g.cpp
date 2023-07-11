#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using vvl = vector<vl>;
using ppi = pair<int, pi>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    vi par(n);
    vvi child(n);
    vi dep(n);
    vvpi deps(n);
    vi longest(n);
    // n = 1??????
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    if(n == 1){
        cout << 0 << "\n";
        cout << "1 1\n1 1\n";
        return 0;
    }
    auto dfs = [&](int cur, int p, auto &&dfs)->void{
        par[cur] = p;
        for(int i : adj[cur]){
            if(i == p) continue;
            dfs(i, cur, dfs);
            child[cur].pb(i);
            dep[cur] = max(dep[cur], 1 + dep[i]);
            longest[cur] = max(longest[cur], longest[i]);
            deps[cur].pb({dep[i] + 1, i});
        }
        sort(all(deps[cur]));
        reverse(all(deps[cur]));
        int lg = 0;
        rep(i, 0, min(2, sz(deps[cur]))){
            lg += deps[cur][i].f;
        }
        longest[cur] = max(longest[cur], lg);
    };
    dfs(0, -1, dfs);
    ppi curdiam = {INT_MAX, {-1, -1}};
    auto dfs2 = [&](int cur, auto &&dfs2)->void{
        if(par[cur] != -1){
            bool added = false;
            for(auto [a1, a2] : deps[par[cur]]){
                if(a2 == cur) continue;
                deps[cur].pb({a1 + 1, par[cur]});
                added = true;
                break;
            }
            if(!added) deps[cur].pb({1, par[cur]});
        }
        sort(all(deps[cur]));
        reverse(all(deps[cur]));
        for(int i : child[cur]){
            int d1 = (longest[i] + 1) / 2;
            vpi ds;
            for(auto &a : deps[cur]){
                if(a.s == i) continue;
                ds.pb(a);
                if(sz(ds) >= 2) break;
            }
            sort(all(ds));
            reverse(all(ds));
            int d2 = 0;
            rep(i, 0, sz(ds)){
                d2 += ds[i].f;
            }
            ppi diam = {max((d2 + 1) / 2 + d1 + 1, max(d2, longest[i])), {cur, i}};
            curdiam = min(curdiam, diam);
        }
        for(int i : child[cur]){
            dfs2(i, dfs2);
        }
    };
    dfs2(0, dfs2);
    vi a;
    for(int i : adj[curdiam.s.f]){
        if(i != curdiam.s.s) a.pb(i);
    }
    adj[curdiam.s.f] = a;
    a.clear();
    for(int i : adj[curdiam.s.s]){
        if(i != curdiam.s.f) a.pb(i);
    }
    adj[curdiam.s.s] = a;
    vi dist(n);
    auto farthest = [&](int cur, int p, int d, auto &&farthest)->pi{
        pi f = {0, cur};
        for(int i : adj[cur]){
            if(i == p) continue;
            pi res = farthest(i, cur, d + 1, farthest);
            if(res.f + 1 > f.f){
                f.f = res.f + 1;
                f.s = res.s;
            }
        }
        return f;
    };
    pi res = farthest(curdiam.s.f, -1, 0, farthest);
    int d1 = res.s;
    res = farthest(d1, -1, 0, farthest);
    int d2 = res.s;
    vi diam;
    auto findit = [&](int cur, int p, auto &&findit)->bool{
        if(cur == d2){
            diam.pb(cur);
            return true;
        }
        for(int i : adj[cur]){
            if(i == p) continue;
            if(findit(i, cur, findit)){
                diam.pb(cur);
                return true;
            }
        }
        return false;
    };
    findit(d1, -1, findit);
    int point1 = diam[(sz(diam)-1)/2];
    res = farthest(curdiam.s.s, -1, 0, farthest);
    d1 = res.s;
    res = farthest(d1, -1, 0, farthest);
    d2 = res.s;
    diam.clear();
    findit(d1, -1, findit);
    int point2 = diam[(sz(diam)-1)/2];
    cout << curdiam.f << "\n";
    cout << (curdiam.s.f + 1) << " " << (curdiam.s.s + 1) << "\n";
    cout << (point1 + 1) << " " << (point2 + 1) << "\n";

    return 0;
}