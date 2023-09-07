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
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        vvi cycles;
        if(n % 2 == 1){
            rep(i, 0, n) a.pb(a[i]);
            n *= 2;
        }
        vl duration;
        vi visited(n);
        ll d = 1;
        rep(i, 0, n){
            if(visited[i] || a[i] == 0) continue;
            int c = sz(cycles);
            cycles.pb({});
            duration.pb(0);
            duration[c] += a[i];
            cycles[c].pb(i);
            ll cur = i + a[i];
            while(cur % n != i){
                assert(!visited[cur % n]);
                visited[cur % n] = true;
                duration[c] += a[cur % n];
                cycles[c].pb(cur);
                cur = cur + a[cur % n];
            }
            cycles[c].pb(cur);
            visited[cur % n] = true;
            d = duration[c] / __gcd(d, duration[c]) * d;
        }
        vl ans(4);
        rep(i, 0, sz(cycles)){
            ll numobjects = duration[i] / n;
            int seen = 0;
            for(int j : cycles[i]) seen |= 1 << (j % 2);
            if(n % 2 == 1 && numobjects % 2 == 0 && seen != 3){
                ans[1] += numobjects / 2;
                ans[2] += numobjects / 2;
            }
            else ans[seen] += numobjects;
        }
        rep(i, 1, 4) cout << ans[i] << " ";
        cout << nL;
    }
    
    return 0;
}