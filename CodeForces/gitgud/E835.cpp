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
    int n, x, y; cin >> n >> x >> y;

    int numqueries = 0;
    auto query = [&](vi &idxs) -> bool {
        if(sz(idxs) == 0) return false;
        numqueries++;
        assert(numqueries <= 19);
        cout << "? " << sz(idxs) << " ";
        for(int i : idxs){
            cout << (i + 1) << " ";
        }
        cout << endl;
        int res; cin >> res;
        if(sz(idxs) % 2 == 1 && res != x) return true;
        if(sz(idxs) % 2 == 0 && res != 0) return true;
        return false;
    };
    int BITS = 10;
    vvi idxs(BITS);
    rep(i, 0, n){
        rep(j, 0, BITS){
            if((i >> j) & 1) idxs[j].pb(i);
        }
    }
    int diffmask = 0;
    int diffbit = -1;
    rep(i, 0, BITS){
        bool res = query(idxs[i]);
        if(res){
            diffbit = i;
            diffmask |= 1 << i;
        }
    }
    // cout << diffmask << endl;
    vi search;
    rep(i, 0, n){
        if((i >> diffbit) & 1) search.pb(i);
    }
    rep(i, 0, BITS){
        if(i == diffbit) continue;
        if(sz(search) == 1) break;
        vvi searches(2);
        for(int j : search){
            searches[(j >> i) & 1].pb(j);
        }
        bool res = query(searches[0]);
        if(res) search = searches[0];
        else search = searches[1];
    }
    int idx1 = search[0], idx2 = search[0] ^ diffmask;
    if(idx1 > idx2) swap(idx1, idx2);
    cout << "! " << (idx1 + 1) << " " << (idx2 + 1) << endl;

    return 0;
}
