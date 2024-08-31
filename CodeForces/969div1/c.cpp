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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = __gcd(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
        if(a == b) return 0;
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return __gcd(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){ cin >> a[i]; }
        if(n == 1){
            cout << 1 << "\n";
            continue;
        }
        // n=2????
        vi dif(n);
        rep(i, 0, n-1){
            dif[i] = abs(a[i] - a[i+1]);
        }
        RMQ<int> rmq(dif);
        ll ans = 0;
        rep(L, 0, n){
            // L=n-1????
            int R1 = L-1;
            for(int d = 1 << 20; d; d /= 2){
                int cur = R1 + d;
                if(cur < n && rmq.query(L, cur) == 0) R1 = cur;
            }
            int R2 = L-1;
            for(int d = 1 << 20; d; d /= 2){
                int cur = R2 + d;
                if(cur < n && __builtin_popcount(rmq.query(L, cur)) != 1) R2 = cur;
            }
            R2++;
            ans += R1 - L + 1;
            ans += n - R2;
            // cout << cn << " " << L << " " << R1 << " " << R2 << "\n";
        }
        cout << ans << "\n";
    }
    
    return 0;
}
