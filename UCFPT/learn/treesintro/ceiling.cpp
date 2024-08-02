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

map<pii, int> lbl;

struct Node
{
    int val;
    int hsh = -1;
    Node *l = 0, *r = 0;
    Node(int val) : val(val) {}
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
    }
    void calc()
    {
        if(hsh != -1) return;
        pii v;
        if(l) v.first = (l->calc(), l->hsh);
        if(r) v.second = (r->calc(), r->hsh);
        if(!lbl.count(v)) lbl[v] = sz(lbl);
        hsh = lbl[v];
    }
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    lbl[{-1, -1}] = 0;
    set<int> hshs;
    rep(i, 0, n){
        Node *root = NULL;
        rep(j, 0, k){
            int a; cin >> a;
            if(j) root->insert(a);
            else root = new Node(a);
        }
        root->calc();
        hshs.insert(root->hsh);
    }
    cout << sz(hshs) << "\n";

    return 0;
}
