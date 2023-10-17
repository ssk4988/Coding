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
    int n; cin >> n;
    vvi grid(n, vi(n));
    bool works = true;
    rep(i, 0, n){
        vi freq(n);
        rep(j, 0, n){
            int k; cin >> k; k--;
            grid[i][j] = k;
            freq[k]++;
        }
        rep(j, 0, n){
            if(freq[j] != 1) works = false;
        }
    }
    rep(i, 0, n){
        vi freq(n);
        rep(j, 0, n){
            freq[grid[j][i]]++;
        }
        rep(j, 0, n){
            if(freq[j] != 1) works = false;
        }
    }
    cout << (works ? "YES": "NO") << nL;
    
    return 0;
}