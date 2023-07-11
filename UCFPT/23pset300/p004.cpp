#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<ll>;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int ALPH = 6;
const int upb = 1 << 6;
struct Node{
    int lo, hi, mid, splitxor = 0;
    vi freq;
    Node *l = NULL, *r = NULL;
    Node(int lo, int hi, vi &v) : lo(lo), hi(hi), freq(upb) {
        mid = (lo + hi) / 2;
        if(lo + 1 == hi) freq[v[lo]]++;
        else{
            l = new Node(lo, mid, v);
            r = new Node(mid, hi, v);
            freq = comb(l->freq, r->freq);
        }
    }
    vi comb(vi &lv, vi &rv){
        vi res(lv);
        rep(i, 0, upb) res[i] += rv[i ^ splitxor];
        return res;
    }
    vi query(int L, int R){
        if(hi <= L || R <= lo) return vi(upb);
        if(L <= lo && hi <= R) return freq;
        vi lv = l->query(L, R), rv = r->query(L, R);
        return comb(lv, rv);
    }
    void update(int idx, int change){
        if(hi <= idx || idx < lo) return;
        if(mid >= idx) splitxor ^= change;
        if(mid != idx){
            l->update(idx, change);
            r->update(idx, change);
        }
        freq = comb(l->freq, r->freq);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = str.size();
    vi v(n + 1);
    rep(i, 0, n) v[i + 1] = v[i] ^ (1 << (str[i] - 'a'));
    Node *tree = new Node(0, n + 1, v);
    int q; cin >> q;
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int l, r; cin >> l >> r;
            vi res = tree->query(l - 1, r + 1);
            ll ans = 0;
            rep(i, 0, upb) if(res[i] > 1) ans += res[i] * (res[i] - 1) / 2;
            cout << ans << "\n";
        }
        else{
            int idx; string st; cin >> idx >> st;
            tree->update(idx, (1<<(st[0] - 'a')) ^ (1<<(str[idx - 1] - 'a')));
            str[idx - 1] = st[0];
        }
    }
    return 0;
}