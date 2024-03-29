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
    vi par(n, -1), c(n);
    int root = -1;
    vvi child(n);
    rep(i, 0, n){
        cin >> par[i];
        par[i]--;
        if(par[i] == -1) root = i;
        else child[par[i]].pb(i);
        cin >> c[i];
    }
    vi subsz(n, 1);
    vi order;
    bool works = true;
    auto dfs = [&](int u, auto &&dfs) -> bool {
        for(int v : child[u]){
            if(dfs(v, dfs)) return true;;
            subsz[u] += subsz[v];
        }
        if(c[u] >= subsz[u]){
            works = false;
            return true;
        }
        order.insert(order.begin() + c[u], u);
        return false;
    };
    if(dfs(root, dfs)){
        cout << "NO\n";
    }
    else{
        vi label(n);
        rep(i, 0, n){
            label[order[i]] = i + 1;
        }
        cout << "YES\n";
        rep(i, 0, n){
            cout << label[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
