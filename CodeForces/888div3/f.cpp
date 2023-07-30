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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        pair<ll, pi> ans = {0, {-1, -1}};
        // try n=2, k=1
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        auto solve = [&](vi &elems, ll score, int curk, auto &&solve)->void{
            if(sz(elems) < 2) return;
            pair<ll, pi> curans = {score, {elems[0], elems.back()}};
            ans = max(ans, curans);
            if(curk < 0) return;
            vvi par(2);
            for(int i : elems){
                par[(a[i] >> curk) & 1].pb(i);
            }
            bool split = false;
            if(sz(par[0]) >= 2){
                solve(par[0], score + (1 << curk), curk - 1, solve);
                split = true;
            }
            if(sz(par[1]) >= 2){
                solve(par[1], score + (1 << curk), curk - 1, solve);
                split = true;
            }
            if(!split && sz(par[0]) >= 1 && sz(par[1]) >= 1){
                solve(elems, score, curk - 1, solve);
            }
        };
        vi curelems;
        rep(i, 0, n) curelems.pb(i);
        solve(curelems, 0, k - 1, solve);
        int res = 0;
        rep(i, 0, k){
            if(((1 << i) & a[ans.s.f]) == ((1 << i) & a[ans.s.s])){
                if(((1 << i) & a[ans.s.f]) == 0){
                    res |= 1 << i;
                }
            }
        }
        assert(((a[ans.s.f] ^ res) & (a[ans.s.s] ^ res)) == ans.f);
        cout << (ans.s.f + 1) << " " << (ans.s.s + 1) << " " << res <<  nL;
    }
    
    return 0;
}