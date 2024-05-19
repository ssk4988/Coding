#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


const int N = 1e6 + 500;
int cnt[2][N];
set<int> diff;

void change(int p, int x, int v) {
    if(cnt[0][x] != cnt[1][x]) diff.erase(x);
    cnt[p][x] = v;
    if(cnt[0][x] != cnt[1][x]) diff.insert(x);
}

void add(int p, int x) {
    if(x == 0) return;
    if(cnt[p][x-1]) return change(p, x-1, 0), add(p, x+1);
    if(cnt[p][x+1]) return change(p, x+1, 0), add(p, x+2);
    if(!cnt[p][x]) return change(p, x, 1);
    int l = x, r = x;
    while(l-2 >= 0 && cnt[p][l-2]) l -= 2, change(p, l, 0);
    while(cnt[p][r+2]) r += 2, change(p, r, 0);
    add(p, r+1);
    add(p ^ 1, l-1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    rep(i, 0, q){
        string c, s; int x; cin >> c >> s >> x;
        int p = c == "B";
        p ^= s == "-";
        add(p, x);
        if(sz(diff)){
            int idx = *diff.rbegin();
            cout << (cnt[0][idx] > cnt[1][idx] ? "Alice" : "Bob") << "\n";
        } else cout << "Equal\n";
    }
    return 0;
}
