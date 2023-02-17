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
        int h, w;
        cin >> h >> w;
        vector<vector<char>> grid(h, vector<char>(w));
        rep(i, 0, h){
            string str; cin >> str;
            rep(j, 0, w){
                grid[i][j] = str[j];
            }
        }
        int s; cin >> s;
        rep(k, 0, s){
            int hp, wp, hi, wi;
            cin >> hi >> wi;
            int scale = min(hi / h, wi / w);
            hp = (hi % h) / 2;
            wp = (wi % w) / 2;
            vector<vector<char>> ans(hi, vector<char>(wi, '.'));
            rep(i, 0, h){
                rep(j, 0, w){
                    rep(i1, 0, scale){
                        rep(j1, 0, scale){
                            ans[hp + i * scale + i1][wp + j * scale + j1] = grid[i][j];
                        }
                    }
                }
            }
            rep(i, 0, hi){
                rep(j, 0, wi){
                    cout << ans[i][j];
                }
                cout << nL;
            }
        }
    }
    
    return 0;
}