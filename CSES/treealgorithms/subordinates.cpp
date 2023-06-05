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
    vi par(n);
    vvi child(n);
    rep(i, 1, n){
        cin >> par[i];par[i]--;
        child[par[i]].pb(i);
    }
    vi subsz(n, 1);
    auto dfs = [&](int cur, auto &&dfs)->void{
        for(int i : child[cur]){
            dfs(i, dfs);
            subsz[cur] += subsz[i];
        }
    };
    dfs(0, dfs);
    rep(i, 0, n){
        cout << (subsz[i] - 1) << " ";
    }
    cout << nL;
    
    return 0;
}
