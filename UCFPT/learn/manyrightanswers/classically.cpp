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
const int M = 100;
template<int B>
struct XORBasis {
	bitset<B> basis[B];
    bitset<M> effect[B];
    int res[B];
    XORBasis() { memset(res, -1, sizeof res); }
	int npivot = 0, nfree = 0;
	bool check(bitset<B> v, bitset<M> &ans) {
		rep(i, 0, B)
			if (v[i] && res[i] != -1){ 
                v ^= basis[i];
                ans ^= effect[i];
            }
		return v.none();
	}
	bool add(bitset<B> v, int idx) {
        bitset<M> e;
		rep(i, 0, B)
			if (v.test(i)) {
				if (basis[i].none()){ 
                    e.flip(idx);
                    effect[i] = e;
                    res[i] = idx;
                    return basis[i] = v, ++npivot;
                }
                e ^= effect[i];
				v ^= basis[i];
			}
        return !++nfree;
	}
    void clear(){
        memset(res, -1, sizeof res);
        rep(i, 0, B){
            if(basis[i].any()) basis[i] &= ~basis[i];
            if(effect[i].any()) effect[i] &= ~effect[i];
        }
        npivot = nfree = 0;
    }
};

XORBasis<10000> x;
vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int r, c; cin >> r >> c;
        x.clear();
        vvi grid(r, vi(c));
        vi b(r * c);
        rep(i, 0, r){
            string str; cin >> str;
            rep(j, 0, c){
                grid[i][j] = str[j] - '0';
                b[i * c + j] = grid[i][j];
            }
        }
        auto toggle = [&](vvi &g, int row, int col)-> void {
            g[row][col] ^= 1;
            rep(i, 0, 4){
                int r1 = row + dr[i], c1 = col + dc[i];
                if(r1 < 0 || r1 >= r || c1 < 0 || c1 >= c) continue;
                g[r1][c1] ^= 1;
            }
        };
        rep(j, 0, c){
            vvi o(grid), net(r, vi(c));
            toggle(o, 0, j); toggle(net, 0, j);
            rep(i, 1, r){
                rep(j1, 0, c){
                    if(o[i-1][j1]){
                        toggle(o, i, j1), toggle(net, i, j1);
                    }
                }
            }
            // cout << "for changing " << 0 << " " << j << ":\n";
            bitset<10000> bs;
            rep(i, 0, r){
                rep(j1, 0, c){
                    // cout << net[i][j1];
                    if(net[i][j1])bs[i * c + j1].flip();
                }
                // cout << "\n";
            }
            x.add(bs, j);
        }
        bitset<10000> bs;
        rep(i, 0, r){
            rep(j, 0, c){
                if(grid[i][j]) bs[i * c + j].flip();
            }
        }
        bitset<M> ans;
        bool cando = x.check(bs, ans);
        if(cando){
            vvi tog(r, vi(c));
            rep(j, 0, c){
                if(ans[j]){
                    toggle(grid, 0, j);
                    tog[0][j] ^= 1;
                }
            }
            rep(i, 1, r){
                rep(j, 0, c){
                    if(grid[i-1][j]){
                        toggle(grid, i, j);
                        tog[i][j] ^= 1;
                    }
                }
            }
            rep(i, 0, r){
                rep(j, 0, c){
                    cout << (tog[i][j] ? 'X' : '_');
                }
                cout << "\n";
            }
            // cout << "leftover:\n";
            // rep(i, 0, r){
            //     rep(j, 0, c){
            //         cout << (grid[i][j] ? 'X' : '_');
            //     }
            //     cout << "\n";
            // }
        }
        else cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}
