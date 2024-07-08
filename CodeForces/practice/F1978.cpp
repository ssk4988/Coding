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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
        // cout << "join " << a << "<" << b << " ";
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

const int LIM = 1e6 + 10;
vi divs[LIM];
pi pre[LIM];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(i, 2, LIM) {
        pre[i] = {-1, -1};
        if(sz(divs[i]) == 0) {
            for(int j = i; j < LIM; j += i){
                divs[j].pb(i);
            }
        }
    }
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        // r - c + n-1
        UF uf(2 * n - 1);
        vi diags;
        vvi ds = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int r = 0, c = 0;
        rep(t, 0, 4){
            rep(x, 0, n-1){
                diags.pb(r - c + n-1);
                r += ds[t][0], c += ds[t][1];
            }
        }
        // rep(i, 0, 4 * (n-1)){
        //     diags.pb(diags[i]);
        // }
        rep(i, 0, sz(diags)){
            int add = diags[i];
            // cout << add << " ";
            add = a[n-1 - (add)%n];
            for(int div : divs[add]){
                if(pre[div].f != -1){
                    uf.join(diags[i], pre[div].f);
                }
                pre[div] = {diags[i], i};
            }
            if(i >= k) {
                int rem = diags[i - k];
                rem = a[n-1 - (rem)%n];
                for(int div : divs[rem]){
                    if(pre[div].s == i - k) pre[div] = {-1, -1};
                }
            }
            // cout << add << " ";
        }
        // cout << "\n";
        ll ans = 0;
        rep(i, 0, sz(uf.e)){
            // cout << a[n-1 - i%n] << " ";
            if(a[n-1 - i%n] == 1) {
                // cout << "cont " << n - abs(n-1 - i) << " ";
                ans += n - abs(n-1 - i);
            }
            else if(uf.find(i) == i) ans++;
        }
        cout << ans << "\n";
        for(int x : a){
            for(int div : divs[x]){
                pre[div] = {-1, -1};
            }
        }
    }
    
    return 0;
}
