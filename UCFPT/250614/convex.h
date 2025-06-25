template<class P> vector<P> convex_hull(vector<P> pts) {
    if(sz(pts) == 1) return pts;
    stable_sort(all(pts));
    vector<P> hull(sz(pts)+1);
    int k = 0, t = 2;
    rep(_, 0, 2) {
        for(P p : pts) {
            while(k >= t && hull[k-2].cross(hull[k-1], p) <= 0) k--;
            hull[k++] = p;
        }
        reverse(all(pts));
        t = k + 1;
    }
    hull.resize(k-1);
    return hull;
}
