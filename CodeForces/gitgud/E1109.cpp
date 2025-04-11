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
ll mod;
vl primes, pw;
vector<vl> pp;


ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

ll calcpow(int idx, ll e) {
    while(sz(pp[idx]) <= e){
        pp[idx].pb(pp[idx].back()*primes[idx]%mod);
    }
    return pp[idx][e];
}

struct Node {
    int lo, hi;
    Node *l=0, *r=0;
    ll sm = 1, lzmult=1;
    vl lzpw;
    Node(int lo, int hi) : lo(lo), hi(hi), lzpw(sz(primes)) {
        if(lo+1<hi) {
            int mid = lo + (hi-lo)/2;
            l=new Node(lo, mid), r=new Node(mid, hi);
            sm = (l->calc() + r->calc()) % mod;
        }
    }
    void mult(int L, int R, ll x, vl& xp) {
        if(hi <= L || R <= lo) return;
        if(L <= lo && hi <= R) {
            (sm *= x) %= mod;
            (lzmult *= x) %= mod;
            rep(i, 0, sz(xp)) lzpw[i] += xp[i];
            return;
        }
        push();
        l->mult(L, R, x, xp), r->mult(L, R, x, xp);
        sm = (l->calc() + r->calc()) % mod;
    }
    ll calc() {
        ll ans = sm;
        rep(i, 0, sz(primes)) {
            (ans *= calcpow(i, lzpw[i])) %= mod;
        }
        return ans;
    }
    ll query(int L, int R) {
        if(hi <= L || R <= lo) return 0;
        if(L <= lo && hi <= R) {
            return calc();
        }
        push();
        return (l->query(L, R) + r->query(L, R))%mod;
    }
    void push() {
        if(lzmult == 1 && accumulate(all(lzpw), 0) == 0) return;
        l->mult(lo, hi, lzmult, lzpw), r->mult(lo, hi, lzmult, lzpw);
        lzmult = 1;
        sm = calc();
        for(auto &x : lzpw) x=0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);    
    int n; cin >> n >> mod;
    const int LIM = 1e5;
    vi prime(LIM, 1);
    vi lprimes;
    ll mod1 = mod;
    for(ll i = 2; i < LIM; i++) {
        if(prime[i]) {
            lprimes.pb(i);
            if(mod1 % i == 0) {
                primes.pb(i);
                pw.pb(0);
            }
            while(mod1 % i == 0) {
                pw.back()++;
                mod1 /= i;
            }
            for(ll j = i*i; j < LIM; j+= i) prime[j] = 0;
        }
    }
    if(mod1 > 1) {
        primes.pb(mod1);
        pw.pb(1);
    }
    pp.assign(sz(pw), vl{1});
    vl a(n);
    Node tree(0, n);
    auto factor = [&](ll x) -> pair<ll, vl> {
        vl xp(sz(primes));
        rep(i, 0, sz(primes)) {
            while(x % primes[i] == 0) {
                x /= primes[i];
                xp[i]++;
            }
        }
        return {x, xp};
    };
    rep(i, 0, n){
        cin >> a[i];
        auto [x, xp] = factor(a[i]);
        tree.mult(i, i+1, x, xp);
    }
    int q; cin >> q;
    ll phi = mod;
    rep(i, 0, sz(primes)) {
        phi /= primes[i];
        phi *= primes[i]-1;
    }
    rep(qid, 0, q) {
        // cerr << "before: ";
        // rep(i, 0, n){
        //     cerr << tree.query(i, i+1) << " ";
        // }
        // cerr << endl;
        int t; cin >> t;
        if(t == 1) {
            ll l, r, x; cin >> l >> r >> x;
            l--;
            auto [x1, xp] = factor(x);
            tree.mult(l, r, x1, xp);
        } else if(t == 2) {
            int p; ll x; cin >> p >> x; p--;
            auto [x1, xp] = factor(x);
            rep(i, 0, sz(primes)) {
                xp[i] *= -1;
            }
            tree.mult(p, p+1, modpow(x1, phi-1), xp);
        } else {
            int l, r; cin >> l >> r; l--;
            cout << tree.query(l, r) << "\n";
        }
    }
    return 0;
}
