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
    vvi grid(8, vi(8));
    rep(i, 0, 8){
        string str; cin >> str;
        rep(j, 0, 8){
            grid[i][j] = str[j] == '.';
        }
    }
    vi row(8), col(8), d1(15), d2(15);
    int ans = 0;
    auto bt = [&](int idx, auto &&bt)->void{
        if(idx == 8){
            ans++;
            return;
        }
        rep(c, 0, 8){
            int d1v = c + idx, d2v = (7 - c) + idx;
            if(!grid[idx][c] || row[idx] || col[c] || d1[d1v] || d2[d2v]) continue;
            row[idx] = col[c] = d1[d1v] = d2[d2v] = true;
            bt(idx + 1, bt);
            row[idx] = col[c] = d1[d1v] = d2[d2v] = false;
        }
    };
    bt(0, bt);
    cout << ans << nL;
    
    return 0;
}
