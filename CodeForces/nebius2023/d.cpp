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


bool DEBUG = false;
int getmin(vi &row){
    int m = sz(row);
    int onecnt = 0;
    rep(i, 0, m){
        if(row[i]) onecnt++;
    }
    int uses = 0;
    rep(i, 0, m - 1){
        if(row[i] && row[i + 1]){
            uses++;i++;
        }
    }
    return max(0, onecnt - min(m/4,uses));
}

int getmax(vi &row){
    int m = sz(row);
    int not11 = 0;
    rep(i, 0, m - 1){
        if(row[i] == 0 || row[i + 1] == 0){
            not11++;
            i++;
        }
    }
    int onecnt = 0;
    rep(i, 0, m){
        if(row[i])onecnt++;
    }
    return max(0, onecnt - (m/4 - min(m/ 4, not11)));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m));
    rep(i, 0, n){
        string j; cin >> j;
        rep(k, 0, m){
            grid[i][k] = j[k] - '0';
        }
    }
    int minans = 0, maxans = 0;
    rep(i, 0, n){
        int minrow = m, maxrow = 0;
        minrow = min(minrow, getmin(grid[i]));
        maxrow = max(maxrow, getmax(grid[i]));
        reverse(all(grid[i]));
        maxrow = max(maxrow, getmax(grid[i]));
        minans += minrow;
        maxans += maxrow;
        if (DEBUG) cout << "for row " << i << ": min of " << minrow << " and max of " << maxrow << nL;
    }
    cout << minans << " " << maxans << nL;
    
    return 0;
}
