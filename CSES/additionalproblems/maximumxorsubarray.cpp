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

struct Node
{
    Node *nex[2] = {};
    int bitnum;
    Node(int b) : bitnum(b) {}
    void add(int val)
    {
        if (bitnum == 0)
            return;
        int idx = 1 & (val >> (bitnum - 1));
        if (nex[idx] == NULL)
        {
            nex[idx] = new Node(bitnum - 1);
        }
        nex[idx]->add(val);
    }
    int closest(int val)
    {
        int ans = 0;
        if (bitnum == 0)
            return ans;
        int idx = 1 & (val >> (bitnum - 1));
        if (nex[idx] != NULL)
        {
            ans |= idx << (bitnum - 1);
            ans |= nex[idx]->closest(val);
        }
        else if (nex[1 - idx] != NULL)
        {
            ans |= (1 - idx) << (bitnum - 1);
            ans |= nex[1 - idx]->closest(val);
        }
        return ans;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    rep(i, 1, n) a[i] ^= a[i - 1];
    Node root(30);
    root.add(0);
    int ans = 0;
    rep(i, 0, n){
        int c = root.closest(~a[i]);
        ans = max(ans, c ^ a[i]);
        root.add(a[i]);
    }
    cout << ans << nL;

    return 0;
}