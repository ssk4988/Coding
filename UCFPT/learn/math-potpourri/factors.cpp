#include <bits/stdc++.h>
using namespace std;

using ll = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

using int128 = __uint128_t;

const ll inf = 1ULL << 63;

inline ll mult(ll a, ll b)
{
    int128 res = int128(a) * int128(b);
    return res >= inf ? inf : ll(res);
    // ll req = (inf + a - 1) / a;
    // return b >= req ? inf : a * b;
}

const int LIM = 10000;
bool composite[LIM];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    composite[0] = composite[1] = true;
    vi primes;
    rep(i, 2, LIM)
    {
        if (composite[i])
            continue;
        primes.pb(i);
        for (int j = i * i; j < LIM; j += i)
            composite[j] = true;
    }
    {
        ll cur = 1, cnt = 0;
        rep(i, 0, sz(primes))
        {
            cur = mult(cur, primes[i]);
            if (cur == inf)
                break;
            cnt++;
        }
        // cout << cnt << "\n";
    }
    // at most 15 primes can be used
    ll cnt = 0;
    map<ll, vl> res;
    auto go = [&](ll n, ll k, ll ps, ll pidx, ll plim, auto &&go) -> void {
        if(k > 1) res[n].pb(k);
        cnt++;
        if(pidx == 0) plim = 100;
        rep(p, 1, plim+1){
            k = mult(k, primes[pidx]);
            if(k == inf) break;
            ps++;
            int128 n1 = int128(n) * int128(ps) / int128(p);
            if(n1 >= inf) break;
            n = ll(n1);
            // n = mult(n, ps);
            // if(n == inf) break;
            // n /= p;
            go(n, k, ps, pidx+1, p, go);
        }
    };
    go(1, 1, 0, 0, 0, go);
    // cout << cnt << " " << sz(res) << "\n";
    for(auto &[key, val] : res){
        sort(all(val));
    }
    ll x;
    while(cin >> x){
        assert(res.count(x));
        cout << x << " " << res[x][0] << "\n";
    }

    return 0;
}
