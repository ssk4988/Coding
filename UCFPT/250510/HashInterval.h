struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str): ha(sz(str)+1), pw(ha) {
        pw[0] = 1;
        rep(i,0,sz(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
            
    }
    H hashInterval(int a, int b) {
        return ha[b] - ha[a] * pw[b-a];
    }
};
