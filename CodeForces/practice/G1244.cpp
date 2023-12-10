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
    ll n; ll k; cin >> n >> k;
    ll mink = n * (n + 1) / 2;
    if(k < mink){
        cout << "-1\n";
        return 0;
    }
    ll cur = mink;
    vl order(n);
    vi used(n);
    ll highestleft = n - 1;
    iota(all(order), 0);
    for(int i = (n - 1) / 2; i >= 0; i--) {
        ll dif = min(k - cur, highestleft - i);
        ll in = dif + i;
        used[in] = true;
        cur += dif;
        if(highestleft == in) highestleft--;
        order[i] = in;
    }
    cout << cur << "\n";
    for(int ins = (n - 1) / 2 + 1, ptr = 0; ptr < n; ptr++){
        if(!used[ptr]) order[ins++] = ptr;
    }
    rep(i, 0, n){
        cout << (i + 1) << " ";
    }
    cout << "\n";
    rep(i, 0, n){
        cout << (order[i] + 1) << " ";
    }
    cout << "\n";
    
    return 0;
}
