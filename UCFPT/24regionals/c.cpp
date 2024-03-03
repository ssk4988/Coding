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
    ll r, c, d, n; cin >> r >> c >> d >> n;
    int ROW_LIM = 5e6 + 1e5;
    if(r >= ROW_LIM - 10) {
        cout << 0 << "\n";
        return 0;
    }
    vector<vpi> rows(ROW_LIM);
    vector<unordered_set<int>> students(ROW_LIM);
    rep(_, 0, n){
        ll i, j; cin >> i >> j;
        students[i].insert(j);
        rows[i].emplace_back(j-1, 2);
        rows[i].emplace_back(j+1, 2);
        rep(r1, i - d, i + d + 1){
            if(r1 <= 0 || r1 >= ROW_LIM) continue;
            ll wid = sqrtl(d * d - (i - r1) * (i - r1));
            // cout << "circle " << _ << " covers " << (j - wid) << " to " << (j + wid) << " on row " << r1 << "\n";
            rows[r1].emplace_back(j - wid, -1);
            rows[r1].emplace_back(j - wid, 2);
            rows[r1].emplace_back(j + wid + 1, +1);
            rows[r1].emplace_back(j + wid + 1, 2);
        }
    }
    int best = 1e9;
    rep(row, 1, r+1){
        rows[row].emplace_back(1, 2);
        rows[row].emplace_back(c, 2);
        sort(all(rows[row]));
        int cur = 0;
        // cout << "sweeping on row " << row << "\n";
        for(auto [col, dif] : rows[row]){
            if(dif != 2) cur -= dif;
            // cur += dif;
            else if(1 <= col && col <= c && !students[row].count(col)){
                // cout << "col " << col << " " << cur << "\n";
                best = min(best, cur);
            }
        }
    }
    cout << best << "\n";

    
    return 0;
}