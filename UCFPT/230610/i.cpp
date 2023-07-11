#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

const int inf = 1e9;
struct Node{
    Node *l = 0, *r = 0;
    int lo, hi, val = 0;
    Node(int lo, int hi): lo(lo), hi(hi){
        int mid = lo + (hi - lo)/2;
        if(lo + 1 != hi){
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
    }
    int query(int L, int R){
        if(R <= lo || hi <= L) return 0;
        if(L <= lo && hi <= R) return val;
        return max(l->query(L, R), r->query(L, R));
    }
    void set(int idx, int v){
        if(lo + 1 == hi){
            val = v;
            return;
        }
        if((lo + (hi - lo)/2) <= idx) r->set(idx, v);
        else l->set(idx, v);
        val = max(l->val, r->val);
    }
};

int querypref(map<int, int> &m, int idx){
    return prev(m.upper_bound(idx))->s;
}
int querysuff(map<int, int> &m, int idx){
    return (m.lower_bound(idx))->s;
}

void insertpref(map<int, int> &m, int idx, int v){
    if(querypref(m, idx) >= v)return;
    while(true){
        auto it = m.upper_bound(idx);
        if(it == m.end() || it->s > v) break;
        m.erase(it);
    }
    m[idx] = v;
}

void insertsuff(map<int, int> &m, int idx, int v){
    if(querysuff(m, idx) >= v) return;
    while(true){
        auto it = m.lower_bound(idx);
        if(it == m.begin()) break;
        it = prev(it);
        if(it->s > v) break;
        m.erase(it);
    }
    m[idx] = v;
}

using a3 = array<int, 3>;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int rg, cg; cin >> rg >> cg;rg--,cg--;
    vvi grid(n, vi(n));
    vvi dp(n, vi(n));
    int maxv = 0;
    vvpi q(int(1e6+100));
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> grid[i][j];
            maxv = max(grid[i][j], maxv);
            q[grid[i][j]].pb({i, j});
        }
    }
    maxv++;
    // vector<Node*> rows(n), cols(n);
    vector<map<int, int>> rowpref(n), rowsuff(n), colpref(n), colsuff(n);
    rep(i, 0, n){
        // rows[i] = new Node(0, n);
        // cols[i] = new Node(0, n);
        rowpref[i][-1] = 0;
        colpref[i][-1] = 0;
        rowsuff[i][n] = 0;
        colsuff[i][n] = 0;
    }
    for(int i = maxv - 1; i >= 0; i--){
        for(auto [r, c] : q[i]){
            int mv = 0;
            if(r > 0){
                if(c >= 2){
                    mv = max(mv, querypref(rowpref[r-1], c-2));
                }
                if(c + 2 < n){
                    mv = max(mv, querysuff(rowsuff[r-1], c+2));
                }
            }
            if(r + 1 < n){
                if(c >= 2){
                    mv = max(mv, querypref(rowpref[r+1], c-2));
                }
                if(c + 2 < n){
                    mv = max(mv, querysuff(rowsuff[r+1], c+2));
                }
            }
            if(c > 0){
                if(r >= 2){
                    mv = max(mv, querypref(colpref[c-1], r-2));
                }
                if(r + 2 < n){
                    mv = max(mv, querysuff(colsuff[c-1], r+2));
                }
            }
            if(c + 1 < n){
                if(r >= 2){
                    mv = max(mv, querypref(colpref[c+1], r-2));
                }
                if(r + 2 < n){
                    mv = max(mv, querysuff(colsuff[c+1], r+2));
                }
            }
            dp[r][c] = 1 + mv;
        }
        for(auto [r, c] : q[i]){
            insertpref(rowpref[r], c, dp[r][c]);
            insertsuff(rowsuff[r], c, dp[r][c]);
            insertpref(colpref[c], r, dp[r][c]);
            insertsuff(colsuff[c], r, dp[r][c]);
            // rows[r]->set(c, dp[r][c]);
            // cols[c]->set(r, dp[r][c]);
        }
    }
    cout << dp[rg][cg] << "\n";

    return 0;
}