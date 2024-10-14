use std::io::{self, prelude::*};

pub struct DSU {
    e: Vec<i32>
}

impl DSU {
    pub fn new(n: usize) -> Self { return Self {e: vec![-1; n]}; }
    
    pub fn find(&mut self, u: usize) -> usize {
        return if self.e[u] < 0 { u } else {
            self.e[u] = self.find(self.e[u] as usize) as i32;
            self.e[u] as usize
        }
    }

    pub fn join(&mut self, mut u: usize, mut v: usize) -> bool {
        u = self.find(u);
        v = self.find(v);
        if u == v { return false; }
        if self.e[u] > self.e[v] { (u, v) = (v, u); }
        self.e[u] += self.e[v];
        self.e[v] = u as i32;
        return true;
    }
}

fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());
    let (n, m) = (input.token::<usize>(), input.token::<usize>());
    let mut roads = Vec::<(usize, usize)>::new();
    let mut dsu = DSU::new(n);
    for i in 0..m {
        let (u, v) = (input.token::<usize>(), input.token::<usize>());
        dsu.join(u-1,v-1);
    }
    for i in 0..n-1 {
        if dsu.join(i, i+1) {
            roads.push((i+1, i+2));
        }
    }
    writeln!(writer, "{}", roads.len());
    for (u,v) in roads {
        writeln!(writer, "{u} {v}");
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
