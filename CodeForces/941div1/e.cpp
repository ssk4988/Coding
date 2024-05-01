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
    int n, m, k; cin >> n >> m >> k;
    vvi grid(n, vi(m));
    vi cnt(k);
    rep(i, 0, n){
        rep(j, 0, m){
            cin >> grid[i][j];
            grid[i][j]--;
            cnt[grid[i][j]]++;
        }
    }
    vi order(k);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b){
        return cnt[a] > cnt[b];
    });
    vi rev(k);
    rep(i, 0, k){
        rev[order[i]] = i;
    }
    vvi ans;
    rep(i, 0, n){
        rep(j, 0, m){
            int height = 2 * (m - 1 - j);
            rep(d, 0, height){
                ans.pb({i, j, d+1, grid[i][j]});
            }
            int width = rev[grid[i][j]] + m;
            rep(d, j, width){
                ans.pb({i, d+1, height, grid[i][j]});
            }
        }
    }
    rep(idx, 0, k){
        int c = order[idx];
        rep(i, 0, n){
            int height = 2 * (m - 1);
            for(int d = 1; d <= height; d += 2){
                ans.pb({i, m + idx, d, c});
            }
        }
        rep(d, 0, 2 * (m - 1)){
            ans.pb({n, m + idx, d+1, c});
        }
    }
    assert(sz(ans) <= 400000);
    cout << sz(ans) << nL;
    for(auto& v : ans){
        cout << v[0]+1 << " " << v[1]+1 << " " << v[2]+1 << " " << v[3]+1 << nL;
    }
    
    return 0;
}
