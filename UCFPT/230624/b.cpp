#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

struct SuffixArray{
    vi sa, lcp;
    SuffixArray(vi &s, int lim = 256){
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        x.back() = 0;
        sa = lcp = y, iota(all(sa), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p){
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i, 0, n) ws[x[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for(int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = 
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(i, 1, n) rank[sa[i]] = i;
        for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi complete;
    set<int> vs;
    vs.insert(0);
    int maxval = 1e9 + 1;
    vs.insert(maxval);
    vi starts;
    int cnt = 0;
    set<int> ends;
    rep(i, 0, n){
        int k; cin >> k;
        vi a(k);
        starts.pb(cnt);
        rep(j, 0, k){
            cin >> a[j];
            vs.insert(a[j]);
            complete.pb(a[j]);
        }
        ends.insert(cnt + k);
        cnt += k + 1;
        complete.pb(maxval);
    }

    unordered_map<int, int> rl, rev;
    for(int i : vs) {rl[i] = sz(rl); rev[rl[i]] = i;}
    rep(i, 0, sz(complete)) complete[i] = rl[complete[i]];
    SuffixArray sa(complete, sz(rl));
    vi revsa(sz(sa.sa));
    rep(i, 0, sz(sa.sa)){
        revsa[sa.sa[i]] = i;
    }
    auto cmp = [&](int a, int b)->bool{
        return revsa[a] > revsa[b];
    };
    priority_queue<int, vi, decltype(cmp)> pq(cmp);
    for(int i : starts) pq.push(i);
    while(pq.size()){
        int v = pq.top(); pq.pop();
        cout << rev[complete[v]] << " ";
        if(ends.count(v + 1) == 0) pq.push(v + 1);
    }
    cout << "\n";
}
