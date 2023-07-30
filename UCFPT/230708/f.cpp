#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pl = pair<ll, ll>;
#define pb push_back
#define f first
#define s second

const ll inf = 1e16;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi;
    ll val = 0, lzadd = 0;
    ll a = 0, lza = 0;
    ll mindp = inf, minsum = inf;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void setdp(int idx, ll x){
        if(lo + 1 == hi){
            mindp = x;
            minsum = a + mindp;
        }
        else{
            push();
            int mid = lo + (hi - lo) / 2;
            if(mid <= idx){
                r->setdp(idx, x);
            }
            else l->setdp(idx, x);
            mindp = min(l->mindp, r->mindp);
            minsum = min(l->minsum, r->minsum);
        }
    }
    void seta(int L, int R, ll x){
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R){
            lza = a = x;
            minsum = a + mindp;
        }
        else{
            push();
            l->seta(L, R, x), r->seta(L, R, x);
            minsum = min(l->minsum, r->minsum);
        }
    }
    ll query(int L, int R){
        if(R <= lo || hi <= L) return inf;
        if(L <= lo && hi <= R) return minsum;
        push();
        return min(l->query(L, R), r->query(L, R));
    }
    // void add(int L, int R, ll x){
    //     if(R <= lo || hi <= L) return;
    //     if(L <= lo && hi <= R){
    //         val += x;
    //         lzadd += x;
    //     }
    //     else{
    //         push();
    //         l->add(L, R, x), r->add(L, R, x);
    //         val = min(l->val, r->val);
    //     }
    // }
    void push(){
        // if(lzadd){
        //     l->add(lo, hi, lzadd), r->add(lo, hi, lzadd);
        //     lzadd = 0;
        // }
        if(lza){
            l->seta(lo, hi, lza), r->seta(lo, hi, lza);
            lza = 0;
        }
    }
};

bool debug = false;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll len; cin >> n >> len;
    vl h(n + 1), w(n + 1);
    vl pref(n + 1);
    rep(i, 1, n + 1){
        cin >> h[i] >> w[i];
        pref[i] = w[i];
        pref[i] += pref[i - 1];
    }
    stack<pl> st;
    Node tree(0, n + 1);
    vl dp(n + 1);
    int lef = 0;
    tree.setdp(0, 0);
    st.push({inf, 0});
    rep(i, 1, n + 1){
        pl nex = {h[i], i};
        int previdx;
        while(st.top() < nex){
            pl t = st.top();
            st.pop();
            // previdx = st.size() ? st.top().s : 0;
            // tree.add(previdx, t.s, -t.f);
        }
        previdx = st.top().s;
        // tree.add(previdx, i, h[i]);
        tree.seta(previdx, i, h[i]);
        st.push({h[i], i});
        while(pref[i] - pref[lef] > len) lef++;
        dp[i] = tree.query(lef, i);
        if(debug) cout << "dp[" << i << "]=" << dp[i] << "\n";
        tree.setdp(i, dp[i]);
        
    }
    cout << dp[n] << "\n";
    
}
