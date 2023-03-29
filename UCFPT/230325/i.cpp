#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2")
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vii;
typedef vector<vi> vvi;

#define nl '\n'
#define rep(i,a,b) for(int i = a; i < b; i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

typedef complex<double> C;
typedef vector<double> vd;

const ll MODL = 1e9 + 7;
const int MOD = int(MODL);
// const ld PI = acos(-1.0L);

void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<C> R(2, 1);
	static vector<C> rt(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0, acos(-1.0) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for(int k = 1; k < n; k *= 2) 
		for(int i = 0; i < n; i += 2*k) rep(j,0,k) {
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
			a[i + j + k] = a[i+j] - z;
			a[i + j] += z;
		}
}

template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<C> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
	rep(i,0,sz(b)) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i &(n-1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
		ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}

const int DEBUG = true;
const int N2POW2 = 2048;

const int maxN = 2e5+10;
vl dp[maxN];
int isred[maxN];
vi child[maxN];
int n,m;
void dfs (int cur){
    dp[cur] = vl(1, 1);
    // dp[cur].push_back(0);
    for(int i : child[cur]){
        dfs(i);
        dp[cur] = convMod<MOD>(dp[cur], dp[i]);
    }
    if(isred[cur]){
        if(dp[cur].size() > 1) dp[cur][1] = (dp[cur][1] + 1) % MOD;
        else dp[cur].push_back(1);
    }
    else{
        dp[cur][0] = (dp[cur][0] + 1) % MOD;
    }
    // dp[cur][isred[cur]]++;
    // dp[cur][isred[cur]] %= MOD;
    // dp[cur].resize(min(sz(dp[cur]), m + 1));
    // while(dp[cur].size() > 5 && dp[cur].back() == 0){
    //     dp[cur].pop_back();
    // }
    
    // dfsorder[dfsordersz++] = cur;
    
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    vi par(n, -1);
    rep(i, 0, n - 1){
        cin >> par[i + 1];
        par[i + 1]--;
        child[par[i + 1]].push_back(i + 1);    
    }
    rep(i, 0, m){
        int v; cin >> v;
        v--; isred[v] = true;
    }
    
    dfs(0);
    dp[0].resize(m + 1);
    rep(i, 0, m + 1){
        cout << dp[0][i] << nl;
    }

    
}
