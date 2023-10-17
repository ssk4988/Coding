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
				jmp[k][j] = jmp[k - 1][j] & jmp[k - 1][j + pw];
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return jmp[dep][a] & jmp[dep][b - (1 << dep)];
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
        rep(i, 0, n){
            cin >> a[i];
        }
        RMQ r(a);
        int q; cin >> q;
        rep(i, 0, q){
            int l, k; cin >> l >> k;
            l--;
            if(a[l] < k){
                cout << "-1 ";
                continue;
            }
            int lo = l, hi = n - 1;
            while(lo < hi){
                int mid = lo + (hi - lo + 1) / 2;
                int res = r.query(l, mid + 1);
                if(res >= k){
                    lo = mid;
                }
                else hi = mid - 1;
            }
            cout << (lo + 1) << " ";
        }
        cout << nL;
    }
    
    return 0;
}
