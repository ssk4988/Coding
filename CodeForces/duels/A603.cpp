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
    vi a(n), b(m); vi c;
    rep(i, 0, n){
        cin >> a[i];
        c.pb(a[i]);
    }
    rep(i, 0, m){
        cin >> b[i];
        c.pb(b[i]);
    }
    sort(all(a)), sort(all(b)), sort(all(c));
    c.erase(unique(all(c)), c.end());
    vi dif(sz(c));
    rep(i, 0, n){
        a[i] = lower_bound(all(c), a[i]) - c.begin();
        dif[a[i]]++;
    }
    rep(i, 0, m){
        b[i] = lower_bound(all(c), b[i]) - c.begin();
        dif[b[i]]--;
    }
    bool works = false;
    int sum = 0;
    for(int i = sz(c) - 1; i >= 0; i--){
        sum += dif[i];
        // cout << i << " " << dif[i] << "\n";
        if(sum > 0){
            works = true;
        }
    }
    cout << (works ? "YES" : "NO") << "\n";
    
    return 0;
}