#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

#define f first
#define s second

bool type(pii s, pii e){
    if(s.f == e.f) return 0; // vertical
    if(s.s == e.s) return 1;
    assert(false);
    return 1;
}

bool intersect(pii s1, pii e1, pii s2, pii e2){
    if(s1 > e1) swap(s1, e1);
    if(s2 > e2) swap(s2, e2);
    bool t1 = type(s1, e1), t2 = type(s2, e2);
    if(t1 > t2) {
        swap(t1, t2);
        swap(s1, s2);
        swap(e1, e2);
    }
    if(t1 == t2){
        if(t1 == 0){
            // both vertical
            if(s1.f != s2.f) return false;
            return !(e2.s < s1.s) && !(e1.s < s2.s);
        }
        else{
            // both horizontal
            if(s1.s != s2.s) return false;
            return !(e2.f < s1.f) && !(e1.f < s2.f);
        }
    }
    // 1st vertical, 2nd horizontal
    return (s1.s <= s2.s && s2.s <= e1.s) && (s2.f <= s1.f && s1.f <= e2.f);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int a, b; cin >> a >> b;
    int n; cin >> n;
    vector<pair<pii, pii>> lines(n);
    set<int> events;
    rep(i, 0, n){
        cin >> lines[i].f.f >> lines[i].f.s >> lines[i].s.f >> lines[i].s.s;
        if(lines[i].f > lines[i].s) swap(lines[i].f, lines[i].s);
        int score = min(max(abs(lines[i].f.f), abs(lines[i].f.s)), max(abs(lines[i].s.f), abs(lines[i].s.s)));
        events.insert(score);
    }
    events.insert(0);
    events.insert(abs(b));
    events.insert(abs(a));
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    vector<pair<pii, pii>> frontier;
    auto rebuild = [&]() -> void {
        frontier = {{{minX, minY}, {minX, maxY}}, {{minX, minY}, {maxX, minY}}, {{maxX, minY}, {maxX, maxY}}, {{minX, maxY}, {maxX, maxY}}};
    };
    rebuild();
    auto addp = [&](pii p) -> void {
        minX = min(minX, p.f);
        maxX = max(maxX, p.f);
        minY = min(minY, p.s);
        maxY = max(maxY, p.s);
        rebuild();
    };
    auto add = [&](pair<pii, pii> line) -> void { addp(line.f), addp(line.s); };
    int ans = 1e9;
    vi added(n);
    for(auto score : events){
        addp({-score, -score}), addp({score, score});
        bool didsomething = true;
        while(didsomething){
            didsomething = false;
            rep(i, 0, n){
                if(added[i]) continue;
                bool is = false;
                for(auto line : frontier){
                    if(intersect(line.f, line.s, lines[i].f, lines[i].s)){
                        is = true;
                    }
                }
                if(is){
                    added[i] = true;
                    add(lines[i]);
                    didsomething = true;
                }
            }
        }
        if(minX <= a && a <= maxX && minY <= b && b <= maxY){
            ans = min(ans, score);
        }
    }
    cout << ans << "\n";
    return 0;
}
