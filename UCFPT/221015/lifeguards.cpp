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

#define maxN 10
#define maxK 10
#define ssz 16

int dp[maxN + 1][maxK + 1][2];
vector<vector<vector<int>>> tree(2, vector<vector<int>>(maxN + 1, vi(2 * ssz, 0)));

void update(vi &segtree, int idx, int val)
{
    int segsz = sz(segtree) / 2;
    idx += segsz;
    segtree[idx] = val;
    for (; idx > 1; idx >>= 1)
    {
        segtree[idx >> 1] = max(segtree[idx], segtree[idx ^ 1]);
    }
}

int maxquery(vi &segtree, int l, int r)
{
    int segsz = segtree.size() / 2;
    int res = 0;
    for (l += segsz, r += segsz; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = max(res, segtree[l++]);
        if (!(r & 1))
            res = max(res, segtree[r--]);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fill(all(tree[1]), vi(2 * ssz, INT_MIN));
    int n, k;
    cin >> n >> k;
    dp[0][0][0] = dp[0][0][1] = 0;
    set<int> start, end;
    map<int, int> endm;
    rep(i, 1, n + 1)
    {
        int l, r;
        cin >> l >> r;

        for (int j = min(k, i); j >= 0; j--)
        {
            if (j)
                dp[i][j][0] = max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]);
            int idx = -1;
            if (ub(all(end), l) != end.end())
            { // && endm.find(*ub(all(end), l)) != endm.end()){
                if (endm.find(*ub(all(end), l)) == endm.end())
                    cout << "bruh\n";
                idx = endm[*ub(all(end), l)];
            }
            else
            {
                // no overlaps
                idx = i; //???????
            }
            if (i != j)
            {
                // if i == 1 do easy
                if (i == 1)
                {
                    dp[i][j][1] = r - l + 1;
                }
                else
                {
                    dp[i][j][1] = max(r - l + 1 + maxquery(tree[0][i - j], 0, idx - 1),
                                      r + maxquery(tree[1][i - j], idx, i - 1));
                }
            }

            update(tree[0][i - j], j, dp[i][j][1]);
            update(tree[1][i - j], j, dp[i][j][1] - r);
        }
        start.insert(l);
        end.insert(r);
        endm[r] = i;
    }
    cout << max(dp[n][k][0], dp[n][k][1]) << nL;

    return 0;
}