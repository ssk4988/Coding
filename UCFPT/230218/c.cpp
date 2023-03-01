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

int n, k, ans = 0;

struct trie
{
    vector<trie *> next;
    trie *parent = NULL;
    int leafcount = 0;
    // string let = "";
    trie(trie *par) : next(26, NULL)
    {
        parent = par;
        // let = c;
    }
    trie *getChild(char c)
    {
        int ind = c - 'a';
        if (next[ind] == NULL)
        {
            next[ind] = new trie(this);
            // next[ind]->let = let + c;
        }
        return next[ind];
    }
};
bool cmp(trie *a, trie *b)
{
    if (a == NULL || b == NULL)
    {
        if (b == NULL)
        {
            return false;
        }
        return true;
    }
    return a->leafcount < b->leafcount;
}

int solve(trie *cur)
{
    rep(i, 0, sz(cur->next))
    {
        if (cur->next[i] != NULL)
        {
            cur->leafcount += solve(cur->next[i]);
        }
    }
    sort(all(cur->next), cmp);
    int ind = sz(cur->next) - 1;
    while (cur->leafcount > k)
    {
        cur->leafcount -= cur->next[ind]->leafcount;
        // cout << cur->next[ind]->let << " " << cur->next[ind]->leafcount << nL;
        ans++;
        ind--;
    }

    return cur->leafcount;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> k;
    trie *root = new trie(NULL);
    // root->let = "rm ";
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        trie *cur = root;
        rep(j, 0, sz(str))
        {
            cur = cur->getChild(str[j]);
        }
        cur->leafcount++;
    }
    solve(root);
    if (root->leafcount > 0)
    {
        ans++;
        // cout << root->let << " " << root->leafcount << nL;
    }
    cout << ans << nL;

    return 0;
}
