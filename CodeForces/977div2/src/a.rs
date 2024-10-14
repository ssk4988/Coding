use std::io::{self, prelude::*};

fn main() {
    let mut input = Scanner::from(io::stdin().lock());
    let mut writer = io::BufWriter::new(io::stdout().lock());
    let nc = input.token::<u32>();
    for cn in 0..nc {
        let n = input.token::<usize>();
        let mut a = vec![0; n];
        for i in 0..n {
            a[i] = input.token::<i32>();
        }
        a.sort();
        let mut ans = a[0];
        for i in 1..n { ans = (ans + a[i]) / 2; }
        writeln!(writer, "{}", ans);
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
