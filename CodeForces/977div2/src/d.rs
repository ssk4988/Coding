use std::{cmp::{max, min}, io::{self, prelude::*}};

fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());
    let tc = input.token::<u32>();
    for cn in 0..tc {
        let (n, m) = (input.token::<usize>(), input.token::<usize>());
        let mut grid = vec![vec![0i64; m]; n];
        let mut pref = vec![vec![0i64; m+1]; n];
        let mut suffMx = vec![vec![0i64; m+1]; n];
        let mut prefMn = vec![vec![0i64; m+1]; n];
        let mut dpL = vec![vec![-(1i64 << 60); m+1]; n];
        let mut dpR = vec![vec![-(1i64 << 60); m+1]; n];
        for i in 0..n {
            for j in 0..m {
                grid[i][j] = input.token::<i64>();
                pref[i][j+1] = pref[i][j] + grid[i][j];
                prefMn[i][j+1] = min(prefMn[i][j], pref[i][j+1]);
            }
            for j in (0..m+1).rev() {
                suffMx[i][j] = pref[i][j];
                if j < m {
                    suffMx[i][j] = max(suffMx[i][j+1], suffMx[i][j]);
                }
            }
        }
        for j in 1..m+1 {
            dpR[0][j] = pref[0][j] - prefMn[0][j-1];
        }
        for j in 0..m {
            dpL[0][j] = suffMx[0][j+1] - pref[0][j];
        }
        for i in 1..n {
            for j in 2..m+1 {
                dpR[i][j] = max(dpR[i][j], max(dpR[i-1][j-1], dpL[i-1][j-1]) + pref[i][j] - prefMn[i][j-2]);
                if j > 2 { // optional?
                    dpR[i][j] = max(dpR[i][j], dpR[i][j-1] + grid[i][j-1]);
                }
            }
            for j in (0..m-1).rev() {
                dpL[i][j] = max(dpL[i][j], max(dpL[i-1][j+1], dpR[i-1][j+1]) + suffMx[i][j+2] - pref[i][j]);
                if j < m-2 {
                    dpL[i][j] = max(dpL[i][j], dpL[i][j+1] + grid[i][j]);
                }
            }
        }
        // dbg!(&pref);
        // dbg!(&suffMx);
        // dbg!(&dpL);
        writeln!(writer, "{}", dpL.last().unwrap().iter().max().unwrap());
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
