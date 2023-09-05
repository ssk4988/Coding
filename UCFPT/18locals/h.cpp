#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

const int inf = 1e9;
struct Node
{
    int lo, hi;
    int val = 0;
    Node *l = 0, *r = 0;
    Node(int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    int query(int L, int R)
    {
        if (R <= lo || hi <= L)
            return -1e9;
        if (L <= lo && hi <= R)
            return val;
        return max(l->query(L, R), r->query(L, R));
    }
    void pointupd(int idx, int v)
    {
        if (lo + 1 == hi)
            val = v;
        else
        {
            int mid = lo + (hi - lo) / 2;
            if (mid <= idx)
                r->pointupd(idx, v);
            else
                l->pointupd(idx, v);
            val = max(l->val, r->val);
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    // Node tree(0, n);
    vi seq(n), idx(n, n);
    rep(i, 0, n)
    {
        int v;
        cin >> v;
        v--;
        // int dp = v > 0 ? tree.query(0, v) : 0;
        // tree.pointupd(v, dp + 1);
        idx[v] = i;
        seq[v] = (v > 0 && idx[v - 1] < idx[v] ? seq[v - 1] : 0) + 1;
    }
    int lis = 0;
    rep(i, 0, n)
    {
        lis = max(lis, seq[i]);
        // cout << i << " " << seq[i] << "\n";
    }
    // int lis = tree.query(0, n);
    cout << (n - lis) << "\n";
}
