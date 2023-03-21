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
    int n;
    ll x;
    cin >> n >> x;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    unordered_map<ll, pi> prev;
    vi ans = {-1};
    rep(i, 0, n){
        rep(j, 0, i - 1){
            if(prev.find(a[i - 1] + a[j])== prev.end()){
                prev[a[i - 1] + a[j]] = {i - 1 + 1, j + 1};
            }
        }
        rep(j, i + 1, n){
            if(prev.find(x - a[i] - a[j]) != prev.end()){
                pi p = prev[x - a[i] - a[j]];
                ans = {p.f, p.s, i + 1, j + 1};
            }
        }
    }
    if(ans[0] == -1){
        cout << "IMPOSSIBLE\n";
    }
    else{
        rep(i, 0, 4){
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
