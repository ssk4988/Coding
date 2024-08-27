#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(vi& s, int lim=256) {
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
        x.push_back(0);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(i,0,n) ws[x[i]]++;
            rep(i,1,lim)ws[i] += ws[i-1];
            for(int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
            swap(x,y),p=1,x[sa[0]] = 0;
            rep(i,1,n) a = sa[i-1], b = sa[i], x[b] = 
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p-1 : p++;
        }
        rep(i,1,n) rank[sa[i]] = i;
        for(int i = 0, j; i < n-1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
    }
};

template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for(int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j + pw]);
        }
    }
    T query(int a, int b) {
        while(a >= b);
        // assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi digs(n);
    vi concat;
    // vvi idx(n);
    vvi furthest(n);
    vii strpl;
    rep(i, 0, n){
        string str; cin >> str;
        for(char c : str){
            digs[i].push_back(c - '0' + 2);
            // idx[i].push_back(sz(digs));
            strpl.push_back({i, sz(digs[i]) - 1});
            concat.push_back(digs[i].back());
        }
        strpl.push_back({-1, -1});
        concat.push_back(1);
        furthest[i].resize(sz(str));
    }
    strpl.push_back({-1, -1});
    SuffixArray sa(concat);
    RMQ rmq(sa.lcp);
    set<pii> best;
    vi latest(n, -1);
    rep(i, 0, n){
        best.insert({latest[i], i});
    }
    while(sz(strpl) != sz(sa.sa));
    // assert(sz(strpl) == sz(sa.sa));
    rep(i, 0, sz(sa.sa)){
        int v = sa.sa[i];
        auto [c, cidx] = strpl[v];
        if(c == -1) continue;
        int prv = -1;
        for(auto it = best.rbegin(); it != best.rend(); it++){
            auto [lidx, w] = *it;
            if(w == c) continue;
            prv = lidx;
            break;
        }
        if(prv != -1){
            while(prv >= i);
            // assert(prv < i);
            int lcp = min(sz(digs[c]) - cidx, rmq.query(prv+1, i+1));
            // cout << "upd " << c << " " << cidx << "," << i << " " << lcp << endl;
            furthest[c][cidx] = max(furthest[c][cidx], lcp);
        }
        best.erase({latest[c], c});
        latest[c] = i;
        best.insert({latest[c], c});
    }
    best.clear();
    int lim = sz(concat) + 5;
    latest.assign(n, lim);
    rep(i, 0, n){
        best.insert({latest[i], i});
    }
    for(int i = sz(sa.sa)-1; i >= 0; i--){
        int v = sa.sa[i];
        auto [c, cidx] = strpl[v];
        if(c == -1) continue;
        int prv = lim;
        for(auto it = best.begin(); it != best.end(); it++){
            auto [lidx, w] = *it;
            if(w == c) continue;
            prv = lidx;
            break;
        }
        // cout << i << " " << c << "," << cidx << " : ";
        // rep(j, 0, n){
        //     cout << latest[j] << " ";
        // }
        // cout << endl;
        if(prv != lim){
            while(i >= prv);
            // assert(i < prv);
            int lcp = min(sz(digs[c]) - cidx, rmq.query(i+1, prv+1));
            // cout << "upd " << c << " " << cidx << "," << i << " " << lcp << endl;
            furthest[c][cidx] = max(furthest[c][cidx], lcp);
        }
        best.erase({latest[c], c});
        latest[c] = i;
        best.insert({latest[c], c});
    }
    // for(int i : sa.sa){
    //     if(i >= sz(concat)) continue;
    //     rep(j, i, sz(concat)){
    //         cout << concat[j] << ",";
    //     }
    //     cout << endl;
    // }
    // rep(i, 0, sz(concat)){
    //     cout << concat[i] << ",";
    // }
    // cout << endl;
    // rep(i, 0, sz(concat)){
    //     cout << strpl[i].first << "," << strpl[i].second << "\n";
    // }
    cout << fixed << setprecision(8);
    map<int, int> freq;
    rep(i, 0, n){
        freq[digs[i].back()]++;
    }
    rep(i, 0, n){
        if(freq[digs[i].back()] > 1){
            cout << "Impossible\n";
            continue;
        }
        ld sum = 0;
        rep(j, 0, sz(furthest[i])){
            sum += furthest[i][j] +1;
            // cout << furthest[i][j] << " ";
        }
        // cout << endl;
        sum /= sz(furthest[i]);
        cout << sum << "\n";
    }


    return 0;
}
