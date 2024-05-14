#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pli = pair<ll, int>;

#define f first
#define s second
#define pb push_back
#define rep(i, a, b) for (int i = a; i < (b); ++i)

ll b, m;
vl pw;
pli operator+(pli a, pli b){
    a.f = (a.f * pw[b.s] + b.f) % m;
    a.s += b.s;
    return a;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q, k, p;
    cin >> n >> q >> k >> b >> m;
    rep(i, 0, k) p *= 3;
    vector<pli> dp(p); // [pattern] = {hsh, sz}
    pw.pb(1);
    rep(i, 0, n){
        string v; cin >> v;
        int binval = 0, terval = 0;
        for(char c : v) {
            binval = binval * 2 + (c - '0');
            terval = terval * 3 + (c - '0');
        }
        dp[terval] = dp[terval] + pli{binval, 1};
        pw.pb(pw.back() * b % m);
    }
    for(int d = k-1, pv = 1; d >= 0; d--, pv *= 3)
        rep(i, 0, p)
            if(i / pv % 3 == 2)
                dp[i] = dp[i - 2 * pv] + dp[i - pv];

    rep(i, 0, q){
        string pat; cin >> pat;
        int terval = 0;
        for(char c : pat)
            terval = terval * 3 + (c == '*' ? 2 : c - '0');
        cout << dp[terval].f << "\n";
    }
    
    return 0;
}
