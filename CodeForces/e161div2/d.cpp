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

struct Node
{
    int idx;
    int attack;
    int defense;
    Node *left = NULL, *right = NULL;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi a(n), d(n);
        rep(i, 0, n) cin >> a[i];
        rep(i, 0, n) cin >> d[i];
        vector<Node *> pts(n);
        rep(i, 0, n)
        {
            pts[i] = new Node();
            pts[i]->idx = i;
            pts[i]->attack = a[i];
            pts[i]->defense = d[i];
            if (i)
                pts[i]->left = pts[i - 1];
        }
        rep(i, 0, n){
            if (i + 1 < n)
                pts[i]->right = pts[i + 1];
        }
        queue<int> q, nextq;
        rep(i, 0, n)
        {
            q.push(i);
        }
        vi alive(n, 1);
        vi round(n);
        rep(i, 0, n)
        {
            vi rem;
            while (!q.empty())
            {
                int k = q.front();
                q.pop();
                if (!alive[k])
                    continue;
                Node *p = pts[k];
                int att = 0;
                if (p->left)
                    att += p->left->attack;
                if (p->right)
                    att += p->right->attack;
                if (att > p->defense)
                {
                    alive[k] = false;
                    rem.pb(k);
                    round[i]++;
                }
            }
            for (int k : rem)
            {
                Node *p = pts[k];
                if (p->left)
                {
                    p->left->right = p->right;
                    nextq.push(p->left->idx);
                }
                if (p->right)
                {
                    p->right->left = p->left;
                    nextq.push(p->right->idx);
                }
            }
            swap(q, nextq);
        }
        rep(i, 0, n){
            cout << round[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
