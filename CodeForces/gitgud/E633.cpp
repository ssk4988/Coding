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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

template<class T>
struct RMQX {
	vector<vector<T>> jmp;
	RMQX(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

// (n-1-i, k-1) / (n, k)
// i=0: n-i-1! / k-1! / n-i-k! * k! * n-k! / n! = k / n
// i=1: n-k / n-1
// i=2: n-1-k / n-2
// i: n-i-k+1 / n-i


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi v(n), c(n);
    rep(i, 0, n){
        cin >> v[i];
    }
    rep(i, 0, n){
        cin >> c[i];
    }
    RMQ rev(c);
    RMQX vis(v);
    ld ans = 0;
    ld eps = 1e-20l; // 6 for n, 6 for precision, 7 for ans
    ld denom = 1;
    vi calc(n);
    rep(i, 0, n){
        int x = i;
        for(int dif = 1 << 20; dif > 0; dif >>= 1){
            if(x + dif <= n && 100 * vis.query(i, x + dif) <= rev.query(i, x + dif)){
                x += dif;
            }
        }
        // cout << i << " " << x << endl;
        int cont = x > i ? min(100 * vis.query(i, x), rev.query(i, x)) : 0;
        if(x + 1 <= n) cont = max(cont, min(100 * vis.query(i, x + 1), rev.query(i, x + 1)));
        // cout << i << " " << x << " " << cont << "\n";
        calc[i] = cont;
    }
    sort(all(calc));
    rep(i, 0, n){
        if(i == 0) denom = ld(k) / n;
        else denom *= ld(n - i - k + 1) / (n - i);
        if(denom < eps) {
            // cout << "break at " << i << "\n";
            break;
        }
        ans += calc[i] * denom;
    }
    cout << fixed << setprecision(7) << ans << "\n";
    return 0;
}
