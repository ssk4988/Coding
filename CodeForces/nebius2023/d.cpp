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
    int uses = m / 4;
    vi used(m);
    int ans = 0;
    rep(i, 0, m){
        if (uses <= 0) break;
        if(used[i]) continue;
        if(row[i] != 1) continue;

        // row[i] = 1
        int l = i, r = i; // create [l, r)
        for(r = i; r < m && row[r]; r++);
        if(r - l == 1) continue;
        int start;
        if(l == 0){
            start = l;
        }
        else if(r == m){
            start = l + ((r - l) % 2);
        }
        else{
            start = l;
        }
        for(int j = start; j < r && uses > 0; j += 2){
            used[j] = used[j + 1] = true;
            uses--;
            ans += 1;
        }
    }
    int onecnt = 0;
    rep(i, 0, m){
        if(!used[i] && row[i] == 1){
            onecnt++;
        }
    }
    // if (DEBUG) cout << "cur ans: " << ans << " 2bed left: " << uses << " ones left: " << onecnt << nL;
    if(uses > 0){
        // necessarily isolated
        ans += onecnt;
    }
    else{
        // not necessarily isolated
        // either ran out of uses or removed exactly all uses
        // no 2 beds anymore
        ans += onecnt;
    }

    // all ones are isolated now, or not?
    // ans += max(0, onecnt - uses);

    return ans;
}

int getmax(vi &row){
    int m = sz(row);
    int uses = m / 4;
    vi used(m);
    int ans = 0;
    rep(i, 0, m - 1){
        if(uses <= 0) break;
        if(used[i] || used[i + 1]){
            continue;
        }
        if(row[i] != 1 && row[i + 1] != 1){
            ans++;
            uses--;
            used[i] = used[i + 1] = true;
        }
    }
    rep(i, 0, m - 1){
        if(uses <= 0) break;
        if(used[i] || used[i + 1]){
            continue;
        }
        if(row[i] == 1 && row[i + 1] == 1){
            ans++;
            uses--;
            used[i] = used[i + 1] = true;
        }
    }
    int onecnt = 0;
    rep(i, 0, m){
        if(!used[i] && row[i] == 1){
            onecnt++;
        }
    }
    // assert(uses <= 0);
    ans += onecnt - uses; // assume one 1 bedroom now
    return ans;
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
