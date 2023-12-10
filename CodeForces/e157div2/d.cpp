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
    vi a(n);
    vi freq(30), target(30);
    rep(i, 0, n-1) {
        cin >> a[i+1];
        a[i+1] ^= a[i];
        rep(j, 0, 25){
            if(a[i + 1] & (1 << j)) freq[j]++;
        }
    }
    rep(i, 0, n){
        rep(j, 0, 25) if(i & (1 << j)) target[j]++;
    }
    // rep(i, 0, n) cout << i << " " << a[i] << endl;
    // rep(i, 0, 25){
    //     cout << i << " " << target[i] << " " << freq[i] << endl;
    // }
    int start = 0;
    rep(i, 0, 25){
        assert(target[i] == freq[i] || target[i] == (n - freq[i]));
        if(target[i] != freq[i]) start ^= 1 << i;
    }
    rep(i, 0, n) a[i] ^= start;
    rep(i, 0, n) cout << a[i] << " ";
    cout << nL;
    
    
    return 0;
}
