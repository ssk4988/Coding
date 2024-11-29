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

struct Node;
vector<Node*> v;

struct Node {
    int distinct = 0;
    Node *l = 0, *r = 0;
    Node(int lo, int hi){
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    Node *add(int idx, int lo, int hi) {
        Node *n = new Node(*this);
        if(lo + 1 == hi){
            n->distinct = min(1, n->distinct + 1);
            return n;
        }
        int mid = lo + (hi - lo) / 2;
        if(idx < mid) n->l = n->l->add(idx, lo, mid);
        else n->r = n->r->add(idx, mid, hi);
        n->distinct = n->l->distinct + n->r->distinct;
        return n;
    }
};

const int N = 1e6 + 10;
vi children[N];
int p[N], jmp[N], dep[N];
Node *tree[N];


int used = 0;
void createNode(int par = 0){
    p[used] = par;
    dep[used] = 1 + dep[par];
    jmp[used] = dep[jmp[par]] * 2 == dep[par] + dep[jmp[jmp[par]]] ? jmp[jmp[par]] : par;
    used++;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    createNode();
    tree[0] = new Node(0, N);
    vi updates;
    updates.pb(0);
    int qs = 0;
    rep(i, 0, q)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int x;
            cin >> x;
            int u = used;
            createNode(updates.back());
            tree[u] = tree[updates.back()]->add(x, 0, N);
            children[updates.back()].pb(u);
            updates.pb(u);
        }
        if (c == '-')
        {
            int k;
            cin >> k;
            int cur = updates.back();
            int tardep = dep[cur] - k;
            while(dep[cur] > tardep){
                if(dep[jmp[cur]] >= tardep) cur = jmp[cur];
                else cur = p[cur];
            }
            updates.pb(cur);
        }
        if (c == '!')
            updates.pop_back();
        if (c == '?')
        {
            cout << tree[updates.back()]->distinct << endl;
        }
    }

    return 0;
}
