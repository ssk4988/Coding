#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
const int F = 100;
using fbs = bitset<F>;
const int MAXN = 1000;
using nbs = bitset<MAXN>;

random_device rd;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
auto gettime() {
    return chrono::steady_clock::now().time_since_epoch().count();
}

int n, m, l, d, e; 

vi lens, imp;
vector<fbs> fact_mem;
// fact_mem - list of memories per fact
fbs dep_adj[F], dep[F], mutex_base[F];
// dep - all transitive dependencies

int critcover[MAXN], depcover[MAXN];

ll testspersec = 500000;
ll iterpercase = 40000;
const double timelimit = 5;
const bool DEBUG = 0;

double score(fbs &crit, nbs &cand) {
    int base_score = 0;
    int len = 0;
    fbs violate, selected, selected_dep;
    rep(i, 0, n) {
        if(!cand[i]) continue;
        base_score += imp[i];
        len += lens[i];
        selected |= fact_mem[i];
    }
    // if(len == 0) return 0;
    // if(len > l) return 0;
    double score = base_score;
    score *= 1 - pow(double(len) / l, 3);
    int critcnt = (crit & selected).count();
    score *= pow(double(critcnt) / sz(crit), 1.5);
    // int vj = 0;
    rep(i, 0, F) {
        if(!selected[i]) continue;
        // vj += (mutex_base[i] & selected).count();
        violate |= mutex_base[i] & selected;
        selected_dep |= dep[i];
    }
    int vj = violate.count();
    int mj = selected.count();
    int tj = selected_dep.count();
    score *= 1 - double(vj) / mj;
    score *= double(mj) / tj;
    return score;
}

bool accept(double E,double E_next,double T){
    // higher is better so un-negate
    double prob = exp((E_next-E)/T);
    // double prob =  exp(-(E_next-E)/T);
    if(prob > 1) return true;
    else{
        bernoulli_distribution bd(prob); 
        return bd(rng);
    }
}

uniform_int_distribution<int> boolgen(0, 1);
uniform_int_distribution<int> stepgen(1, 2);
uniform_int_distribution<int> ngen(0, 1);


// const bool USEWEIGHTED = 0;
nbs modify(nbs cur, int totcrit, int totdep, double T) {
    // int iters = stepgen(rng);
    int iters = 1;
    rep(_, 0, iters) {
        int a;
        bool useweighted = uniform_real_distribution<double>(0, 1)(rng) < 0;
        if(useweighted) {
            vector<double> probs(n);
            double probsum = 0;
            rep(i, 0, n) {
                probs[i] = (double(critcover[i]) / totcrit + 1) * (depcover[i] / totdep + 1);
                if(cur[i]) probs[i] = 1 / probs[i];
                probsum += probs[i];
            }
            double genprob = uniform_real_distribution<double>(0, probsum)(rng);
            a = 0;
            while(a+1 < n && genprob > probs[a]) {
                genprob -= probs[a];
                a++;
            }
        } else {
            a = ngen(rng);
        }
        cur[a].flip();
    }
    return cur;
}

pair<double, nbs> simAnneal(fbs crit, fbs deps) {
    // best params: 7 9s, 1000
    /*
    unweighted
    0.999999999999
    1000
    531730.91713447
    6 9s with 5 sec
    546707.58963003
    */
    double u = 0.9999999999; // decay rate
    double T = 1000; // Initial temperature
    T = pow(1/u, iterpercase);
    // T = 1.01;
    // int curiter = 0;
    // cerr << T << " " << iterpercase << "\n";
    const int totcrit = crit.count();
    const int totdep = deps.count();
    nbs cur;
    while(cur.count() == 0) cur = modify(cur, totcrit, totdep, T);
    nbs best = cur;
    double cur_score = score(crit, cur);
    double best_score = score(crit, best);
    // while(curiter++ < iterpercase) {
    while(T > 1) {
        nbs nxt = modify(cur, totcrit, totdep, T);
        double nxt_score = score(crit, nxt);
        if(accept(cur_score, nxt_score, T)) {
            cur = nxt;
            if(nxt_score > best_score) {
                best_score = nxt_score;
                best = nxt;
            }
            cur_score = nxt_score;
        }
        T *= u;
        // T = max(1 + 1e-7, u);
    }
    return {best_score, best};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    auto start = gettime();
    cin >> n >> m >> l >> d >> e;
    ngen = uniform_int_distribution<int>(0, n-1);
    lens.resize(n), imp.resize(n);
    fact_mem.resize(n); 
    rep(i, 0, n) {
        cin >> lens[i] >> imp[i];
        int k; cin >> k;
        rep(j, 0, k) {
            int u; cin >> u; u--;
            fact_mem[i][u] = 1;
        }
    }
    rep(i, 0, d) {
        int u, v; cin >> u >> v;
        u--, v--;
        dep_adj[u][v] = 1;
    }
    rep(i, 0, e) {
        int u, v; cin >> u >> v;
        u--, v--;
        mutex_base[u][v] = mutex_base[v][u] = 1;
    }
    auto dfs = [&](int u, int s, auto &&dfs) -> void {
        if(dep[s][u]) return;
        dep[s][u] = 1;
        rep(v, 0, F) if(dep_adj[u][v]) dfs(v, s, dfs);
    };
    rep(i, 0, F) dfs(i, i, dfs);
    double total_score = 0;
    auto prv_time = gettime();
    rep(qid, 0, m) {
        if(qid) {
            double duration = (prv_time-start)/1e9;
            iterpercase = (timelimit - 0.2 - duration) / (m-qid) * testspersec;
            if(DEBUG) {
                cerr << "qid=" << qid << " testspersec=" << testspersec << " iterspercase=" << iterpercase << " duration=" << duration << "\n";
            }
        }
        memset(critcover, 0, sizeof critcover);
        memset(depcover, 0, sizeof depcover);
        int k; cin >> k;
        fbs crit;
        fbs deps;
        rep(i, 0, k) {
            int j; cin >> j; j--;
            crit[j] = 1;
            deps |= dep[j];
        }
        rep(i, 0, n) {
            critcover[i] = (crit & fact_mem[i]).count();
            depcover[i] = (deps & fact_mem[i]).count();
        }
        double sc = 0;
        nbs cand;
        tie(sc, cand) = simAnneal(crit, deps);
        cout << cand.count() << " ";
        rep(i, 0, n) if(cand[i]) cout << i+1 << " ";
        cout << "\n";
        total_score += score(crit, cand);
        auto nxt_time = gettime();
        testspersec = iterpercase / ((nxt_time - prv_time) / 1e9);
        prv_time = nxt_time;
    }
    cerr << fixed << setprecision(8) << total_score << "\n";
    
    
    return 0;
}
