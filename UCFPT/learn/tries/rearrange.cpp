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

vi order, rorder;

struct Node
{
    vector<Node *> nex;
    int cnt = 0, here = 0;
    Node() : nex(26, NULL) {}
};

void add(Node *root, string &w)
{
    root->cnt++;
    rep(i, 0, sz(w))
    {
        int c = w[i] - 'a';
        if (root->nex[c] == NULL)
            root->nex[c] = new Node();
        root = root->nex[c];
        root->cnt++;
    }
    root->here++;
}

string fin(Node *root, int k)
{
    string ans = "";
    while (root->here < k)
    {
        k -= root->here;
        vector<Node *> c;
        int numc = 0;
        rep(i, 0, sz(order))
        {
            if (root->nex[order[i]] != NULL)
            {
                numc++;
                if (k > root->nex[order[i]]->cnt)
                    k -= root->nex[order[i]]->cnt;
                else
                {
                    ans.pb(char(order[i] + 'a'));
                    root = root->nex[order[i]];
                    break;
                }
            }
        }
        if (numc == 0)
            break;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        Node *root = new Node();
        int n, q;
        cin >> n >> q;
        rep(i, 0, n)
        {
            string str;
            cin >> str;
            add(root, str);
        }
        order = vi(26);
        rorder = vi(26);
        rep(i, 0, 26){
            order[i] = i;
            rorder[i] = i;
        }
        cout << "Gift Exchange #" << (cn + 1) << ":\n";
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 1){
                char x, y; cin >> x >> y;
                int x1 = x - 'a', y1 = y - 'a';
                swap(order[rorder[x1]], order[rorder[y1]]);
                swap(rorder[x1], rorder[y1]);
            }
            else{
                int k; cin >> k;
                string res = fin(root, k);
                cout << res << nL;
            }
        }
        cout << nL;
    }

    return 0;
}
