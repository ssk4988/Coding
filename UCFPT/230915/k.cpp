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
    vvi starts(n, vi(26));
    vvi ends(n, vi(26));
    rep(i, 0, n){
        string str; cin >> str;
        int cur = 0;
        for(char c = 'a'; c <= 'z'; c++){
            starts[i][c - 'a'] = cur;
            while(cur < m && str[cur] == c) cur++;
            ends[i][c - 'a'] = cur;
        }
    }
    int q; cin >> q;
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--, b--;
        int ans = 0;
        rep(j, 0, 26){
            int a1 = starts[a][j], a2 = ends[a][j];
            int b1 = starts[b][j], b2 = ends[b][j];
            if(b2 <= a1 || a2 <= b1) continue;
            ans += min(a2, b2) - max(a1, b1);
        }
        cout << ans << nL;
    }
    
    return 0;
}
