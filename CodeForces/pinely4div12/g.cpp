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
        int n, m, k, q; cin >> n >> m >> k >> q;
        vvi grid(n, vi(m));
        string s; cin >> s;
        vpi ans;
        for(char c : s){
            if(c == 'H') {
                rep(i, 0, n){
                    bool works = true;
                    rep(j, 0, m){
                        if(grid[i][j] != (j >= k)) works = false;
                    }
                    if(works){
                        ans.pb({i, 0});
                        rep(j, 0, k){
                            grid[i][j] = 1;
                        }
                        goto done;
                    }
                }
                rep(i, 0, n){
                    bool works = true;
                    rep(j, 0, k) if(grid[i][j]) works = false;
                    if(works){
                        ans.pb({i, 0});
                        rep(j, 0, k){
                            grid[i][j] = 1;
                        }
                        goto done;
                    }
                }
            }
            else {
                rep(j, 0, m){
                    bool works = true;
                    rep(i, 0, n){
                        if(grid[i][j] != (i >= k)) works = false;
                    }
                    if(works){
                        ans.pb({0, j});
                        rep(i, 0, k){
                            grid[i][j] = 1;
                        }
                        goto done;
                    }
                }
                rep(j, 0, m){
                    bool works = true;
                    rep(i, 0, k) if(grid[i][j]) works = false;
                    if(works){
                        ans.pb({0, j});
                        rep(i, 0, k){
                            grid[i][j] = 1;
                        }
                        goto done;
                    }
                }
            }

            done:
            vi rows, cols;
            rep(i, 0, n){
                int cnt = accumulate(all(grid[i]), 0);
                if(cnt == m) rows.pb(i);
            }
            rep(j, 0, m){
                int cnt = 0;
                rep(i, 0, n){
                    cnt += grid[i][j];
                }
                if(cnt == n) cols.pb(j);
            }
            for(int i : rows){
                rep(j, 0, m) grid[i][j] = 0;
            }
            for(int j : cols){
                rep(i, 0, n) grid[i][j] = 0;
            }
        }
        assert(sz(ans) == q);
        for(auto [i, j] : ans){
            cout << i+1 << " " << j+1 << "\n";
        }
    }
    
    return 0;
}
