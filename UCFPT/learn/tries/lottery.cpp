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

struct Node{
    vector<Node *> nex;
    int cnt = 0;
    Node(): nex(26, NULL){}
};

void add(Node *root, string &w){
    root->cnt++;
    rep(i, 0, sz(w)){
        if(root->nex[w[i] - 'a'] == NULL) root->nex[w[i] - 'a'] = new Node();
        root = root->nex[w[i] - 'a'];
        root->cnt++;
    }
}

int query(Node *root, string &w){
    rep(i, 0, sz(w)){
        if(root->nex[w[i] - 'a'] == NULL) return 0;
        root = root->nex[w[i] - 'a'];
    }
    return root->cnt;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int q; cin >> q;
        Node *pref = new Node(), *suff = new Node();
        bool p = true;
        cout << "Lottery #" << (cn + 1) << ":\n";
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 1){
                string str; cin >> str;
                add(p ? pref : suff, str);
                reverse(all(str));
                add(p ? suff : pref, str);
            }
            else if(t == 2){
                string str; cin >> str;
                int ans = query(p ? pref : suff, str);
                cout << ans << nL;
            }
            else{
                p = !p;
            }
        }
        cout << nL;
    }
    
    return 0;
}
