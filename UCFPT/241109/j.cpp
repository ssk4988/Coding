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

pi operator+(pi a, pi b) {
    return {a.f + b.f, a.s + b.s};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vpi v(n);
    rep(i, 0, n){
        cin >> v[i].f >> v[i].s;
    }
    n = min(30, n);
    v.resize(n);
    int n2 = n / 2;
    vpi sm(1 << n2);
    rep(mask, 0, sz(sm)){
        rep(i, 0, n2){
            if((mask >> i) & 1) sm[mask] = sm[mask] + v[i];
        }
    }
    vector<pair<pi, pi>> lookup;
    // cerr << "to " << sz(sm) << endl;
    rep(mask, 0, sz(sm)){
        for(int sub = mask; sub >= 0; sub = min(sub-1, (sub-1)&mask)) {
            int sub1 = mask ^ sub;
            pi res = sm[sub1];
            res.f *= -1, res.s *= -1;
            res = res + sm[sub];
            lookup.emplace_back(res, pi{sub, sub1});
        }
    }
    int n3 = n - n2;
    sm = vpi(1 << n3);
    rep(mask, 0, sz(sm)){
        rep(i, 0, n3){
            if((mask >> i) & 1) sm[mask] = sm[mask] + v[i + n2];
        }
    }
    vector<pair<pi, pi>> lookup2;
    rep(mask, 0, sz(sm)){
        for(int sub = mask; sub >= 0; sub = min(sub-1, (sub-1)&mask)) {
            int sub1 = mask ^ sub;
            pi res = sm[sub1];
            res.f *= -1, res.s *= -1;
            res = res + sm[sub];
            res.f *= -1, res.s *= -1;
            lookup2.emplace_back(res, pi{sub, sub1});
        }
    }
    sort(all(lookup));
    sort(all(lookup2));
    int p2 = 0;
    rep(p1, 0, sz(lookup)) {
        while(p2 < sz(lookup2) && lookup2[p2].f < lookup[p1].f) p2++;
        if(p2 < sz(lookup2) && lookup2[p2].f == lookup[p1].f) {
            auto [psub, psub1] = lookup[p1].s;
            auto [sub, sub1] = lookup2[p2].s;
            int m = (sub << n2) ^ psub;
            int m1 = (sub1 << n2) ^ psub1;
            if(__builtin_popcount(m) == 0 || __builtin_popcount(m1) == 0) continue;
            // cerr << res.f << " " << res.s << " " << m << " " << m1 << endl;
            cout << "no\n";
            cout << __builtin_popcount(m) << " ";
            rep(i, 0, n){
                if((m >> i) & 1) cout << i+1 << " ";
            }
            cout << "\n";
            cout << __builtin_popcount(m1) << " ";
            rep(i, 0, n){
                if((m1 >> i) & 1) cout << i+1 << " ";
            }
            cout << "\n";
            return 0;

        }
    }
    cout << "yes\n";
    
    return 0;
}
