use std::io::{self, prelude::*};

pub struct DSUTree {
    par: Vec<usize>,
    rep: Vec<usize>,
    children: Vec<Vec<usize>>
}

impl DSUTree {
    pub fn new(n: usize) -> Self { 
        return Self { 
            par: (0..n).map(|x| x).collect::<Vec<usize>>(),
            rep: (0..n).map(|x| x).collect::<Vec<usize>>(),
            children: vec![Vec::new(); n]
        }; 
    }
    
    pub fn find(&mut self, u: usize) -> usize {
        if self.rep[u] != u {
            self.rep[u] = self.find(self.rep[u]);
        }
        self.rep[u]
    }

    pub fn join(&mut self, mut u: usize, mut v: usize) -> bool {
        u = self.find(u);
        v = self.find(v);
        if u == v { return false; }
        let n = self.par.len();
        self.par.push(n);
        self.rep.push(n);
        self.children.push(vec![u, v]);
        self.par[u] = n;
        self.par[v] = n;
        self.rep[u] = n;
        self.rep[v] = n;
        return true;
    }
}

fn dfs(u: usize, dt: &DSUTree, scores: &mut Vec<i32>, ans: &mut Vec<i64>, ws: &Vec<i32>) -> usize {
    // eprintln!("u: {u}");
    let diff = if dt.par[u] == u { 0 } else { ws[dt.par[u]] - ws[u] };
    let weight = (scores[u] as i64) * (diff as i64);
    let mut cs: Vec<usize> = Vec::new();
    for v in &dt.children[u] {
        cs.push(dfs(*v, dt, scores, ans, ws));
    }
    if cs.len() == 0 {
        ans[u] = weight;
        return u;
    }
    let mut c = cs[0];
    for c1 in cs {
        if ans[c1] > ans[c] { c = c1; }
    }
    ans[c] += weight;
    c
}

fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());

    let tc = input.token::<i32>();
    for cn in 0..tc {
        let (n, m, p) = (input.token::<usize>(), input.token::<usize>(), input.token::<usize>());
        let mut marked = vec![false; n];
        for i in 0..p {
            let x = input.token::<usize>()-1;
            marked[x] = true;
        }
        let mut dt = DSUTree::new(n);
        let mut edges = vec![(0,0,0); m];
        for i in 0..m {
            edges[i] = (input.token::<usize>()-1, input.token::<usize>()-1, input.token::<usize>());
            (edges[i].0, edges[i].1, edges[i].2) = (edges[i].2, edges[i].0, edges[i].1);
        }
        // dbg!(&edges);
        edges.sort();
        let mut scores = (0..n).map(|x| if marked[x] { 1 } else { 0 }).collect::<Vec<_>>();
        let mut ws = vec![0i32; n];
        for (w, u, v) in edges {
            // println!("try {w} {u} {v}");
            if dt.join(u, v) {
                // println!("{w} {u} {v}");
                scores.push(scores[dt.children[dt.par.len()-1][0]] + scores[dt.children[dt.par.len()-1][1]]);
                ws.push(w as i32);
                // dbg!(&scores);
            }
        }
        // dbg!(&dt.par);
        // dbg!(&ws);
        // dbg!(&scores);
        let mut ans = (0..n).map(|x| 0).collect::<Vec<i64>>();
        dfs(dt.par.len()-1, &dt, &mut scores, &mut ans, &ws);
        // dbg!(&ans);
        ans.sort();
        ans.reverse();
        for i in 1..n {
            ans[i] += ans[i-1];
        }
        let base = (*ws.iter().last().unwrap() as i64) * (p as i64);
        for x in ans { write!(writer, "{} ", base - x); }
        writeln!(writer, "");
    }
}

pub struct Scanner<B> {
    reader: B,
    buffer: Vec<String>,
}

impl<R: BufRead> Scanner<R> {
    pub fn token<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            self.reader.read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

impl<R: BufRead> From<R> for Scanner<R> {
    fn from(reader: R) -> Self {
        Self {
            reader,
            buffer: Vec::new(),
        }
    }
}
