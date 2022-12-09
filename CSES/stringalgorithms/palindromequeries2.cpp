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

int n;
vpl pows;
pl m = {1000000007, 1000000009};
ll base = 29;

ll mod1(ll k, ll m1){
    return (k % m1 + m1) % m1;
}

pl mod(pl k){
    return {mod1(k.f, m.f), mod1(k.s, m.s)};
}

void update(vpl &bit, int index, int val){
    
    pl p1 = mod({pows[index].f * val, pows[index].s * val});
    index++;
    while(index < bit.size()){
        bit[index] = mod({bit[index].f + p1.f, bit[index].s + p1.s});
        index += index&-index;
    }
}

pl query(vpl &bit, int index){
    index++;
    pl cur = {0, 0};
    while(index > 0){
        cur = mod({cur.f + bit[index].f, cur.s + bit[index].s});
        index -= index&-index;
    }
    return cur;
}

pl query(vpl &bit, int l, int r){
    l--;
    pl rres = query(bit, r);
    pl lres = query(bit, l);
    pl res = mod({rres.f - lres.f, rres.s - lres.s});
    l++;
    return mod({res.f * pows[n - l].f, res.s * pows[n - l].s});
}



int revindex(int k){
    return n - 1 - k;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> n >> q;
    pows = vpl(n + 1);
    pows[0] = {1, 1};
    rep(i, 1, n + 1){
        pows[i] = mod({pows[i - 1].f * base, pows[i - 1].s * base});
    }
    vpl bit(n);
    vpl rbit(n);
    string str; cin >> str;
    rep(i, 0, n){
        update(bit, i, str[i] - 'a' + 1);
        update(rbit, revindex(i), str[i] - 'a' + 1);
    }
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int ind;
            char c;
            cin >> ind >> c;
            ind--;
            update(bit, ind, c - str[ind]);
            update(rbit, revindex(ind), c - str[ind]);
            str[ind] = c;
        }
        else{
            int a, b;
            cin >> a >> b;
            a--; b--;
            pl p1 = query(bit, a, b);
            pl p2 = query(rbit, revindex(b), revindex(a));
            cout << ((p1 == p2) ? "YES" : "NO") << nL;
        }
    }

    
    return 0;
}