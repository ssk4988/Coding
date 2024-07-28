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
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int N = 2000;
    // vi divcnt(N+1);
    // rep(i, 1, N+1){
    //     for(int j = i; j <= N; j += i){
    //         divcnt[j]++;
    //     }
    // }
    int nc; cin >> nc;
    rep(cn,0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        vi pre(n+1, -1);
        UF uf(n);
        bool works = true;
        vpi ans;
        for(int t = n-1; t > 0; t--){
            rep(i, 0, t) pre[i] = -1;
            bool did = false;
            rep(i, 0, n){
                if(pre[a[i] % t] == -1){
                    pre[a[i]%t] = i;
                } else if(!uf.sameSet(pre[a[i]%t], i)){
                    did = true;
                    ans.pb({pre[a[i]%t], i});
                    uf.join(pre[a[i]%t], i);
                    break;
                }
            }
            if(!did){
                works = false;
                break;
            }
        }
        if(works){
            reverse(all(ans));
            cout << "YES\n";
            for(auto [i, j] : ans){
                cout << i+1 << " " << j+1 << "\n";
            }
        } else cout << "NO\n";
    }
    
    return 0;
}
