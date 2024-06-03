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

const int BITS = 10;
const int NMASK = 1 << BITS;
using bs = bitset<NMASK>;
bs rows[NMASK], cols[NMASK], fun[NMASK];
pii ev[BITS][BITS][2][2];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    int b = 1 << k;
    rep(i, 0, k){
        rep(j, 0, k){
            rep(b1, 0, 2){
                rep(b2, 0, 2){
                    ev[i][j][b1][b2] = {n+1, -1};
                }
            }
        }
    }
    vi prec(256);
    prec['!'] = 10;
    prec['='] = 9;
    prec['&'] = 8;
    prec['|'] = 7;
    prec['^'] = 6;
    rep(i, 0, n){
        int p1, p2; cin >> p1 >> p2; p1--, p2--;
        string s; cin >> s;
        reverse(all(s));
        int retval; cin >> retval;
        rep(x, 0, 2){
            rep(y, 0, 2){
                vi term;
                vector<char> ops;
                auto calc = [&]()->void {
                    char op = ops.back(); ops.pop_back();
                    int t1 = term.back(); term.pop_back();
                    if(op == '!'){
                        term.pb(!t1);
                        return;
                    }
                    int t2 = term.back(); term.pop_back();
                    if(op == '='){ term.pb(t1 == t2); return; }
                    if(op == '&'){ term.pb(t1 & t2); return; }
                    if(op == '|'){ term.pb(t1 | t2); return; }
                    if(op == '^'){ term.pb(t1 ^ t2); return; }
                    assert(false);
                };
                for(char c : s){
                    if(c == '1') term.pb(1);
                    else if(c == '0') term.pb(0);
                    else if(c == 'x') term.pb(x);
                    else if(c == 'y') term.pb(y);
                    else if(c == ')') ops.pb(c);
                    else if(c == '(') {
                        while(ops.back() != ')') calc();
                        ops.pop_back();
                    }
                    else {
                        while(sz(ops) && prec[ops.back()] > prec[c]) calc();
                        ops.pb(c);
                    }
                }
                while(sz(ops)) calc();
                int val = term.back();
                if(val) ev[p1][p2][x][y] = min(ev[p1][p2][x][y], {i, retval});
            }
        }
    }
    int finval; cin >> finval;
    ll ref = 0, sym = 0, trans = 0;
    rep(m1, 0, b){
        rep(m2, 0, b){
            pii best = {n, finval};
            rep(p1, 0, k){
                rep(p2, 0, k){
                    best = min(best, ev[p1][p2][(m1 >> p1) & 1][(m2 >> p2) & 1]);
                }
            }
            fun[m1][m2] = best.s;
            rows[m1][m2] = fun[m1][m2];
            cols[m2][m1] = fun[m1][m2];
        }
    }
    rep(m1, 0, b){
        if(fun[m1][m1] == 1) ref++;
        rep(m2, 0, b){
            if(fun[m1][m2] && fun[m2][m1]) sym++;
            if(fun[m1][m2]) continue;
            trans += (rows[m1] & cols[m2]).count();
        }
    }
    cout << ref << " " << sym << " " << trans << "\n";
    
    return 0;
}
