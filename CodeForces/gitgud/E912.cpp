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


vl s;
vl test;
const ll LIM = 1'000'000'000'000'000'000;
void go(int idx, ll cur) {
    if(idx == sz(s)){
        return;
    }
    ll b = LIM / cur;
    if(b < s[idx]) return;
    test.pb(cur * s[idx]);
    go(idx, cur * s[idx]);
    go(idx+1, cur);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl p = vl(n);
    rep(i, 0, n){
        cin >> p[i];
    }
    ll k; cin >> k;
    vl a, b;
    rep(i, 0, n){
        (i % 2 == 0 ? a : b).pb(p[i]);
    }
    // cout << "a: ";
    // for(auto x : a) cout << x << " ";
    // cout << endl;
    // cout << "b: ";
    // for(auto x : b) cout << x << " ";
    // cout << endl;

    test.pb(1);
    s = a;
    go(0, 1);
    // cout << sz(test) << "\n";
    vl aset = test;
    test = {1};
    s = b;
    go(0, 1);
    // cout << sz(test) << "\n";
    vl bset = test;
    sort(all(aset));
    sort(all(bset));
    auto check = [&](ll target) -> bool {
        ll ans = 0;
        int bpnt = sz(bset) - 1;
        rep(apnt, 0, sz(aset)){
            ll over = target / aset[apnt];
            // cout << "over: " << over << endl;
            while(bpnt >= 0 && bset[bpnt] > over){
                bpnt--;
            }
            ans += bpnt + 1;
        }
        return ans >= k;
    };
    ll x = 0;
    for(ll dif = 1LL << 60; dif; dif >>= 1){
        if(!check(x + dif)) x += dif;
    }
    x++;
    cout << x << "\n";
    // cout << check(LIM) << "\n";

    return 0;
}
