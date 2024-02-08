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
    int n, m; cin >> n >> m;
    string a, b; cin >> a >> b;
    vi av(n), bv(m), cv(m);
    rep(i, 0, m){
        bv[i] = b[i] - 'a';
    }
    rep(i, 0, n){
        av[i] = a[i] - 'a';
        cv[m - n + i] = av[i];
    }
    for(int i = m - n - 1; i >= 0; i--){
        cv[i] = (bv[i + n] - cv[i + n] + 26) % 26;
    }
    // rep(i, 0, n){
    //     for(int j = m - n + i, pre = a[i]; j >= 0; bv[j] = ((bv[j] - pre) % 26 + 26) % 26, j -= n){
    //         pre = bv[j];
    //     }
    // }
    for(int i : cv){
        cout << char('a' + i);
    }
    cout << nL;
    
    
    return 0;
}
