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
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m, 1));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, sz(str)) if(str[j] == '.') grid[i][j] = 0;
    }
    int ans = 0;
    vi occ(n, m);
    for(int l = m - 1; l >= 0; l--){
        rep(i, 0, n) if(grid[i][l]) occ[i] = l;
        multiset<int> ints;
        set<int> seps;
        ints.insert(n);
        seps.insert(-1);
        seps.insert(n);
        vpi pq;
        rep(i, 0, n) pq.pb({occ[i], i});
        sort(all(pq));
        for(int i = 0; i < sz(pq); i++){
            auto [col, row] = pq[i];
            if(i == 0 || pq[i - 1].f != col) ans = max(ans, (col + 1 - 1 - l) * *ints.rbegin());
            int top = *prev(seps.lower_bound(row)), bottom = *seps.upper_bound(row);
            ints.erase(ints.find(bottom - top - 1));
            seps.insert(row);
            ints.insert(row - top - 1);
            ints.insert(bottom - row - 1);
            if(i + 1 >= n || pq[i + 1].f != col) ans = max(ans, (col + 1 - l) * *ints.rbegin());
        }
    }
    cout << ans << nL;
    
    return 0;
}
