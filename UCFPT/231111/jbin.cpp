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
    rep(i, 0, n){
        cin >> lines[i].f.f >> lines[i].f.s >> lines[i].s.f >> lines[i].s.s;
        if(lines[i].f > lines[i].s) swap(lines[i].f, lines[i].s);
    }
    int lo = 0, hi = 1e6 + 100;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        vi inq(n);
        int minX = -mid, maxX = mid, minY = -mid, maxY = mid;
        queue<int> q;
        vector<pair<pii, pii>> frontier = {{{minX, minY}, {minX, maxY}}, {{minX, minY}, {maxX, minY}}, {{maxX, minY}, {maxX, maxY}}, {{minX, maxY}, {maxX, maxY}}};
        rep(i, 0, n){
            bool is = false;
            for(auto line : frontier){
                if(intersect(line.f, line.s, lines[i].f, lines[i].s)){
                    is = true;
                }
            }
            if(is){
                q.push(i);
                inq[i] = true;
                auto [p1, p2] = lines[i];
                minX = min(minX, p1.f);
                minX = min(minX, p2.f);
                maxX = max(maxX, p1.f);
                maxX = max(maxX, p2.f);
                minY = min(minY, p1.s);
                minY = min(minY, p2.s);
                maxY = max(maxY, p1.s);
                maxY = max(maxY, p2.s);
            }

        }
        while(!q.empty()){
            auto id = q.front(); q.pop();
            frontier = {{{minX, minY}, {minX, maxY}}, {{minX, minY}, {maxX, minY}}, {{maxX, minY}, {maxX, maxY}}, {{minX, maxY}, {maxX, maxY}}};
            rep(i, 0, n){
                if(inq[i]) continue;
                bool is = false;
                for(auto line : frontier){
                    if(intersect(line.f, line.s, lines[i].f, lines[i].s)){
                        is = true;
                    }
                }
                if(is){
                    q.push(i);
                    inq[i] = true;
                    auto [p1, p2] = lines[i];
                    minX = min(minX, p1.f);
                    minX = min(minX, p2.f);
                    maxX = max(maxX, p1.f);
                    maxX = max(maxX, p2.f);
                    minY = min(minY, p1.s);
                    minY = min(minY, p2.s);
                    maxY = max(maxY, p1.s);
                    maxY = max(maxY, p2.s);
                }

            }
        }
        if(minX <= a && a <= maxX && minY <= b && b <= maxY){
            hi = mid;
        }
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
