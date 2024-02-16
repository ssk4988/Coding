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
const int NUM_STATES = 18;
using vb = int;
using vvb = int*;
// using vvb = vi;
// using vb = vector<bool>;
// using vvb = vector<vector<bool>>;

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


inline int stateidx(int i, int j, int k){
    return k + 2 * j + 2 * 3 * i;
}

int* gen(int freq){
    // vvb res(NUM_STATES, vb(NUM_STATES));
    // vvb res(NUM_STATES);
    int *res = new int[NUM_STATES];
    memset(res, 0, sizeof res);
    // if(freq != 0){
    //     cout << "bruh\n";
    // }
    rep(i, 0, 3){
        rep(j, 0, 3){
            rep(k, 0, 2){
                rep(h, 0, 3){
                    rep(use, 0, 1 + (k == 0)){
                        if(i + j + h + 2 * use <= freq && (freq - (i + j + h + 2 * use)) % 3 == 0){
                            // if(i + j + h == 0 && use){
                            //     cout << "used\n";
                            // }
                            // if(i + j + h == 0 && !use) cout << "stay same\n";
                            // res[stateidx(i, j, k)][stateidx(h, i, use|k)] = 1;
                            res[stateidx(i, j, k)] |= 1 << stateidx(h, i, use|k);
                        }
                    }
                }
            }
        }
    }
    return res;
}

int* comb(int* a, int* b){
    // vvb res(NUM_STATES);
    int*res = new int[NUM_STATES];
    memset(res, 0, sizeof res);
    // vvb res(NUM_STATES, vb(NUM_STATES));
    // vi rows(NUM_STATES), 
    // vi cols(NUM_STATES);
    int *cols = new int[NUM_STATES];
    memset(cols, 0, sizeof cols);
    rep(i, 0, NUM_STATES){
        rep(j, 0, NUM_STATES){
            // rows[i] |= a[i][j] << j;
            cols[i] |= ((b[j] >> i) & 1) << j;
        }
    }
    rep(i, 0, NUM_STATES){
        rep(j, 0, NUM_STATES){
            res[i] |= bool(a[i] & cols[j]) << j;
            // res[i][j] = bool(rows[i] & cols[j]);
        }
    }
    // rep(i, 0, n){
    //     rep(l, 0, k){
    //         if(!a[i][l]) continue;
    //         rep(j, 0, m){
    //             res[i][j] = res[i][j] || (a[i][l] && b[l][j]);
    //         }
    //         // if(res[i][j]){
    //         //     cout << "br";
    //         // }
    //     }
    // }
    // int sum = 0;
    // rep(i, 0, n){
    //     sum += accumulate(all(res[i]), 0);
    // }
    return res;
}

// vvb ident(){
//     vvb res(NUM_STATES, vb(NUM_STATES));
//     rep(i, 0, NUM_STATES){
//         res[i][i] = 1;
//     }
//     return res;
// }


const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, freq=0;
    int* mat=0;
	Node(int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
			mat = comb(l->mat, r->mat);
            freq = l->freq;
		}
        else{
            mat = gen(freq);
        }
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            freq = x;
            mat = gen(freq);
        }
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
            mat = comb(l->mat, r->mat);
            freq = l->freq;
		}
	}
	void push() {
        
	}
};

// int cnt(vvb a) {
//     int sum = 0;
//     rep(j, 0, sz(a)){
//         rep(k, 0, sz(a[j])){
//             sum += a[j][k];
//         }
//     }
//     return sum;
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int most = 0;
    // rep(i, 0, 30){
    //     cout << i << " " << cnt(gen(i)) << "\n";
    // }
    // vvb on(NUM_STATES, vb(NUM_STATES));
    // rep(i, 0, 10){
    //     rep(j, 0, 10){
    //         vvb a = gen(i) * gen(j);
    //         rep(k, 0, NUM_STATES){
    //             rep(l, 0, NUM_STATES){
    //                 if(a[k][l]) on[k][l] = true;
    //             }
    //         }
    //         int c = cnt(a);
    //         most = max(most, c);
            
    //         // cout << i << " " << j << " " << c << "\n";
    //     }
    // }
    // rep(i, 0, NUM_STATES){
    //     rep(j, 0, NUM_STATES){
    //         if(on[i][j]) cout << i << " to " << j << "\n";
    //     }
    // }
    // cout << most << "\n";
    // cout << cnt(on) << "\n";
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n), c;
        rep(i, 0, n){
            cin >> a[i];
            rep(j, -2, 3){
                c.pb(a[i] + j);
            }
        }
        sort(all(c));
        c.erase(unique(all(c)), c.end());
        rep(i, 0, n){
            a[i] = lower_bound(all(c), a[i]) - c.begin();
            // cout << a[i] << " ";
        }
        // cout << "\n";
        Node tree(0, sz(c));
        map<int, int> freq;
        rep(i, 0, n){
            // cout << "update " << i << ":\n";
            freq[a[i]]++;
            tree.set(a[i], a[i]+1, freq[a[i]]);
            // cout << tree.mat[stateidx(0, 0, 0)][stateidx(0, 0, 1)];
            int res = tree.mat[0];
            cout << res;
            // cout << ((tree.mat[0] >> stateidx(0, 0, 1)) & 1);
            // cout << ((tree.mat[stateidx(0, 0, 0)] >> stateidx(0, 0, 1)) & 1);
            // for(auto [key, val] : freq){
            //     cout << key << "," << val << "\n";
            // }
            // rep(j, 0, NUM_STATES){
            //     cout << j << " " << tree.mat[0][j] << "\n";
            // }
        }
        cout << "\n";
        // return 0;
    }
    
    return 0;
}