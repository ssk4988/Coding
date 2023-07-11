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
    int n, t; cin >> n >> t;
    vi par(n, -1);
    vl g(n);
    vvi child(n);
    rep(i, 1, n){
        cin >> par[i] >> g[i];
        par[i]--;
        child[par[i]].pb(i);
    }
    vl sumg(g), duration(n), gval(n);
    auto dfs = [&](int cur, auto &&dfs)->void{
        for(int nex : child[cur]) {
            dfs(nex, dfs);
            gval[nex] += sumg[nex]; // extra time for going down from parent
            duration[nex] += 2; // extra time to go down and back up
            duration[cur] += duration[nex];
            sumg[cur] += sumg[nex];
        }
        sort(all(child[cur]), [&](int a, int b)->bool{return sumg[a] * duration[b] > sumg[b] * duration[a];});
        ll t = 0;
        for(int nex : child[cur]){
            gval[cur] += t * sumg[nex] + gval[nex];
            t += duration[nex];
        }
    };
    dfs(0, dfs);
    if(t == 0){
        cout << duration[0] << " " << gval[0] << nL;
    }
    else{
        pl best = {LLONG_MAX, LLONG_MAX};
        auto dfs1 = [&](int cur, pl p, auto &&dfs1)->void{
            ll d = 0;
            for(int nex : child[cur]){
                d += duration[nex];
            }
            vl pref(sz(child[cur])), suff(sz(child[cur])), cont(sz(child[cur]));
            ll t = 0;
            rep(i, 0, sz(child[cur])){
                pref[i] = cont[i] = t * sumg[child[cur][i]] + gval[child[cur][i]];
                t += duration[child[cur][i]];
                if(i) pref[i] += pref[i - 1];
            }
            for(int i = sz(child[cur]) - 1; i >= 0; i--){
                suff[i] = sumg[child[cur][i]];
                if(i + 1 < sz(child[cur])) suff[i] += suff[i + 1];
            }
            t = 0;
            rep(i, 0, sz(child[cur])){
                int nex = child[cur][i];
                pl p1 = {p.f + d - duration[nex] + 1, p.s};
                // p1.s += i ? pref[i] : 0;
                p1.s += pref.back();
                p1.s -= cont[i];
                if(i + 1 < sz(child[cur])){
                    p1.s -= suff[i + 1] * duration[nex];
                }
                p1.s += (d - duration[nex] + 1) * sumg[nex];
                dfs1(nex, p1, dfs1);
                t += duration[nex];
            }
            if(sz(child[cur]) == 0){
                best = min(best, p);
            }
        };
        dfs1(0, {0, 0}, dfs1);
        cout << best.f << " " << best.s << nL;
    }

    
    return 0;
}