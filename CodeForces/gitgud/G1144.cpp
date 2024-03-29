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
    rep(i, 0, n){
        cin >> a[i];
    }
    if(n == 1){
        cout << "YES\n1\n";
        return 0;
    }
    vpi inc(n, {-1, -1});
    vpi dec(n, {1e9, -1});
    inc[0] = {1e9, -1};
    dec[0] = {-1, -1};
    rep(i, 1, n){
        if(a[i] > a[i-1]){
            inc[i] = max(inc[i], {inc[i-1].f, 0});
        }
        if(a[i] < a[i-1]){
            dec[i] = min(dec[i], {dec[i-1].f, 1});
        }
        if(a[i] > dec[i-1].f){
            inc[i] = max(inc[i], {a[i-1], 1});
        }
        if(a[i] < inc[i-1].f){
            dec[i] = min(dec[i], {a[i-1], 0});
        }
    }
    vi seq(n, -1);
    pi cur = inc[n-1].s != -1 ? pi{n-1, 0} : pi{n-1, 1};
    while(cur.s != -1){
        seq[cur.f] = cur.s;
        cur = {cur.f - 1, (cur.s ? dec : inc)[cur.f].s};
    }
    if(cur.f == -1){
        cout << "YES\n";
        rep(i, 0, n){
            cout << seq[i] << " ";
        }
        cout << "\n";
    }
    else{
        cout << "NO\n";
    }
    return 0;
}
