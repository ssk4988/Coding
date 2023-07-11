#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using pl = pair<ll,ll>;
using vpl = vector<pl>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using ld = long double;

const int LIM = 1e5+100;
bitset<LIM> isPrime;
vi er(){
    const int S = (int)round(sqrt(LIM)), R = LIM / 2;
    vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM) * 1.1));
    vector<pi> cp;
    for(int i = 3; i < + S; i += 2) if(!sieve[i]) {
        cp.pb({i, i * i / 2});
        for(int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
    }
    for(int L = 1; L <= R; L += S){
        array<bool, S> block{};
        for(auto &[p, idx]:cp)
            for(int i = idx; i < S+L; idx = (i+=p)) block[i-L]=1;
        rep(i, 0,min(S,R-L))
            if(!block[i]) pr.pb((L+i)*2+1);
    }
    for(int i : pr) isPrime[i] = 1;
    return pr;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true){
        int n; cin >> n;
        if(n == 0){
            cin >> n;
            break;
        }
        vi e = er();
        unordered_map<ll, unordered_map<ll, ll>> howtoget;
        for(ll i : e){
            ll v = 0;
            for(ll p = i; p <= n; p *= i){
                v += n / p;
            }
            rep(j, 1, v + 1){
                howtoget[v / j][i]++;
            }
        }
        vl keys;
        for(auto &p : howtoget) keys.pb(p.f);
        sort(all(keys));
        reverse(all(keys));
        ll x; cin >> x;
        ll ans = 0;
        unordered_map<ll, ll> sufffreq;
        ll pp = 1;
        for(ll key : keys){
            if(key < x) break;
            unordered_map<ll, ll> &fs = howtoget[key];
            vl fskey;
            for(auto &p : fs){
                fskey.pb(p.f);
            }
            ll ss = sz(fs);
            ll ways = 0;
            rep(i, 1, 1 << ss){
                ll prod = pp;
                rep(j, 0, ss){
                    if(i & (1 << j)){
                        prod /= sufffreq[fskey[j]]+1;
                    }
                }
                ways += prod;
            }
            if(ways > 1) ans += ways * (ways - 1) / 2;
            for(ll i : fskey){
                pp /= sufffreq[i] + 1;
                sufffreq[i]+=fs[i];
                pp *= sufffreq[i] + 1;
            }
        }
        cout << ans << "\n";
    }
}