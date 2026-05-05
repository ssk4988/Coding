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

const int LIM = 2e5 + 10;
int phi[LIM];

void calculatePhi() {
	rep(i,0,LIM) phi[i] = i&1 ? i : i/2;
	for (int i = 3; i < LIM; i += 2) if(phi[i] == i)
		for (int j = i; j < LIM; j += i) phi[j] -= phi[j] / i;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    calculatePhi();
    vl pref(LIM);
    vi prime(LIM, 1);
    phi[1]--;
    // cout << phi[0] << " " << phi[1] << " " << phi[2] << endl;
    rep(i, 2, LIM) {
        if(!prime[i]) continue;
        for(int j = 2*i; j < LIM; j += i) prime[j] = false, pref[j] += phi[j/i];
    }
    rep(i, 1, LIM) {
        pref[i] += pref[i-1];
    }
    int q; cin >> q;
    rep(i, 0, q) {
        int l,r ; cin >> l >> r; l--;
        ll ans = (pref[r] - pref[l]);
        cout << ans << "\n";
    }

    return 0;
}
