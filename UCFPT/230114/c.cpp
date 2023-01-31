#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef vector<int> vi;
typedef long long ll;
typedef pair<ll, ll> pii;

// ld eps = 1e-10;

pii sub(pii a, pii b)
{
    // b - a
    return {b.first - a.first, b.second - a.second};
}

void rotate(pii &a, bool left)
{
    pii ac = a;
    if (left)
    {
        a.first = -ac.second;
        a.second = ac.first;
    }
    else
    {
        a.first = ac.second;
        a.second = -ac.first;
    }
}

ll distsqr(pii a, pii b)
{
    pii c = sub(a, b);
    return c.first * c.first + c.second * c.second;
}

ll dot(pii a, pii b)
{
    return a.first * b.first + a.second * b.second;
}

ll crossz(pii a, pii b)
{
    return a.first * b.second - b.first * a.second;
}

pii scale(pii a, ll c)
{
    return {a.first * c, a.second * c};
}

pii proj(pii a, pii b)
{
    // projection of b onto a
    return scale(a, dot(a, b) / dot(a, a));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, k, d;
    while (true)
    {
        cin >> n >> k >> d;
        int dsqr = d * d;
        if (n == 0 && k == 0 && d == 0)
            break;
        int tot = n + k;
        vector<pii> pts(tot);
        for (int i = 0; i < tot; i++)
        {
            cin >> pts[i].first >> pts[i].second;
        }
        if (tot == 1)
        {
            cout << 0 << nl;
            continue;
        }
        else if (tot == 2)
        {
            if (n == 1 && k == 1)
            {
                cout << (distsqr(pts[0], pts[1]) < dsqr) << nl;
            }
            else
            {
                cout << 0 << nl;
            }
            continue;
        }
        int mindestruction = INT_MAX;
        for (int i = 0; i < tot; i++)
        {
            for (int j = 0; j < tot; j++)
            {
                if (i == j)
                    continue;
                pii wall = sub(pts[i], pts[j]);

                if (i < n == j < n)
                {
                    // wall should go from one to another
                }
                else
                {
                    // rotate wall 90 degrees to left, wall should go between them
                    rotate(wall, true);
                }
                pii perp = wall;
                rotate(perp, false);
                for (int l = 0; l < 2; l++)
                {
                    // direction of wall
                    if (l == 1)
                        perp = scale(perp, -1);
                    ll walllensqr = dot(perp, perp);
                    for (int m = 0; m < 2; m++)
                    {
                        // which country belongs on close side
                        int destroy = 0;
                        for (int k = 0; k < tot; k++)
                        {
                            pii dist = sub(pts[i], pts[k]);
                            ll val = dot(dist, perp);
                            ll val2 = val * val;
                            if((k < n) == m){
                                if(val <= 0){}
                                else destroy++;
                            }
                            else{
                                if(val >= 0 && val2 >= dsqr * walllensqr){}
                                else destroy++;
                            }
                        }
                        mindestruction = min(destroy, mindestruction);
                    }
                }
            }
        }
        cout << mindestruction << nl;
    }
}
