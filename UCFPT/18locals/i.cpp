#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

const bool DEBUG = false;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // t == 1
    string tstr; cin >> tstr;
    int t = stoi(tstr);
    int ts = sz(tstr);
    int n; cin >> n;
    vector<string> fs(n);
    vi v(n);
    rep(i, 0, n){
        cin >> fs[i];
        v[i] = stoi(fs[i]);
    }
    // n++;
    vector<vi> cando(ts, vi(n));
    rep(i, 0, ts){
        rep(j, 0, n){
            if(sz(fs[j]) + i > ts) continue;
            if(tstr.substr(i, sz(fs[j])) == fs[j]){
                cando[i][j] = true;
                if(DEBUG){
                    cout << "cando " << i << " " << j << "\n";
                }
            }
        }
    }
    // rep(i, 0, ts) cando[i][n - 1] = true;
    vector<bool> inq(1 << (n + 2)); // bit n for if used travis, bit n + 1 on for travis used 2 digs
    // const int bs = 1 << n;
    queue<pi> q;
    q.push({0, 0}); // len, bitmask
    inq[0] = true;
    bool solveable = false;
    while(!q.empty() && !solveable){
        auto [len, b] = q.front();
        q.pop();
        if(DEBUG) cout << "visited " << len << " " << b << "\n";
        if(len == ts){
            solveable = true;
            break;
        }
        rep(j, 0, n){
            if(((b & (1 << j)) == 0) && cando[len][j] && !inq[b | (1 << j)]){
                q.push({len + sz(fs[j]), b | (1 << j)});
                if(len + sz(fs[j]) >= ts) solveable = true;
                inq[b | (1 << j)] = true;
            }
        }
        if(len + 1 <= ts && ((b & (1 << n)) == 0) && !inq[b | (1 << n)] && tstr[len] != '0'){
            q.push({len + 1, b | (1 << n)});
            if(len + 1 >= ts) solveable = true;
            inq[b | (1 << n)] = true;
        }
        if(len + 2 <= ts && ((b & (3 << n)) == 0) && !inq[b | (3 << n)] && tstr[len] != '0'){
            q.push({len + 2, b | (3 << n)});
            if(len + 2 >= ts) solveable = true;
            inq[b | (3 << n)] = true;
        }
    }
    cout << solveable << "\n";
}
