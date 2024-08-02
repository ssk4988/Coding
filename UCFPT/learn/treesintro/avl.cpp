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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Node
{
    int val;
    int height = 0;
    bool bal = true;
    Node *l = 0, *r = 0;
    Node(int val) : val(val) { calc(); }
    void insert(int v)
    {
        if (v < val)
        {
            if (l)
                l->insert(v);
            else
                l = new Node(v);
        }
        else
        {
            if (r)
                r->insert(v);
            else
                r = new Node(v);
        }
        calc();
    }
    void calc()
    {
        bal = true;
        int lh = 0, rh = 0;
        if (l)
        {
            // l->calc();
            lh = l->height;
            if(!l->bal) bal = false;
        }
        if (r) {
            // r->calc();
            rh = r->height;
            if(!r->bal) bal = false;
        }
        height = 1 + max(lh, rh);
        if(abs(lh - rh) > 1) bal = false;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        Node *v = NULL;
        bool bal = true;
        rep(i, 0, n){
            int a; cin >> a;
            if(i == 0) v = new Node(a);
            else v->insert(a);
            v->calc();
            if(!v->bal) bal = false;
            // cout << i << " " << bal << "\n";
        }
        cout << "Tree #" << (cn + 1) << ": " << (bal ? "KEEP" : "REMOVE") << "\n";
    }

    return 0;
}
