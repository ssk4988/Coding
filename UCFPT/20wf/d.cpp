#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define nl '\n'

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vii = vector<pii>;
using vvi = vector<vi>;

array<vi, 2> manacher(const string &s)
{
    int n = sz(s);
    array<vi, 2> p = {vi(n+1), vi (n)};
    rep(z, 0, 2) for(int i = 0, l = 0, r = 0; i < n; i++)
    {
        int t = r-i+!z;
        if(i<r) p[z][i] = min(t, p[z][l+t]);
        int L = i-p[z][i], R = i+p[z][i]-!z;
        while(L >=1 && R+1<n && s[L-1] == s[R+1])
            p[z][i]++, L--, R++;
        if(R > r) l=L, r=R;
    }
    return p;
}

const int DEBUG = false, BLANK = -1, INF = 1e9;
struct Node {
    int lo, hi;
    Node *l = 0, *r = 0;
    pii val = {-INF, -INF}; // j-i, dp[i] + i - j
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void push() {
        if(!l) return;
        if(a == 0 && b == 0) return;
        l->add(lo, hi, a, b);
        r->add(lo, hi, a, b);
        a = 0;
        b = 0;
    }
    void add(int L, int R, ll lin, ll con) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            a += lin;
            b += con;
            // b += con + lin * (lo - L);
            // cout << "add on " << lo << "," << hi << " a=" << lin << " b=" << con << "\n";
            return;
        }
        push(), l->add(L, R, lin, con), r->add(L, R, lin, con);
    }
};


void solve()
{
    string str; cin >> str;
    int n = sz(str);
    vi man = manacher(str)[0];
    vi dp(n+1, INF);
    dp[0] = n;
    rep(i, 0, n){



    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}
