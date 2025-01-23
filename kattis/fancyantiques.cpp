#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const int inf = 1e9+10;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    int m1 = m / 2;
    int m2 = m - m1;
    vi cont(m);
    vi validleft(1 << m1);
    vi validright(1 << m2);
    int base = 0;
    vii pairs;
    int pleft = 0, pright = 0;
    rep(i, 0, n) {
        int a1, p1, a2, p2; cin >> a1 >> p1 >> a2 >> p2;
        a1--, a2--;
        if(p1 < p2) swap(a1, a2), swap(p1, p2);
        cont[a2] += p1 - p2;
        base += p1;
        if(max(a1, a2) < m1) {
            validleft[1 << a1]++;
            validleft[1 << a2]++;
            validleft[(1 << a1) | (1 << a2)]--;
            pleft++;
        } else if(min(a1, a2) >= m1) {
            validright[1 << (a1-m1)]++;
            validright[1 << (a2-m1)]++;
            validright[(1 << (a1-m1)) | (1 << (a2-m1))]--;
            pright++;
        } else pairs.pb({min(a1, a2), max(a1, a2)});
    }
    if(m == 1) {
        cout << base - cont[0] << "\n";
        return 0;
    }
    rep(i, 0, m1) {
        rep(mask, 0, 1 << m1) {
            if((mask >> i)&1) validleft[mask] += validleft[mask ^ (1 << i)];
        }
    }
    rep(i, 0, m2) {
        rep(mask, 0, 1 << m2) {
            if((mask >> i)&1) validright[mask] += validright[mask ^ (1 << i)];
        }
    }
    vvi rightdp(m2+1, vi(1 << m2, -inf));
    rep(mask, 0, sz(validright)) {
        if(validright[mask] != pright) continue;
        rightdp[__builtin_popcount(mask)][mask] = 0;
        rep(i, 0, m2) {
            if ((mask >> i) & 1) rightdp[__builtin_popcount(mask)][mask] += cont[m1+i];
        }
    }
    rep(cnt, 0, sz(rightdp)) {
        rep(bit, 0, m2) {
            for(int mask = sz(rightdp[cnt])-1; mask >= 0; mask--) {
                if((mask >> bit) & 1) continue;
                // cout << sz(rightdp[cnt])-1 << " " << bit << " " << mask << " " << (mask ^ (1 << bit)) << endl;
                rightdp[cnt][mask] = max(rightdp[cnt][mask], rightdp[cnt][mask ^ (1 << bit)]);
            }
        }
        rep(mask, 0, sz(rightdp[cnt])) {
            if(cnt) rightdp[cnt][mask] = max(rightdp[cnt][mask], rightdp[cnt-1][mask]);
        }
    }
    int ans = -inf;
    rep(mask, 0, sz(validleft)) {
        if(validleft[mask] != pleft) continue;
        int bits = k - __builtin_popcount(mask);
        if(bits < 0) continue;
        bits = min(bits, m2);
        int othermask = 0;
        int cans = 0;
        rep(i, 0, m1) if((mask >> i) &1) cans += cont[i];
        for(auto [p1, p2] : pairs) {
            if((mask >> p1) & 1) continue;
            othermask |= 1 << (p2-m1);
        }
        ans = max(ans, rightdp[bits][othermask] + cans);
    }
    if(ans < 0) {
        cout << -1 << "\n";
        return 0;
    }
    ans = base - ans;
    cout << ans << "\n";
    
    return 0;
}
