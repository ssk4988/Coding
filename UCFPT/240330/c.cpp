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

ll MOD = -1;
inline ll mod(ll k){
    return k % MOD;
}
inline ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

// ax = b mod m
ll solve(ll a, ll b, ll m){
    // cout << "solving " << a << "x=" << b << " mod " << m << endl;
    ll g = __gcd(m, a);
    if(g != 1) return solve(a / g, b / g, m / g);
    ll x, y;
    ll res = euclid(a, m, x, y);
    // cout << "modinv of " << a << " mod " << m << " is " << x << endl;
    x = (x % m + m) % m;
    return (b * x) % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, q; cin >> n >> q;
    MOD = n;
    vl chairs(n);
    iota(all(chairs), 0);
    ll a = 1, b = 0; // lazy offsets
    ll c = 1, d = 0; // formula for current alive guys since last recalc
    ll alive = n;

    rep(_, 0, q){
        char t; cin >> t;
        if(t == '?'){
            int y; cin >> y; y %= n;
            ll e = mod(a * c), f = mod(mod(a * d) + b); // e * x + f = y;
            ll g = __gcd(n, e);
            // cout << "query position " << y << endl;
            // cout << e << "*x+" << f << "=" << y << endl;
            // cout << "a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl;
            y = mod1(y - f);
            if(y % g != 0){
                cout << -1 << "\n";
                continue;
            }
            ll idx = solve(e, y, n);
            idx %= n;
            idx = mod(c * idx + d);
            // cout << "idx=" << idx << endl;

            if(chairs[idx] == -1) cout << -1 << "\n";
            else if(chairs[idx] == 0) cout << n << "\n";
            else cout << chairs[idx] << "\n";
        }
        else if(t == '+'){
            ll add; cin >> add;
            b = mod(b + add);
        }
        else{
            ll mult; cin >> mult;
            if(__gcd(mult, alive) == 1){
                b = mod(b * mult);
                a = mod(a * mult);
                continue;
            }
            // cout << "before: \n";
            // vi o(n, -1);
            // rep(i, 0, n){
            //     if(chairs[i] == -1) continue;
            //     o[mod(mod(a * i) + b)] = chairs[i];
            // }
            // rep(i, 0, n) cout << o[i] << " ";
            // cout << endl;
            vector<vpl> bucket(n);
            rep(i, 0, n){
                if(chairs[i] == -1) continue;
                bucket[mod(mod(mod(a * i) + b) * mult)].pb({mod(mod(a * i) + b), chairs[i]});
            }
            alive = 0;
            vi guys;
            rep(i, 0, n){
                if(sz(bucket[i]) == 0) {
                    chairs[i] = -1;
                    continue;
                }
                int mindex = 0;
                rep(j, 0, sz(bucket[i])){
                    if(mod1(i - bucket[i][j].f) < mod1(i - bucket[i][mindex].f)) mindex = j;
                }
                chairs[i] = bucket[i][mindex].s;
                guys.pb(i);
                alive++;
            }
            if(sz(guys) == 1){
                c = 0, d = guys[0];
            }
            else{
                c = mod1(guys[1] - guys[0]), d = guys[0];
            }
            // cout << mult << ": ";
            // rep(i, 0, n){
                // cout << chairs[i] << " ";
            // }
            // cout << endl;
            a = 1; b = 0;
            // cout << "a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl;
        }
    }
    
    return 0;
}