use std::{collections::HashMap, io::{self, prelude::*}};

fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());
    let nc = input.token::<u32>();
    for cn in 0..nc {
        let n = input.token::<u32>();
        let x = input.token::<u32>();
        let mut a = (0..n).map(|_| input.token::<u32>()).collect::<Vec<_>>();
        a.sort();
        let mut ans = 0;
        let mut freq = HashMap::<u32, u32>::new();
        for v in a {
            if v > ans {break}
            let count = freq.entry(v % x).or_default();
            *count += 1;
            while *freq.entry(ans % x).or_default() > 0 {
                *freq.entry(ans % x).or_default() -= 1;
                ans += 1;
            }
        }
        writeln!(writer, "{ans}");
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
