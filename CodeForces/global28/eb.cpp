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

void solve() {
    int n, m; cin >> n >> m;
    int edges = 2 * n * m;
    int span = (2 * n + m - 1) * n;
    // cout << edges << " " << span << "\n";
    if(span < edges){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    // cout << endl;
    srand(time(NULL));
    while(true) {
        int nodes = 2 * n + m;
        vvi col(2 * n, vi(m, -1));
        vector<UF> ufs;
        vi cs(m);
        iota(all(cs), 0);
        rep(c, 0, n){
            ufs.push_back(UF(nodes));
        }
        rep(j, 0, m){
            rep(t, 0, n){
        // rep(i, 0, 2 * n){
                rep(v, 0, 2){
                    col[cs[j]][j] = t;
                    (cs[j] += 1) %= 2 * n;
                }
                // int cnt = 0;

                // do {
                //     col[i][j] = rand() % n;
                //     if(cnt > 100){ break; }
                //     cnt++;
                // } while(!ufs[col[i][j]].join(i, 2 * n + j));
                // if(cnt > 100){
                //     goto nxt;
                // }
                // col[i][j] = 
            }
        }
        // cout << "ended" << endl;
        rep(i, 0, 2 * n){
            rep(j, 0, m){
                cout << col[i][j]+1 << " ";
            }
            cout << "\n";
        }
        break;
        nxt:
    }
    // vector<set<int>> cadj(nodes);
    // rep(i, 0, 2 * n){
    //     rep(j, 0, m) cadj[i].insert(2 * n + j), cadj[2 * n + j].insert(i);
    // }
    // vector<UF> ufs;
    // rep(c, 0, n){
    //     ufs.push_back(UF(nodes));
    // }
    // bool works = true;
    // rep(i, 0, n){
    //     rep(j, 0, m){
    //         col[i][j] = i;
    //         assert(ufs[i].join(i, 2 * n + j));
    //     }
    // }
    // rep(i, n, 2*n){
    //     rep(j, 0, m){
    //         int c = 0;
    //         while(c < n && !ufs[c].join(i, 2 * n + j)) {
    //             c++;
    //         }
    //         col[i][j] = c;
    //         if(c == n){
    //             works = false;
    //             goto done;
    //         }
    //         // cout << c+1 << " ";
    //     }
    //     // cout << "\n";
    // }
    // done:
    // if(!works) {
    //     cout << "NO\n";
    //     return;
    // }
    // cout << "YES\n";
    // rep(i, 0, 2*n){
    //     rep(j, 0, m){
    //         cout << col[i][j]+1 << " ";
    //     }
    //     cout << "\n";
    // }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
