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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll) M);
}

ull modpow(ull b, ull e, ull mod){
    ull ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2){
        if(e & 1) ans = modmul(ans, b, mod);
    }
    return ans;
}

bool isPrime(ull n) {
    if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for(ull a : A) {
        ull p = modpow(a % n, d, n), i = s;
        while(p != 1 && p != n - 1 && a % n && i--){
            p = modmul(p, p, n);
        }
        if(p != n - 1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n){
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while(t++ % 40 || __gcd(prd, n) == 1) {
        if(x==y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<ull> factor(ull n){
    if(n == 1) return {};
    if(isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int LIM = 1e5 + 10;
    vvi factors(LIM, {1});
    vi mobius(LIM, 1);
    vi composite(LIM);
    composite[0] = composite[1] = true;
    vi primes;
    rep(i, 2, LIM){
        factors[i].pb(i);
        if(!composite[i]){
            primes.pb(i);
            mobius[i] = -1;
        } 
        ll sq = ll(i) * i;
        for(int j = i * 2; j < LIM; j += i){
            factors[j].pb(i);
            if(!composite[i]){
                composite[j] = true;
                if(j % sq == 0) mobius[j] = 0;
                else mobius[j] *= mobius[i];
            }
        }
    }
    int n;
    cin >> n;
    vl a(n);
    set<ll> ss;
    rep(i, 0, n){
        cin >> a[i];
        ss.insert(a[i]);
    }
    a.clear();
    for(ll i : ss){
        a.pb(i);
    }
    n = sz(a);
    vvi gs(LIM);
    for(ll i : a){
        // factors.pb(i);
        for(int div : factors[i]){
            gs[div].pb(i);
        }
    }
    ll ans = 0;
    vi freq(LIM);
    for(int i = LIM - 1; i >= 1; i--){
        sort(all(gs[i]));
        reverse(all(gs[i]));
        stack<int> st;
        vi updates;
        for(int j : gs[i]){
            int sum = 0;
            int rem = j / i;
            for(int div : factors[rem]){
                sum += mobius[div] * freq[div];
            }
            while(st.size() > 0 && sum > 0){
                int las = st.top(); st.pop();
                ans = max(ans, (ll) rem * las * i / __gcd(rem, las));
                for(int div : factors[las]){
                    if(rem % div == 0) sum -= mobius[div];
                    freq[div]--;
                }
            }
            st.push(rem);
            for(int div : factors[rem]){
                freq[div]++;
                updates.pb(div);
            }
        }
        for(int j : updates){
            freq[j] = 0;
        }
    }
    if(sz(a) == 1){
        ans = a[0];
    }
    cout << ans << nL;
    // try 2 4 8
    
    return 0;
}
